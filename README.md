# BeanSandbox

This library is shared under the GNU Public License. Please see the `GNUPublicLicense.txt` file in this repository or http://www.gnu.org/licenses/gpl.txt for details.

A library for use with PunchThrough Design's LightBlue Bean and IOS app

## Methods

#### initializeValues()

    Used to initialize all control values to their defaults. This function 
    is used in the constructor, but can also be called any time. For 
    instance, you may want to call this function any time a new Bean 
    connection is made so the internal values will match the Sandbox 
    control default values.

**Usage:** 

    BeanSandbox sbx;
    sbx.initializeValues();
___
#### autoUpdateSandbox( boolean bYesNo );

    Sets whether to send value updates to the LightBlue app's controls on a 
    periodic basis. If enabled the controls will be updated approximately 
    every half second.

**Paramters:**

    (boolean) bYesNo - True to enable control updates. False to disable updates.

**Return Value:**

    (boolean) True if automatic control updates are enabled, otherwise false.
___
#### boolean autoUpdateSandbox();

    Retrieves the current auto control update setting.

**Return Value:**

    (boolean) True if automatic control updates are enabled, otherwise false.
___
#### getSliderValue( byte nSlider )

    Gets the current value of a specific slider.  Valid slider numbers are 1 
    through 6. Any other slider number will return 0;

**Paramters:**

    (byte) nSlider - The slider whose value you wish to read. (1 to 6)

**Return Value:**

    (byte) The value of the specified slider. (0 to 255)

**Usage:**

    BeanSandbox sbx
    byte nVolume;
    nVolume = sbx.getSliderValue(1);
___
#### setSliderValue( byte nSlider, byte nValue )

    Sets the value of a specified slider. Valid sliders are 1 through 6.

**Paramters:**

    (byte) nSlider - The slider whose value you wish to set. (1 to 6)
    (byte) nValue - Value to be assigned to slider. (0 to 255)

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    BeanSandbox sbx
    byte nVolume = 100;
    boolean bVolumeChanged = false;
    if(sbx.setSliderValue(1,nVolume))
    {
      // Volume slider was set
      bVolumeChanged = true;
    }
___
#### isChecked( byte nCheckbox )

    Returns the current status of specified checkbox.  Valid checkbox 
    numbers are 1 through 6. Any other checkbox number will return false.

**Paramters:**

    (byte) nCheckbox - The checkbox whose value you wish to read. (1 to 6)

**Return Value:**

    (boolean) True if the checkbox is currently checked, otherwise false.

**Usage:**

    BeanSandbox sbx
    if(sbx.isChecked(1))
    {
      // Checkbox 1 is checked, write HIGH to pin 1
      digitalWrite(1,HIGH);
    }
    else
    {
      // Checkbox 1 is not checked, write LOW to pin 1
      digitalWrite(1,LOW);
    }
___
#### setCheckbox( byte nCheckbox, boolean bChecked )

    Sets the value of a specified checkbox. Valid checkbox numbers are 
    1 through 6.

**Paramters:**

    (byte) nCheckbox - The checkbox whose value you wish to set. (1 to 6)
    (boolean) bChecked - True to set the checkbox checked. False to set unchecked.

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    // Checkbox 2 will be synchronized to checkbox 1
    BeanSandbox sbx
    if(sbx.isChecked(1))
    {
      sbx.setCheckbox(2,true);
    }
    else
    {
      sbx.setCheckbox(2,false);
    }
___
#### setTouchpadMode( byte nMode )

    Sets the mode the touchpad operates in.  In immediate mode (the 
    default mode) the touchpad values will update as the user slides 
    their finger around the touchpad.  In on-release mode the touchpad
    values will only update when the user lifts their finger from 
    the touchpad.

**Paramters:**

    (byte) nMode - nMode should be SBX_PADMODE_IMMEDIATE or SBX_PADMODE_ONRELEASE.

**Usage:**

    BeanSandbox sbx;
    sbx.setTouchpadMode( SBX_PADMODE_ONRELEASE );
___
#### getTouchpadX()

    Gets the current X-axis value for the touchpad.

**Return Value:**

    (byte) The current x-axis value. (0 to 255)

**Usage:**

    BeanSandbox sbx;
    byte nX = sbx.getTouchpadX();
    analogWrite( A0, nX );

___
#### getTouchpadY()

    Gets the current Y-axis value for the touchpad.

**Return Value:**

    (byte) The current y-axis value. (0 to 255)

**Usage:**

    BeanSandbox sbx;
    byte nY = sbx.getTouchpadY();
    analogWrite( A1, nY );

___
#### setTouchpadX( byte nValue )

    Sets the x-axis of the touchpad.

**Parameters:**

    (byte) nValue - The value to be assigned. (0 to 255)

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    BeanSandbox sbx;
    byte nRand = (byte) random(0,256);
    sbx.setTouchpadX( nRand );
___
#### setTouchpadY( byte nValue )

    Sets the y-axis of the touchpad.

**Parameters:**

    (byte) nValue - The value to be assigned. (0 to 255)

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    BeanSandbox sbx;
    byte nRand = (byte) random(0,256);
    sbx.setTouchpadY( nRand );
