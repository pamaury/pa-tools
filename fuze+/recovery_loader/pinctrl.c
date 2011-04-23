#include "pinctrl.h"
#include "system.h"
#include "logf.h"

void pinctrl_init(void)
{
    logf("pinctrl_init\n");
    //__REG_CLR(HW_PINCTRL_CTRL) = __BLOCK_CLKGATE | __BLOCK_SFTRST;
}
