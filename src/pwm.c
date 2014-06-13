#include <pwm.h>

static struct semaphore lock;
static struct pwm_device Pwm_devive;

struct file_operations tiny_fops;

static int pwm_init()
{
	int ret;
	ret = gpio_request(PWM_GPIO,DEVICE_NAME);
	if(ret)
	{
		printk("request GPIO %d for pwm failed\n",ret);
	}
	gpio_set_value(PWM_GPIO,0);
	s3c_gpio_getcfg(S3C_GPIO_OUTPUT);
	Pwm_devive = pwm_request(PWM_ID,DEVICE_NAME);
	if (IS_ERR(Pwm_devive))
		{
			printk("request pwm %d for %s failed\n", PWM_ID, DEVICE_NAME);
			return -ENODEV;
		}
	pwm_stop();
	sema_init(&lock, 1);
	ret = misc_register(&tiny210_device);
	printk(DEVICE_NAME"initialization\n");
	return ret;
}

static void pwm_exit()
{
	pwm_stop();
	misc_deregister(&tiny210_device);
	gpio_free(PWM_GPIO);
}

module_init(pwm_init);
module_exit(pwm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MC");
MODULE_DESCRIPTION("pwm driver");
