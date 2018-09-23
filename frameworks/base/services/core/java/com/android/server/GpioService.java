package com.android.server;

import android.os.IGpioService;
import android.content.Context;

public class GpioService extends IGpioService.Stub {
	
	private static final String TAG = "GpioService";
	
	private Context mContext;
	
	native static void gpioInit();
	native static void GpioExport(int pin);
	native static void GpioUnExport(int pin);
	native static void SetGpioDirection(int pin, int direction);
	native static void SetGpioValue(int pin , int value);
	native static boolean gpioExists();
	
	public GpioService() {
		
	}

	public GpioService(Context context) {
		mContext = context;
		/*
		mContext.enforceCallingOrSelfPermission(
                android.Manifest.permission.GPIO,
                "cancelVibrate");
                */
		gpioInit();
	}
	
	public void systemReady() {}
	
	@Override
    public void GpioServiceSetDirection(int pin , int direction)
    {
		/*
        mContext.enforceCallingOrSelfPermission(
                android.Manifest.permission.GPIO,
                "cancelVibrate");
                                */
		SetGpioDirection(pin, direction);
    }
    
	@Override
    public void GpioServiceSetValue(int pin , int value)
    {
		/*
		mContext.enforceCallingOrSelfPermission(
                android.Manifest.permission.GPIO,
                "cancelVibrate");
                                                */
		SetGpioValue(pin , value);
    }
	
	@Override
	public void GpioServiceExport(int pin)
	{
		/*
		mContext.enforceCallingOrSelfPermission(
                android.Manifest.permission.GPIO,
                "cancelVibrate");
                */
		GpioExport(pin);
	}
    
	@Override
	public void GpioServiceunExport(int pin)
	{
		/*
		mContext.enforceCallingOrSelfPermission(
                android.Manifest.permission.GPIO,
                "cancelVibrate");
                */
		GpioUnExport(pin);
	}

}