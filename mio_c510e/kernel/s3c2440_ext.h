/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2011 by Amaury Pouly
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#ifndef __S3C2440_EXT_H__
#define __S3C2440_EXT_H__

#include "s3c2440.h"

/***********
 * CLK/PWR *
 ***********/

/* CLKCON */
#define CLKCON_IDLE     (1 << 2)
#define CLKCON_SLEEP    (1 << 3)
#define CLKCON_NAND     (1 << 4)
#define CLKCON_LCDC     (1 << 5)
#define CLKCON_USBH     (1 << 6)
#define CLKCON_USBD     (1 << 7)
#define CLKCON_PWM      (1 << 8)
#define CLKCON_SDI      (1 << 9)
#define CLKCON_UART0    (1 << 10)
#define CLKCON_UART1    (1 << 11)
#define CLKCON_UART2    (1 << 12)
#define CLKCON_GPIO     (1 << 13)
#define CLKCON_RTC      (1 << 14)
#define CLKCON_ADC      (1 << 15)
#define CLKCON_I2C      (1 << 16)
#define CLKCON_I2S      (1 << 17)
#define CLKCON_SPI      (1 << 18)
#define CLKCON_CAM      (1 << 19)
#define CLKCON_AC97     (1 << 20)

/*******
 * USB *
 *******/

/* EP_INT_REG / EP_INT_EN_REG  */
#define EP0_INTERRUPT   1
#define EP1_INTERRUPT   2

/* USB_INT_REG / USB_INT_EN_REG */
#define SUSPEND_INT     1
#define RESUME_INT      2
#define RESET_INT       4

/* EP0_CSR */
#define OUT_PKT_RDY     1
#define IN_PKT_RDY      2
#define SENT_STALL      4
#define DATA_END        8
#define SETUP_END       16
#define SEND_STALL      32
#define SRV_OUT_PKT_RDY 64
#define SRV_SETUP_END  128

/* IN_CSR1_REG */
#define IN_PKT_RDY_EPx  1
#define FIFO_FLUSH      (1 << 3)

/* IN_CSR2_REG */
#define MODE_IN         (1 << 5)

/* OUT_CSR2_REG */
#define AUTO_CLR        (1 << 7)

/* FUNC_ADDR */
#define ADDR_UPDATE     (1 << 7)

/*******
 * ADC *
 *******/

/* ADCCON */
#define ENABLE_START    (1 << 0)
#define READ_ START     (1 << 1)
#define STDBM           (1 << 2)
#define SEL_MUX_AIN0    (0 << 3)
#define SEL_MUX_AIN1    (1 << 3)
#define SEL_MUX_AIN2    (2 << 3)
#define SEL_MUX_AIN3    (3 << 3)
#define SEL_MUX_AINYM   (4 << 3)
#define SEL_MUX_AINYP   (5 << 3)
#define SEL_MUX_AINXM   (6 << 3)
#define SEL_MUX_AINXP   (7 << 3)
#define PRSCVL_bitp     6
#define PRSCEN          (1 << 14)
#define ECFLG           (1 << 15)

/* ADCTSC */
#define XY_PST_bitm     (3 << 0)
#define XY_PST_NOOP     (0 << 0)
#define XY_PST_X_MES    (1 << 0)
#define XY_PST_Y_MES    (2 << 0)
#define XY_PST_WAIT_INT (3 << 0)
#define AUTO_PST        (1 << 2)
#define PULL_UP         (1 << 3)
#define XP_SEN          (1 << 4)
#define XM_SEN          (1 << 5)
#define YP_SEN          (1 << 6)
#define YM_SEN          (1 << 7)
#define UD_SEN          (1 << 8)

/* ADCDAT0 */
#define XPDATA_bitm     0x3ff


#endif /* __S3C2440_EXT_H__ */
