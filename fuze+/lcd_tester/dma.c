#include "config.h"
#include "system.h"
#include "dma.h"
#include "imx233.h"

#define PHYSICAL_ADDR(x) x

void dma_init(void)
{
    /* Enable APHB and APBX */
    imx233_reset_block(&HW_APBH_CTRL0);
    imx233_reset_block(&HW_APBX_CTRL0);
}

void dma_reset_channel(unsigned chan)
{
    volatile uint32_t *ptr;
    uint32_t bm;
    if(APB_IS_APBX_CHANNEL(chan))
    {
        ptr = &HW_APBX_CHANNEL_CTRL;
        bm = HW_APBX_CHANNEL_CTRL__RESET_CHANNEL(APB_GET_DMA_CHANNEL(chan));
    }
    else
    {
        ptr = &HW_APBH_CTRL0;
        bm = HW_APBH_CTRL0__RESET_CHANNEL(APB_GET_DMA_CHANNEL(chan));
    }
    __REG_SET(*ptr) = bm;
    /* wait for end of reset */
    while(*ptr & bm)
        ;
}

void dma_clkgate_channel(unsigned chan, bool enable_clock)
{
    if(APB_IS_APBX_CHANNEL(chan))
        return;
    if(enable_clock)
        __REG_CLR(HW_APBH_CTRL0) =
            HW_APBH_CTRL0__CLKGATE_CHANNEL(APB_GET_DMA_CHANNEL(chan));
    else
        __REG_SET(HW_APBH_CTRL0) =
            HW_APBH_CTRL0__CLKGATE_CHANNEL(APB_GET_DMA_CHANNEL(chan));
}

void dma_freeze_channel(unsigned chan, bool freeze)
{
    volatile uint32_t *ptr;
    uint32_t bm;
    if(APB_IS_APBX_CHANNEL(chan))
    {
        ptr = &HW_APBX_CHANNEL_CTRL;
        bm = HW_APBX_CHANNEL_CTRL__FREEZE_CHANNEL(APB_GET_DMA_CHANNEL(chan));
    }
    else
    {
        ptr = &HW_APBH_CTRL0;
        bm = HW_APBH_CTRL0__FREEZE_CHANNEL(APB_GET_DMA_CHANNEL(chan));
    }

    if(freeze)
        __REG_SET(*ptr) = bm;
    else
        __REG_CLR(*ptr) = bm;
}

void dma_enable_channel_interrupt(unsigned chan, bool enable)
{
    volatile uint32_t *ptr;
    uint32_t bm;
    if(APB_IS_APBX_CHANNEL(chan))
    {
        ptr = &HW_APBX_CTRL1;
        bm = HW_APBX_CTRL1__CHx_CMDCMPLT_IRQ_EN(APB_GET_DMA_CHANNEL(chan));
    }
    else
    {
        ptr = &HW_APBH_CTRL1;
        bm = HW_APBH_CTRL1__CHx_CMDCMPLT_IRQ_EN(APB_GET_DMA_CHANNEL(chan));
    }

    if(enable)
    {
        __REG_SET(*ptr) = bm;
        dma_clear_channel_interrupt(chan);
    }
    else
        __REG_CLR(*ptr) = bm;
}

void dma_clear_channel_interrupt(unsigned chan)
{
    if(APB_IS_APBX_CHANNEL(chan))
    {
        __REG_CLR(HW_APBX_CTRL1) =
            HW_APBX_CTRL1__CHx_CMDCMPLT_IRQ(APB_GET_DMA_CHANNEL(chan));
        __REG_CLR(HW_APBX_CTRL2) =
            HW_APBX_CTRL2__CHx_ERROR_IRQ(APB_GET_DMA_CHANNEL(chan));
    }
    else
    {
        __REG_CLR(HW_APBH_CTRL1) =
            HW_APBH_CTRL1__CHx_CMDCMPLT_IRQ(APB_GET_DMA_CHANNEL(chan));
        __REG_CLR(HW_APBH_CTRL2) =
            HW_APBH_CTRL2__CHx_ERROR_IRQ(APB_GET_DMA_CHANNEL(chan));
    }
}

bool dma_is_channel_error_irq(unsigned chan)
{
    if(APB_IS_APBX_CHANNEL(chan))
        return !!(HW_APBX_CTRL2 &
            HW_APBX_CTRL2__CHx_ERROR_IRQ(APB_GET_DMA_CHANNEL(chan)));
    else
        return !!(HW_APBH_CTRL2 &
            HW_APBH_CTRL2__CHx_ERROR_IRQ(APB_GET_DMA_CHANNEL(chan)));
}

