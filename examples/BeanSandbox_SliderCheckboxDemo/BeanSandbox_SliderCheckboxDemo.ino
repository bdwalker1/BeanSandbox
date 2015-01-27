/*
  This demo shows how the BeanSandbox library can be used to read/write to the LightBlue app's slider and checkbox controls.
  
  If checkbox 1 is checked, checkboxes 2, 3 and 4 will be checked and sliders 2, 3 and 4 will synchronize to slider 1.
  If checkbox 1 is not checked, checkboxes 2, 3 and 4 will be unchecked and all four sliders can be set independently.
  
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
      sbx.initializeValues();
    }
    // If checkbox 1 is checked make sure checkboxes 2, 3 and 4 are also checked, and synchronize sliders 2, 3 and 4 to slider 1
    if( sbx.isChecked(1) )
    {
      if(!sbx.isChecked(2))
        sbx.setCheckbox( 2, true );
      if(!sbx.isChecked(3))
        sbx.setCheckbox( 3, true );
      if(!sbx.isChecked(4))
        sbx.setCheckbox( 4, true );

      byte nSliderValue = sbx.getSliderValue(1);
      if( sbx.getSliderValue(2) != nSliderValue )
        sbx.setSliderValue( 2, nSliderValue );
      if( sbx.getSliderValue(3) != nSliderValue )
        sbx.setSliderValue( 3, nSliderValue );
      if( sbx.getSliderValue(4) != nSliderValue )
        sbx.setSliderValue( 4, nSliderValue );
    }
    // If checkbox 1 is not checked make sure checkboxes 2, 3 and 4 are also not checked
    if( !sbx.isChecked(1) )
    {
      if(sbx.isChecked(2))
        sbx.setCheckbox( 2, false );
      if(sbx.isChecked(3))
        sbx.setCheckbox( 3, false );
      if(sbx.isChecked(4))
        sbx.setCheckbox( 4, false );
    }

    // Give the Bean a slight rest
    Bean.sleep(50);
  }
}
