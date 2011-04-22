#include "pinctrl.h"

void pinctrl_init(void)
{
    __REG_CLR(HW_PINCTRL_CTRL) = __BLOCK_CLKGATE;
    __REG_CLR(HW_PINCTRL_CTRL) = __BLOCK_SFTRST;
}
