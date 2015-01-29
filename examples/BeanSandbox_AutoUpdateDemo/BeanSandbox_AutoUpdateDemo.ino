/*
  This demo shows how using the auto-update option can allow control changes to be reflected in the LightBluw Sandbox
  even when the control isn't on the active page when the value is changed.
  
  For this demo, the x-axis value of the touchpad will be set based on slider 1's value and the y-axis value of the touchad
  will be set based on slider 2's value.

*/

#include <BeanSandbox.h>

BeanSandbox sbx;  // Object for interacting with LightBlue sandbox controls
boolean bConnected = false;  // Flag for determining if we have an existing connection or a new connection when we start our loop()

void setup()
{
  // Initialize serial communications at 57600bps
  Serial.begin(57600);
  
  // Enable the wake on connect so the Arduino will wake upon BLE connection rather than waiting for serial input
  Bean.enableWakeOnConnect( true );

  // Enable the auto-update feature  
  sbx.autoUpdateSandbox( true );
  
}

void loop()
{
  // Check BLE connection state  
  if(!Bean.getConnectionState())
  {
    // If we are not connected, just give a heartbeat blink and sleep for 5 minutes
    Bean.setLed( 0, 180, 0 );
    Bean.sleep(100);
    Bean.setLed( 0, 0, 0 );
    Bean.sleep(300000);
    bConnected = false;
  }
  else
  {
    // If we are connected, begin processing
    if(!bConnected)
    {
      // If this is our first time through loop since connecting, initialize the control values
      bConnected = true;
    }
    // Check slider 1's value
    byte nValue = sbx.getSliderValue(1);
    // If the touchpad x-axis is not equal to slider 1's value ...
    if(sbx.getTouchpadX()!=nValue)
    {
      // ... update touchpad x-axis.
      sbx.setTouchpadX( nValue );
    }
    // Check slider 2's value
    nValue = sbx.getSliderValue(2);
    // If the touchpad y-axis is not equal to slider 2's value ...
    if(sbx.getTouchpadY()!=nValue)
    {
      // ... update touchpad x-axis.
      sbx.setTouchpadY( nValue );
    }

   // Give the Bean a slight rest
    Bean.sleep(50);
  }
}
