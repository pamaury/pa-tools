#include "pwm.h"
#include "clkctrl.h"
#include "pinctrl.h"

void imx233_pwm_init(void)
{
    __REG_SET(HW_PWM_CTRL) = __BLOCK_SFTRST;
    __REG_CLR(HW_PWM_CTRL) = __BLOCK_SFTRST | __BLOCK_CLKGATE;
    while(HW_PWM_CTRL & __BLOCK_CLKGATE);
    imx233_enable_pwm_xtal_clk24m(true);
}

bool imx233_pwm_is_channel_enable(int channel)
{
    return HW_PWM_CTRL & HW_PWM_CTRL__PWMx_ENABLE(channel);
}

void imx233_pwm_enable_channel(int channel, bool enable)
{
    if(enable)
        __REG_SET(HW_PWM_CTRL) = HW_PWM_CTRL__PWMx_ENABLE(channel);
    else
        __REG_CLR(HW_PWM_CTRL) = HW_PWM_CTRL__PWMx_ENABLE(channel);
}

void imx233_pwm_setup_channel(int channel, int period, int cdiv, int active,
    int active_state, int inactive, int inactive_state)
{
    /* stop */
    bool enable = imx233_pwm_is_channel_enable(channel);
    if(enable)
        imx233_pwm_enable_channel(channel, false);
    /* setup pin */
    imx233_set_pin_function(IMX233_PWM_PIN_BANK(channel), IMX233_PWM_PIN(channel),
        PINCTRL_FUNCTION_MAIN);
    imx233_set_pin_drive_strength(IMX233_PWM_PIN_BANK(channel), IMX233_PWM_PIN(channel),
        PINCTRL_DRIVE_4mA);
    /* watch the order ! active THEN period */
    HW_PWM_ACTIVEx(channel) = active << HW_PWM_ACTIVEx__ACTIVE_BP |
        inactive << HW_PWM_ACTIVEx__INACTIVE_BP;
    HW_PWM_PERIODx(channel) = period | active_state << HW_PWM_PERIODx__ACTIVE_STATE_BP |
        inactive_state << HW_PWM_PERIODx__INACTIVE_STATE_BP |
        cdiv << HW_PWM_PERIODx__CDIV_BP;
    /* restore */
    imx233_pwm_enable_channel(channel, enable);
}
