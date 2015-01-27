/*
  This demo shows how the BeanSandbox library can be used to read/write to the LightBlue app's push button controls.
  
  By using the library to set/clear the push buttons you can use the push buttons as virtual LEDs.

  Button 1 will toggle the red of the LED.
  Button 2 will toggle the green of the LED.
  Button 3 will toggle the blue of the LED.
  Button 4 will set slider 6 to the Bean's current temperature while pressed. Slider 6 will be reset to 0 when button 4 is released.

  When button 5 is pressed, button 9 will be turned on and button 13 off.  When button 5 is released, button 9 will be turned off and button 13 will be turned on.
  
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

  // Set buttons 1, 2 and 3 to toggle mode
  sbx.setPushButtonMode( 1, SBX_BTNMODE_TOGGLE );
  sbx.setPushButtonMode( 2, SBX_BTNMODE_TOGGLE );
  sbx.setPushButtonMode( 3, SBX_BTNMODE_TOGGLE );
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

    // Set the onboard LED based on buttons 1, 2 and 3
    byte nRed = 0;
    byte nGreen = 0;
    byte nBlue = 0;
    if(sbx.isBtnPressed(1))
    {
      nRed = 60;
    }
    if(sbx.isBtnPressed(2))
    {
      nGreen = 150;
    }
    if(sbx.isBtnPressed(3))
    {
      nBlue = 255;
    }
    Bean.setLed( nRed, nGreen, nBlue );
    
    // If button 4 is pressed set slider 6 to temp reading
    if(sbx.isBtnPressed(4))
    {
      if( sbx.getSliderValue( 6 ) == 0 )
        sbx.setSliderValue( 6, Bean.getTemperature() );
    }
    else
    {
      if( sbx.getSliderValue( 6 ) != 0 )
        sbx.setSliderValue( 6, 0 );
    }

    // If button 5 is pressed, set button 9 on and button 13 off
    if(sbx.isBtnPressed(5))
    {
      if(!sbx.isBtnPressed(9))
        sbx.setButton(9, true);
      if(sbx.isBtnPressed(13))
        sbx.setButton(13, false);
    }
    else
    // If button 5 is not pressed, set button 9 on and button 13 off
    {
      if(sbx.isBtnPressed(9))
        sbx.setButton(9, false);
      if(!sbx.isBtnPressed(13))
        sbx.setButton(13, true);
    }

    // Give the Bean a slight rest
    Bean.sleep(50);
  }
}

