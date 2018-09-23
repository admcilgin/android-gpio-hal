package com.android.hello;

import com.android.hello.R;
import android.app.Activity;
import android.os.ServiceManager;
import android.os.Bundle;
import android.os.Gpio;
import android.os.RemoteException;
import android.util.Log;
import android.content.Context;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class Hello extends Activity implements OnClickListener {

	private final static String LOG_TAG = "com.android.gpio";
	
	private Gpio gpioservice = null;

	private EditText valueText = null;
        private EditText pinText = null;
	private Button setDirectionButton = null;
	private Button setValueButton = null;
	private Button exportButton = null;
        private Button unexportButton = null;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

	gpioservice = (Gpio) getSystemService(Context.GPIO_SERVICE);

        pinText = (EditText)findViewById(R.id.pin_edit_value);
        valueText = (EditText)findViewById(R.id.edit_value);
	setDirectionButton = (Button)findViewById(R.id.button_direction);
	setValueButton = (Button)findViewById(R.id.button_value);
	exportButton = (Button)findViewById(R.id.button_export);
        unexportButton = (Button)findViewById(R.id.button_unexport);

        setDirectionButton.setOnClickListener(this);
	setValueButton.setOnClickListener(this);
	exportButton.setOnClickListener(this);
        unexportButton.setOnClickListener(this);
         
        Log.i(LOG_TAG, "Gpio Activity Created");
    }
    
    @Override
    public void onClick(View v) {
    	if(v.equals(setDirectionButton)) {
    		  String text = valueText.getText().toString(); 
                  String pint = pinText.getText().toString(); 
    		  int val = Integer.parseInt(text);
                  int pin = Integer.parseInt(pint);
                  gpioservice.gpsetDirection(pin , val);		
    	}
    	else if(v.equals(setValueButton)) {
    		  String text = valueText.getText().toString(); 
                  String pint = pinText.getText().toString(); 
    		  int val = Integer.parseInt(text);
                  int pin = Integer.parseInt(pint);
                  gpioservice.gpsetValue(pin , val);
    	}
    	else if(v.equals(exportButton)) {
                 String pint = pinText.getText().toString(); 
                 int pin = Integer.parseInt(pint);
                 gpioservice.gpexport(pin);
    	}
    	else if(v.equals(unexportButton)) {
    	        String pint = pinText.getText().toString(); 
                int pin = Integer.parseInt(pint);
                gpioservice.gpunexport(pin);
    	}
    }
}
