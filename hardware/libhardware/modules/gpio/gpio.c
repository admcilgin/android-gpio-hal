/**
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/gpio.h>
#include <hardware/hardware.h>

#include <cutils/log.h>

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

static int write_to_file(char *device , char *value , int value_to_write)
{
    int written , fd , finalret;

	fd = TEMP_FAILURE_RETRY(open(device , O_RDWR));

	if(fd < 0)
		return -errno;

	written = TEMP_FAILURE_RETRY(write(fd , value , strlen(value)));

	if(written == -1)
		finalret = -errno;
	else if (written != strlen(value))
		finalret = -EAGAIN;
	else
		finalret = 0;

	errno = 0;
	close(fd);

	return finalret;
}

static int gpio_set_direction(gpio_device_t* dev __unused , unsigned int pin , unsigned int value)
{
	char value_buffer[16];
	int to_write;
	to_write = snprintf(value_buffer , sizeof(value_buffer), "2,%u,%u,\n", pin , value);
	return write_to_file("/dev/stormmxgpio" , value_buffer , to_write);
}

static int gpio_set_value(gpio_device_t* dev __unused , unsigned int pin , unsigned int value)
{
	char value_buffer[16];
	int to_write;
	to_write = snprintf(value_buffer , sizeof(value_buffer), "3,%u,%u,\n", pin , value);
	return write_to_file("/dev/stormmxgpio" , value_buffer , to_write);
}

static int gpio_export(gpio_device_t* dev __unused , unsigned int pin)
{
	char value_buffer[16];
	int to_write;
	to_write = snprintf(value_buffer , sizeof(value_buffer), "0,%u,\n", pin);
	return write_to_file("/dev/stormmxgpio" , value_buffer , to_write);
}

static int gpio_unexport(gpio_device_t* dev __unused , unsigned int pin)
{
	char value_buffer[16];
	int to_write;
	to_write = snprintf(value_buffer , sizeof(value_buffer), "1,%u,\n", pin);
	return write_to_file("/dev/stormmxgpio" , value_buffer , to_write);
}

static int gpio_close(hw_device_t *device)
{
	free(device);
	return 0;
}

static int gp_open(const hw_module_t* module, const char* id __unused,
        hw_device_t** device __unused)
{
	gpio_device_t *gpiodev = calloc(1 , sizeof(gpio_device_t));

	if(!gpiodev) {
		ALOGE("Cannot allocate memory for gpio device");
		return -ENOMEM;
	}

	gpiodev->common.tag = HARDWARE_DEVICE_TAG;
	gpiodev->common.module = (hw_module_t *) module;
	gpiodev->common.version = HARDWARE_DEVICE_API_VERSION(1,0);
	gpiodev->common.close = gpio_close;

	//function pointers
	gpiodev->gp_export = gpio_export;
	gpiodev->gp_unexport = gpio_unexport;
	gpiodev->gp_set_value = gpio_set_value;
	gpiodev->gp_set_direction = gpio_set_direction;

	*device = (hw_device_t *) gpiodev;

	return 0;
}
////////////////////////////
/* HW MODULE Definition */
////////////////////////////
static struct hw_module_methods_t gpio_module_methods = {
	 .open = gp_open ,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .module_api_version = GPIO_API_VERSION,
    .hal_api_version = HARDWARE_HAL_API_VERSION,
    .id = GPIO_HARDWARE_MODULE_ID,
    .name = "Gpio HAL",
    .author = "Nima Moahammadi",
    .methods = &gpio_module_methods,
};
