# BeanSandbox
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
#### void setTouchpadMode( byte nMode )

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
#### byte getTouchpadX()

    Gets the current X-axis value for the touchpad.

**Return Value:**

    (byte) The current x-axis value. (0 to 255)

**Usage:**

    BeanSandbox sbx;
    byte nX = sbx.getTouchpadX();
    analogWrite( A0, nX );

___
#### byte getTouchpadY()

    Gets the current Y-axis value for the touchpad.

**Return Value:**

    (byte) The current y-axis value. (0 to 255)

**Usage:**

    BeanSandbox sbx;
    byte nY = sbx.getTouchpadY();
    analogWrite( A1, nY );

___
#### boolean setTouchpadX( byte nValue )

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
#### boolean setTouchpadY( byte nValue )

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
#### boolean setTouchpad( byte nX, byte nY )

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
#### boolean isTouchpadActive()

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
#### void setPushButtonMode( byte nButton, byte nMode )

___
#### boolean isBtnPressed( byte nButton )

___
#### boolean setButton( byte nButton, boolean bPressed )

___
