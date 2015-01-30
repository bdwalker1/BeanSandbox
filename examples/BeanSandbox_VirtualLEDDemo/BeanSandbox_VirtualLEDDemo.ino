/*
  This demo shows how you can use the LightBlue IOS app's buttons as virtual LEDs.
  
  For this demo, the value of slider 6 (the slider on the push button screen) will 
  be displayed on buttons 1-8 in binary.  Communication is not instantaneous, so you'll
  notice some lag time in the LEDs catching up to the slider changes.

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
  sbx.autoUpdateSandbox( false );
  
  sbx.setPushButtonMode(1, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(2, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(3, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(4, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(5, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(6, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(7, SBX_BTNMODE_LED);
  sbx.setPushButtonMode(8, SBX_BTNMODE_LED);

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
      // If auto-update is not active, initialize control values
      if(!sbx.autoUpdateSandbox())
      {
        sbx.initializeValues();
      }
    }

    byte nValue = sbx.getSliderValue(6);
    for(int i=0; i<8; i++)
    {
      if( (nValue >> i) & 0x01 )
      {
        if(!sbx.isLedOn(8-i)) { sbx.setLed(8-i,true); }
      }
      else
      {
        if(sbx.isLedOn(8-i)) { sbx.setLed(8-i,false); }
      }
    }
    
   // Give the Bean a slight rest
    Bean.sleep(50);
  }
}
