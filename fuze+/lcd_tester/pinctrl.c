#include "pinctrl.h"
#include "system.h"
#include "logf.h"

void pinctrl_init(void)
{
    __REG_CLR(HW_PINCTRL_CTRL) = __BLOCK_CLKGATE;
}
