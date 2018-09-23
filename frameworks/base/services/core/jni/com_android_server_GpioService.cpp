/*
 * Copyright (C) 2009 The Android Open Source Project
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

#define LOG_TAG "GpioService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/gpio.h>

#include <stdio.h>

namespace android {

   static hw_module_t *gGpioModule = NULL;
   static gpio_device_t *gGpioDevice = NULL;

   static void gpioInit(JNIEnv /* env */, jobject /* clazz */) {

	   if(gGpioModule != NULL)
		   return;

	   int err = hw_get_module(GPIO_HARDWARE_MODULE_ID , (hw_module_t const**) &gGpioModule);

	   if(err)
		   ALOGE("Could not Load %s module (%s) " , GPIO_HARDWARE_MODULE_ID , strerror(-err));
	   else
	   {
		   if(gGpioModule)
			   gpio_open(gGpioModule , &gGpioDevice);
	   }

   }

   static jboolean gpioExists(JNIEnv* /* env */, jobject /* clazz */)
   {
	   if(gGpioModule && gGpioDevice)
		   return JNI_TRUE;
	   else
		   return JNI_FALSE;
   }

   static void SetGpioDirection(JNIEnv* env , jobject clazz  , int pin , int val)
   {
	   if(gGpioDevice)
	   {
		   int err = gGpioDevice->gp_set_direction(gGpioDevice , pin , val);
		   if(err != 0)
			   ALOGE("Gpio Module Failed to set Direction : %s " , strerror(-err));
	   }
	   else
		   ALOGW("No Gpio Module to set Direction.");
   }

   static void SetGpioValue(JNIEnv* env , jobject clazz  , int pin , int val)
   {
	   if(gGpioDevice)
	   {
		   int err = gGpioDevice->gp_set_value(gGpioDevice , pin , val);
		   if(err != 0)
			   ALOGE("Gpio Module Failed to set Value : %s " , strerror(-err));
	   }
	   else
		   ALOGW("No Gpio Module to set Value.");
   }

   static void GpioExport(JNIEnv* env , jobject clazz  , int pin)
   {
	   if(gGpioDevice)
	   {
		   int err = gGpioDevice->gp_export(gGpioDevice , pin);
		   if(err != 0)
			   ALOGE("Gpio Module Failed to Export : %s " , strerror(-err));
	   }
	   else
		   ALOGW("No Gpio Module to Export");
   }

   static void GpioUnExport(JNIEnv* env , jobject clazz  , int pin)
   {
	   if(gGpioDevice)
	   {
		   int err = gGpioDevice->gp_unexport(gGpioDevice , pin);
		   if(err != 0)
			   ALOGE("Gpio Module Failed to unExport : %s " , strerror(-err));
	   }
	   else
		   ALOGW("No Gpio Module to unExport");
   }


   static const JNINativeMethod method_table[] = {
		   {"gpioInit" , "()V" , (void*)gpioInit } ,
		   {"gpioExists" , "()Z" , (void*)gpioExists } ,
		   {"SetGpioDirection" , "(II)V" , (void*)SetGpioDirection } ,
		   {"SetGpioValue" , "(II)V" , (void*)SetGpioValue } ,
		   {"GpioExport" , "(I)V" , (void*)GpioExport } ,
		   {"GpioUnExport" , "(I)V" , (void*)GpioUnExport }
   };

   int register_android_server_GpioService(JNIEnv *env)
   {
       return jniRegisterNativeMethods(env, "com/android/server/GpioService",
               method_table, NELEM(method_table));
   }

};
