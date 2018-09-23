#ifndef _HARDWARE_GPIO_H
#define _HARDWARE_GPIO_H

#include <hardware/hardware.h>

__BEGIN_DECLS

#define GPIO_API_VERSION HARDWARE_MODULE_API_VERSION(1,0)
#define GPIO_HARDWARE_MODULE_ID "gpio"
#define GPIO_DEVICE_ID_MAIN "main_gpio"

struct gpio_device;
typedef struct gpio_device {

	struct hw_device_t common;

	int fd;

	int (*gp_export)(struct gpio_device* dev , unsigned int pin);
	int (*gp_unexport)(struct gpio_device* dev , unsigned int pin);
	int (*gp_set_direction)(struct gpio_device* dev , unsigned int pin , unsigned int value);
	int (*gp_set_value)(struct gpio_device* dev , unsigned int pin , unsigned int value);

} gpio_device_t;

static inline int gpio_open(const struct hw_module_t* module , gpio_device_t** device)
{
	return module->methods->open(module , GPIO_DEVICE_ID_MAIN , (struct hw_device_t**) device);
}

__END_DECLS

#endif //_HARDWARE_GPIO_H
