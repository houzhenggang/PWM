/*
 * pwm.h
 *
 *  Created on: 2014年6月13日
 *      Author: root
 */

#ifndef PWM_H_
#define PWM_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/backlight.h>
#include <linux/err.h>
#include <linux/pwm.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>

#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

#define DEVICE_NAME	"pwm"
#define PWM_SET_FEQ 1
#define PWM_STOP	0
#define _1HZ_NS		1000000000UL
#define PWM_ID		0
#define PWM_GPIO	S5PV210_GPD0(0)

#endif /* PWM_H_ */
