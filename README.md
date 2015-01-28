# BeanSandbox
A library for use with PunchThrough Design's LightBlue Bean and IOS app

## Methods

### void initializeValues()

This function is used to initialize all control values to their defaults.

**Usage:**

`BeanSandbox sbx;

sbx.initializeValues();`

### byte getSliderValue( byte nSlider )

### boolean setSliderValue( byte nSlider, byte nValue )

### boolean isChecked( byte nCheckbox )

### boolean setCheckbox( byte nCheckbox, boolean bChecked )

### void setTouchpadMode( byte nMode )

### byte getTouchpadX()

### byte getTouchpadY()

### boolean setTouchpadX( byte nValue )

### boolean setTouchpadY( byte nValue )

### boolean setTouchpad( byte nX, byte nY )

### boolean isTouchpadActive()

### void setPushButtonMode( byte nButton, byte nMode )

### boolean isBtnPressed( byte nButton )

### boolean setButton( byte nButton, boolean bPressed )
