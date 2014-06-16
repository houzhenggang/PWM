#include <pwm.h>

static struct semaphore lock;
static struct pwm_device Pwm_devive;

static int pwm_open()
{
	if (!down_trylock(&lock))
	{
		return 0;
	} else
	{
		return -EBUSY;
	}
}

static int pwm_close()
{
	up(&lock);
	return 0;
}

static long pwm_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	switch (cmd)
	{
	case PWM_SET_FEQ:
		pwm_start(arg);
		break;

	case PWM_STOP:
		pwm_close();
		break;
	}
	return 0;
}

static struct file_operations tiny_fops = { .owner = THIS_MODULE, .open =
		pwm_open, .release = pwm_close, .unlocked_ioctl = pwm_ioctl };

static struct miscdevice tiny210_device = { .minor = MISC_DYNAMIC_MINOR, .name =
		DEVICE_NAME, .fops = &tiny_fops };

static int pwm_init()
{
	int ret;
	ret = gpio_request(PWM_GPIO, DEVICE_NAME);
	if (ret)
	{
		printk("request GPIO %d for pwm failed\n", ret);
	}
	gpio_set_value(PWM_GPIO, 0);
	s3c_gpio_getcfg(S3C_GPIO_OUTPUT);
	Pwm_devive = pwm_request(PWM_ID, DEVICE_NAME);
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
