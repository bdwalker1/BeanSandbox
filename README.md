# BeanSandbox
A library for use with PunchThrough Design's LightBlue Bean and IOS app

## Methods

#### initializeValues()

    Used to initialize all control values to their defaults. This function is used
    in the constructor, but can also be called any time.  For instance, you may want to call this 
    function any time a new Bean connection is made so the internal values will match the 
    Sandbox control default values.

**Usage:** 

    BeanSandbox sbx;
    sbx.initializeValues();

#### autoUpdateSandbox( boolean bYesNo );

    Sets whether to send value updates to the LightBlue app's controls on a periodic basis.  
    If enabled the controls will be updated approximately every half second.

**Paramters:**

    (boolean) bYesNo - True to enable control updates. False to disable updates.

**Return Value:**

    (boolean) True if automatic control updates are enabled, otherwise false.

#### boolean autoUpdateSandbox();

    Retrieves the current auto control update setting.

**Return Value:**

    (boolean) True if automatic control updates are enabled, otherwise false.

#### getSliderValue( byte nSlider )

    Gets the current value of a specific slider.  Valid slider numbers are 1 through 6.  Any
    other slider number will return 0;

**Paramters:**

    (byte) nSlider - The slider whose value you wish to read. (1 to 6)

**Return Value:**

    (byte) The value of the specified slider.

**Usage:**

    BeanSandbox sbx
    byte nVolume;
    nVolume = sbx.getSliderValue(1);

#### setSliderValue( byte nSlider, byte nValue )

    Sets the value of a specified slider. Valid sliders are 1 through 6.

**Paramters:**

    (byte) nSlider - The slider whose value you wish to set. (1 to 6)
    (byte) nValue - Value to be assigned to slider. (1 to 255)

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

#### isChecked( byte nCheckbox )

    Returns the current status of specified checkbox.  Valid checkbox numbers are 1 through 6.  
    Any other checkbox number will return false.

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

#### setCheckbox( byte nCheckbox, boolean bChecked )

    Sets the value of a specified checkbox. Valid checkbox numbers are 1 through 6.

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

#### void setTouchpadMode( byte nMode )

#### byte getTouchpadX()

#### byte getTouchpadY()

#### boolean setTouchpadX( byte nValue )

#### boolean setTouchpadY( byte nValue )

#### boolean setTouchpad( byte nX, byte nY )

#### boolean isTouchpadActive()

#### void setPushButtonMode( byte nButton, byte nMode )

#### boolean isBtnPressed( byte nButton )

#### boolean setButton( byte nButton, boolean bPressed )
