#include <pwm.h>

static pwm_start(int freq)
{
	int period = _1HZ_NS / freq;
	s3c_gpio_cfgpin(PWM_GPIO, S3C_GPIO_SFN(2));
	pwm_config(Pwm_devive, period / 2, period);
	pwm_enable(Pwm_devive);
}

static pwm_close()
{
	pwm_disable();
	s3c_gpio_cfgpin(PWM_GPIO,S3C_GPIO_OUTPUT);
}
