/*
  This demo shows how the BeanSandbox library can be used to read values from the the 
  LightBlue app's touchpad, checkbox 5 and slider 5 to control the Bean's onboard LED.
  
  Slider 5 controls the red intensity of the LED.
  Touchpad X-axis controls the green intensity of the LED.
  Touchapd Y-axis controls the blue intensity of the LED.
  
  If checkbox 5 is checked, changes to the touchpad will affect the LED as you slide your finger around.
  If checkbox 5 is not checked, the LED will only change based on new touchpad values when you lift your finger from the touchpad.
  
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

  // Initialize the touchpad to immediate mode
  sbx.setTouchpadMode( SBX_PADMODE_IMMEDIATE );
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

    // Set the touchpad mode based on checkbox 5
    if(sbx.isChecked(5))
    {
      sbx.setTouchpadMode( SBX_PADMODE_IMMEDIATE );
    }
    else
    {
      sbx.setTouchpadMode( SBX_PADMODE_ONRELEASE );
    }

    // Set the onboard LED based on slider 5 for red intensity, touchpad X-axis for green intensity and touchpad Y-axis for blue intensity
    byte nRed = sbx.getSliderValue(5);
    byte nGreen = sbx.getTouchpadX();
    byte nBlue = sbx.getTouchpadY();
    Bean.setLed( nRed, nGreen, nBlue );

    // Give the Bean a slight rest
    Bean.sleep(50);
  }
}