#if 0
/* Commit and/or discard all DMA descriptors and buffers pointed by them,
 * handle circular lists. At the same time, convert virtual pointers to
 * real ones */
static void dma_commit_and_discard(unsigned chan, struct apb_dma_command_t *cmd)
{
    /* We handle circular descriptors by using unused bits:
     * bits 8-11 are not used by the hardware so we first go through the whole
     * list and mark them all a special value at the same time we commit buffers
     * and then we go through the list another time to clear the mark and
     * commit the descriptors */
    struct apb_dma_command_t *cur = cmd;

    while((cur->cmd & HW_APB_CHx_CMD__UNUSED_BM) != HW_APB_CHx_CMD__UNUSED_MAGIC)
    {
        cur->cmd = (cur->cmd & ~HW_APB_CHx_CMD__UNUSED_BM) | HW_APB_CHx_CMD__UNUSED_MAGIC;
        int op = cur->cmd & HW_APB_CHx_CMD__COMMAND_BM;
        int sz = __XTRACT_EX(cur->cmd, HW_APB_CHx_CMD__XFER_COUNT);
        /* device > host: discard */
        if(op == HW_APB_CHx_CMD__COMMAND__WRITE)
            discard_dcache_range(cur->buffer, sz);
        /* host > device: commit and discard */
        else if(op == HW_APB_CHx_CMD__COMMAND__READ)
            commit_discard_dcache_range(cur->buffer, sz);
        if((uint32_t)cur->buffer % CACHEALIGN_SIZE)
            apb_nr_unaligned[chan]++;
        /* Virtual to physical buffer pointer conversion */
        cur->buffer = PHYSICAL_ADDR(cur->buffer);
        /* chain ? */
        if(cur->cmd & HW_APB_CHx_CMD__CHAIN)
            cur = cur->next;
        else
            break;
    }

    cur = cmd;
    while((cur->cmd & HW_APB_CHx_CMD__UNUSED_BM) != 0)
    {
        cur->cmd = cur->cmd & ~HW_APB_CHx_CMD__UNUSED_BM;
        int sz = __XTRACT_EX(cur->cmd, HW_APB_CHx_CMD__CMDWORDS) * sizeof(uint32_t);
        /* commit descriptor and discard descriptor */
        /* chain ? */
        if(cur->cmd & HW_APB_CHx_CMD__CHAIN)
        {
            struct apb_dma_command_t *next = cur->next;
            cur->next = PHYSICAL_ADDR(cur->next);
            commit_dcache_range(cur, sizeof(struct apb_dma_command_t) + sz);
            cur = next;
        }
        else
        {
            commit_dcache_range(cur, sizeof(struct apb_dma_command_t) + sz);
            break;
        }
    }
}
#else
static void dma_commit_and_discard(unsigned chan, struct apb_dma_command_t *cmd)
{
    (void) chan;
    (void) cmd;
}
#endif

void dma_start_command(unsigned chan, struct apb_dma_command_t *cmd)
{
    dma_commit_and_discard(chan, cmd);
    if(APB_IS_APBX_CHANNEL(chan))
    {
        HW_APBX_CHx_NXTCMDAR(APB_GET_DMA_CHANNEL(chan)) = (uint32_t)PHYSICAL_ADDR(cmd);
        HW_APBX_CHx_SEMA(APB_GET_DMA_CHANNEL(chan)) = 1;
    }
    else
    {
        HW_APBH_CHx_NXTCMDAR(APB_GET_DMA_CHANNEL(chan)) = (uint32_t)PHYSICAL_ADDR(cmd);
        HW_APBH_CHx_SEMA(APB_GET_DMA_CHANNEL(chan)) = 1;
    }
}

int dma_wait_completion(unsigned chan, unsigned tmo)
{
    tmo += current_tick;
    volatile uint32_t *sema;
    if(APB_IS_APBX_CHANNEL(chan))
        sema = &HW_APBX_CHx_SEMA(APB_GET_DMA_CHANNEL(chan));
    else
        sema = &HW_APBH_CHx_SEMA(APB_GET_DMA_CHANNEL(chan));

    while(*sema & HW_APB_CHx_SEMA__PHORE_BM && !TIME_AFTER(current_tick, tmo))
        udelay(10);
    return __XTRACT_EX(*sema, HW_APB_CHx_SEMA__PHORE);
}