___
#### setTouchpad( byte nX, byte nY )

    Sets both x-axis and y-axis touchpad values at the same time.

**Parameters:**

    (byte) nX - The x-axis value to be assigned. (0 to 255)
    (byte) nY - The y-axis value to be assigned. (0 to 255)

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    BeanSandbox sbx;
    byte nRandX = (byte) random(0,256);
    byte nRandY = (byte) random(0,256);
    sbx.setTouchpad( nRandX, nRandY );
___
#### isTouchpadActive()

    Indicates whether the touchpad is currently being touched.

**Return Value:**

    (boolean) True if the touchpad is being touched, otherwise false.

**Usage:**

    BeanSandbox sbx;
    if(sbx.isTouchpadActive())
    {
      Bean.setLed( 255, 0, 0 );
    }
    else
    {
      Bean.setLed( 0, 0, 0 );
    }
___
#### setPushButtonMode( byte nButton, byte nMode )

    Sets the mode a push button operates in. By default the buttons operate 
    in immediate mode where they are like a momentary push button -- active 
    only while being touched.  In toggle mode the button will act as a 
    push-on/push-off switch where the value will be go back and forth 
    between on and off with each touch.

**Paramters:**

    (byte) nButton - The button number to set the mode for. (1 to 16)
    (byte) nMode - nMode should be SBX_BTNMODE_IMMEDIATE, SBX_BTNMODE_TOGGLE 
                   or SBX_BTNMODE_LED.

**Usage:**

    BeanSandbox sbx;
    // Set buttons 1-4 to LED mode.
    sbx.setPushButtonMode( 1, SBX_BTNMODE_LED );
    sbx.setPushButtonMode( 2, SBX_BTNMODE_LED );
    sbx.setPushButtonMode( 3, SBX_BTNMODE_LED );
    sbx.setPushButtonMode( 4, SBX_BTNMODE_LED );
    // Set buttons 5-8 to toggle mode.
    sbx.setPushButtonMode( 5, SBX_BTNMODE_TOGGLE );
    sbx.setPushButtonMode( 6, SBX_BTNMODE_TOGGLE );
    sbx.setPushButtonMode( 7, SBX_BTNMODE_TOGGLE );
    sbx.setPushButtonMode( 8, SBX_BTNMODE_TOGGLE );
___
#### isBtnPressed( byte nButton )

    Returns the current status of specified button.  Valid button 
    numbers are 1 through 16. Any other button number will return false.

**Paramters:**

    (byte) nButton - The button whose value you wish to read. (1 to 16)

**Return Value:**

    (boolean) True if the button is currently pressed, otherwise false.

**Usage:**

    BeanSandbox sbx
    if(sbx.isBtnPressed(1))
    {
      // Button 1 is pressed, write HIGH to pin 1
      digitalWrite(1,HIGH);
    }
    else
    {
      // Button 1 is not pressed, write LOW to pin 1
      digitalWrite(1,LOW);
    }
___
#### setButton( byte nButton, boolean bPressed )

    Sets the value of a specified button. Valid button numbers are 
    1 through 16.

**Paramters:**

    (byte) nButton - The button whose value you wish to set. (1 to 16)
    (boolean) bPressed - True to set the button pressed. False to set unpressed.

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    // Button 1 will be turned on and off based on the value of digital pin 0
    BeanSandbox sbx
    if(digitalRead(0)==HIGH)
    {
      sbx.setButton(1,true);
    }
    else
    {
      sbx.setButton(1,false);
    }
___
#### isLedOn( byte nLed )

    This is a wrapper function for isBtnPressed() for buttons being used as LEDs.
    Returns the current status of specified virtual LED.  Valid LED 
    numbers are 1 through 16. Any other LED number will return false. Also, if
    specified button is not set to LED mode this function will return false.

**Paramters:**

    (byte) nLed - The LED(button) whose status you wish to read. (1 to 16)

**Return Value:**

    (boolean) True if the LED is currently set to be on, otherwise false.

**Usage:**

    BeanSandbox sbx
    sbx.setPushButtonMode(1,SBX_BTNMODE_LED);
    // If LED 1 is on, turn it off.
    if(sbx.isLedOn(1))
    {
      sbx.setLed(1, false);
    }
___
#### setLed( byte nLed, boolean bOnOff )

    This is a wrapper function for setButton() for buttons being used as LEDs.
    Turns virtual LED (button) on or off. Valid LED numbers are 
    1 through 16.

**Paramters:**

    (byte) nLed - The LED you wish to set. (1 to 16)
    (boolean) bOnOff - True to turn the LED on. False to turn the LED off.

**Return Value:**

    (boolean) True if the function succeeds, otherwise false.

**Usage:**

    // Virtual LED 1 will be turned on and off based on the value of digital pin 0
    BeanSandbox sbx
    sbx.setPushButtonMode(1,SBX_BTNMODE_LED);
    if(digitalRead(0)==HIGH)
    {
      sbx.setLed(1,true);
    }
    else
    {
      sbx.setLed(1,false);
    }
___
