#include <BeanSandbox.h>

// Define constants for control numbers
const byte SBX_SLIDER1 = 0x00;
const byte SBX_SLIDER2 = 0x02;
const byte SBX_SLIDER3 = 0x04;
const byte SBX_SLIDER4 = 0x06;
const byte SBX_SLIDER5 = 0x0B;
const byte SBX_SLIDER6 = 0x1D;
const byte SBX_CHKBOX1 = 0x01;
const byte SBX_CHKBOX2 = 0x03;
const byte SBX_CHKBOX3 = 0x05;
const byte SBX_CHKBOX4 = 0x07;
const byte SBX_CHKBOX5 = 0x0C;
const byte SBX_CHKBOX6 = 0x1E;
const byte SBX_PADX = 0x08;
const byte SBX_PADY = 0x09;
const byte SBX_PADTOUCH = 0x0A;
const byte SBX_BTN1 = 0x0D;
const byte SBX_BTN2 = 0x0E;
const byte SBX_BTN3 = 0x0F;
const byte SBX_BTN4 = 0x10;
const byte SBX_BTN5 = 0x11;
const byte SBX_BTN6 = 0x12;
const byte SBX_BTN7 = 0x13;
const byte SBX_BTN8 = 0x14;
const byte SBX_BTN9 = 0x15;
const byte SBX_BTN10 = 0x16;
const byte SBX_BTN11 = 0x17;
const byte SBX_BTN12 = 0x18;
const byte SBX_BTN13 = 0x19;
const byte SBX_BTN14 = 0x1A;
const byte SBX_BTN15 = 0x1B;
const byte SBX_BTN16 = 0x1C;

BeanSandbox::BeanSandbox()
{
  // Serial timeout needs to be very short to prevent lag
  Serial.setTimeout(5);

  // Setup default modes
  _nTouchpadMode = SBX_PADMODE_IMMEDIATE;
  for(int i=0;i<16;i++) { _nPushButtonMode[i] = SBX_BTNMODE_IMMEDIATE; }

  // Setup default values
  initializeValues();

  // Initialize last processed time
  _nLastProcessed = 0;

  _nLastControlUpdate = 0;
}

BeanSandbox::~BeanSandbox()
{
  
}

void BeanSandbox::initializeValues()
{
  // Setup default values
  for(int i=0;i<6;i++) { _nSlider[i] = 0; }
  for(int i=0;i<6;i++) { _bCheckbox[i] = true; }
  _bTouchpadTouch = false;
  _nTouchpadValuesImmediate[0] = 0; _nTouchpadValuesImmediate[1] = 0;
  _nTouchpadValuesOnRelease[0] = 0; _nTouchpadValuesOnRelease[1] = 0;
  for(int i=0;i<16;i++) { _bPushButtonImmediate[i] = false; _bPushButtonToggle[i] = false; }
}

boolean BeanSandbox::autoUpdateSandbox( boolean bYesNo )
{
    _bAutoUpdateSandbox = bYesNo;
    return _bAutoUpdateSandbox;
}

boolean BeanSandbox::autoUpdateSandbox()
{
    return _bAutoUpdateSandbox;
}

void BeanSandbox::_processSerial()
{
  size_t length = 64;
  char _buffer[64];
  unsigned long nNow = millis();
  boolean bButtonsUpdated = false;

  // To prevent hammering the Serial reads, we'll only process new serial input 
  // if it has been more than 30 milliseconds since our last check.
  if( (_nLastProcessed > nNow) || ((nNow-_nLastProcessed) > 30) )
  {
    // Update last processed time
    _nLastProcessed = nNow;

    // Read any waiting serial input
    length = Serial.readBytes(_buffer, length);
  
    // If we read anything, process it.
    while ( length > 0 )
    {
      // Loop through the buffer two bytes at a time. 
      for (int i=0; i<(length-1); i+=2)
      {
        // The first byte is control number; the second byte is the control value.
        byte nControl = _buffer[i];
        byte nValue = _buffer[i+1];
        
        // Process the current control
        switch(nControl)
        {
          case SBX_SLIDER1:
          {
            // Set the slider value
            _nSlider[0] = nValue;
            break;
          }
          case SBX_SLIDER2:
          {
            // Set the slider value
            _nSlider[1] = nValue;
            break;
          }
          case SBX_SLIDER3:
          {
            // Set the slider value
            _nSlider[2] = nValue;
            break;
          }
          case SBX_SLIDER4:
          {
            // Set the slider value
            _nSlider[3] = nValue;
            break;
          }
          case SBX_SLIDER5:
          {
            // Set the slider value
            _nSlider[4] = nValue;
            break;
          }
          case SBX_SLIDER6:
          {
            // Set the slider value
            _nSlider[5] = nValue;
            break;
          }
          case SBX_CHKBOX1:
          {
            // Update the checkbox's value.
            if(nValue==1)
            {
              _bCheckbox[0] = true;
            }
            else
            {
              _bCheckbox[0] = false;
            }
            break;
          }
          case SBX_CHKBOX2:
          {
            // Update the checkbox's value.
            if(nValue==1)
            {
              _bCheckbox[1] = true;
            }
            else
            {
              _bCheckbox[1] = false;
            }
            break;
          }
          case SBX_CHKBOX3:
          {
            // Update the checkbox's value.
            if(nValue==1)
            {
              _bCheckbox[2] = true;
            }
            else
            {
              _bCheckbox[2] = false;
            }
            break;
          }
          case SBX_CHKBOX4:
          {
            // Update the checkbox's value.
            if(nValue==1)
            {
              _bCheckbox[3] = true;
            }
            else
            {
              _bCheckbox[3] = false;
            }
            break;
          }
          case SBX_CHKBOX5:
          {
            // Update the checkbox's value.
            if(nValue==1)
            {
              _bCheckbox[4] = true;
            }
            else
            {
              _bCheckbox[4] = false;
            }
            break;
          }
          case SBX_CHKBOX6:
          {
            // Update the checkbox's value.
            if(nValue==1)
            {
              _bCheckbox[5] = true;
            }
            else
            {
              _bCheckbox[5] = false;
            }
            break;
          }
          case SBX_PADX:
          {
            // Update the touchpad's X value
            _nTouchpadValuesImmediate[0] = nValue;
            break;
          }
          case SBX_PADY:
          {
            // Update the touchpad's Y value
            _nTouchpadValuesImmediate[1] = nValue;
            break;
          }
          case SBX_PADTOUCH:
          {
            // If touchpad is touched...
            if(nValue==1)
            {
              // ... set touch to true.
              _bTouchpadTouch = true;
            }
            else
            {
              // If touchpad was released, set touch to false.
              _bTouchpadTouch = false;
              // And update the touchpad's onrelease valies.
              _nTouchpadValuesOnRelease[0] = _nTouchpadValuesImmediate[0]; _nTouchpadValuesOnRelease[1] = _nTouchpadValuesImmediate[1];
            }
            break;
          }
          case SBX_BTN1:
          case SBX_BTN2:
          case SBX_BTN3:
          case SBX_BTN4:
          case SBX_BTN5:
          case SBX_BTN6:
          case SBX_BTN7:
          case SBX_BTN8:
          case SBX_BTN9:
          case SBX_BTN10:
          case SBX_BTN11:
          case SBX_BTN12:
          case SBX_BTN13:
          case SBX_BTN14:
          case SBX_BTN15:
          case SBX_BTN16:
          {
            bButtonsUpdated = true;
            // Set the index for the current push button
            int nIndex = nControl - SBX_BTN1;
            // Process based on the button’s mode setting
            switch(_nPushButtonMode[nIndex])
            {
              // If the button’s mode is SBX_BTNMODE_LED ignore presses from the Sandbox.
              case SBX_BTNMODE_LED:
              {
                break;
              }
              // Otherwise, set value as appropriate.
              default:
              {
                // If the button is pressed...
                if(nValue==0)
                {
                  // ... update immediate value to true ...
                  _bPushButtonImmediate[nIndex] = true;
                  // ... and toggle the button's toggle value.
                  _bPushButtonToggle[nIndex] = !(_bPushButtonToggle[nIndex]);
                }
               else
                {
                  // If the button was released update the immediate value to false.
                  _bPushButtonImmediate[nIndex] = false;
                }
              }
            }
            break;
          }
          default:
          {
            break;
          }
        }
      }
      // Read any additional waiting serial input
      length = Serial.readBytes(_buffer, length);
    }

    // Update sandbox controls if enabled
    if(_bAutoUpdateSandbox)
    {
      if( (_nLastControlUpdate > nNow) || ( (nNow-_nLastControlUpdate) > 500 ) )
      {
        _updateAllControls();
        _nLastControlUpdate = nNow;
      }
    }
    else
    {
      char sendBuffer[32];
      uint8_t length = 0;

      // If auto-update is not enabled, at least update values for any buttons set to toggle that may have changed
      if( bButtonsUpdated )
      {
        for(int i=1; i<=16; i++)
        {
          if( _nPushButtonMode[i-1] == SBX_BTNMODE_TOGGLE )
          {
            sendBuffer[length] = i+12;
            sendBuffer[length+1] = (byte) _bPushButtonToggle[i-1];
            length += 2;
          }
        }
      }

      // Always update buttons set to LED mode as long as the button isn’t currently being 
      for(int i=1; i<=16; i++)
      {
        if( _nPushButtonMode[i-1] == SBX_BTNMODE_LED )
        {
          sendBuffer[length] = i+12;
          sendBuffer[length+1] = (byte) _bPushButtonImmediate[i-1];
          length += 2;
        }
      }

      // If we put data in the buffer, send it
      if(length>0)
      {
        // Send the info to the sandbox
        Serial.write( (uint8_t*) sendBuffer, length );
        delay(10);
        Bean.sleep(50);
      }
    }
  }
}

byte BeanSandbox::getSliderValue( byte nSlider )
{
  // Process serial input
  _processSerial();
  // If slider number is not 1-6 ...
  if( (nSlider<1) || (nSlider>6) )
  {
    // ... return zero.
    return 0;
  }
  // Otherwise return the correct slider value.
  return _nSlider[nSlider-1];
}

boolean BeanSandbox::setSliderValue( byte nSlider, byte nValue )
{
  // Default return value to false
  boolean bReturnValue = false;  

  // If slider number is valid (1-6) ...
  if( (nSlider>=1) && (nSlider<=6) )
  {
    // ... set the appropriate control number.
    byte nControl = 255;
    switch(nSlider)
    {
      case 1:
      {
        nControl = SBX_SLIDER1;
        break;
      }
      case 2:
      {
        nControl = SBX_SLIDER2;
        break;
      }
      case 3:
      {
        nControl = SBX_SLIDER3;
        break;
      }
      case 4:
      {
        nControl = SBX_SLIDER4;
        break;
      }
      case 5:
      {
        nControl = SBX_SLIDER5;
        break;
      }
      case 6:
      {
        nControl = SBX_SLIDER6;
        break;
      }
    }
    if(nControl!=255)
    {
      // ... try to send the value
      bReturnValue = _sendControlValueToBean( nControl, nValue );
      // If success ... 
      if(bReturnValue)
        // ... store the new status in our array.
        _nSlider[nSlider-1] = nValue;
    }
  }
  return bReturnValue;
}

boolean BeanSandbox::isChecked( byte nCheckbox )
{
  // Process serial input
  _processSerial();
  // If checkbox number is not 1-6 ...
  if( (nCheckbox<1) || (nCheckbox>6) )
  {
    // ... return false.
    return false;
  }
  // Otherwise return the correct checkbox value.
  return _bCheckbox[nCheckbox-1];
}

boolean BeanSandbox::setCheckbox( byte nCheckbox, boolean bChecked )
{
  // Default return value to false
  boolean bReturnValue = false;  

  // If checkbox number is valid (1-6) ...
  if( (nCheckbox>=1) && (nCheckbox<=6) )
  {
    // ... set the appropriate control number.
    byte nControl = 255;
    switch(nCheckbox)
    {
      case 1:
      {
        nControl = SBX_CHKBOX1;
        break;
      }
      case 2:
      {
        nControl = SBX_CHKBOX2;
        break;
      }
      case 3:
      {
        nControl = SBX_CHKBOX3;
        break;
      }
      case 4:
      {
        nControl = SBX_CHKBOX4;
        break;
      }
      case 5:
      {
        nControl = SBX_CHKBOX5;
        break;
      }
      case 6:
      {
        nControl = SBX_CHKBOX6;
        break;
      }
    }
    // Set Value based on boolean input
    byte nValue = 0;
    if(bChecked)
    {
      nValue = 1;
    }
    if(nControl!=255)
    {
      // ... try to send the value
      bReturnValue = _sendControlValueToBean( nControl, nValue );
      // If success ... 
      if(bReturnValue)
        // ... store the new status in our array.
        _bCheckbox[nCheckbox-1] = bChecked;
    }
  }
  return bReturnValue;
}

void BeanSandbox::setTouchpadMode( byte nMode )
{
  switch(nMode)
  {
    // If mode is immediate or on-release set the button's mode value.
    case SBX_PADMODE_IMMEDIATE:
    case SBX_PADMODE_ONRELEASE:
    {
      _nTouchpadMode = nMode;
      break;
    }
    // If the mode passed in was invalid, do nothing.
    default:
    {
      break;
    }
  }
}

byte BeanSandbox::getTouchpadX()
{
  // Process serial input
  _processSerial();
  // Initialize the return value to the x-axis immediate value.
  byte nReturnValue = _nTouchpadValuesImmediate[0];
  // If the touchpad is set to on-release mode ...
  if( _nTouchpadMode == SBX_PADMODE_ONRELEASE )
  {
    // ... update the return value to the x-axis on-release value.
    nReturnValue = _nTouchpadValuesOnRelease[0];
  }
  return nReturnValue;
}

byte BeanSandbox::getTouchpadY()
{
  // Process serial input
  _processSerial();
  // Initialize the return value to the y-axis immediate value.
  byte nReturnValue = _nTouchpadValuesImmediate[1];
  // If the touchpad is set to on-release mode ...
  if( _nTouchpadMode == SBX_PADMODE_ONRELEASE )
  {
    // ... update the return value to the y-axis on-release value.
    nReturnValue = _nTouchpadValuesOnRelease[1];
  }
  return nReturnValue;
}

boolean BeanSandbox::setTouchpadX( byte nValue )
{
  boolean bReturnValue = false;
  bReturnValue = _sendControlValueToBean( SBX_PADX, nValue );
  if(bReturnValue)
  {
    _nTouchpadValuesImmediate[0] = nValue;
    _nTouchpadValuesOnRelease[0] = nValue;
  }
  return bReturnValue;
}

boolean BeanSandbox::setTouchpadY( byte nValue )
{
  boolean bReturnValue = false;
  bReturnValue = _sendControlValueToBean( SBX_PADY, 255-nValue );
  if(bReturnValue)
  {
    _nTouchpadValuesImmediate[1] = nValue;
    _nTouchpadValuesOnRelease[1] = nValue;
  }
  return bReturnValue;
}

boolean BeanSandbox::setTouchpad( byte nX, byte nY )
{
  boolean bReturnValue = ( setTouchpadX( nX ) && setTouchpadY( nY ) );
  return bReturnValue;
}

boolean BeanSandbox::isTouchpadActive()
{
  // Process serial input
  _processSerial();
  return _bTouchpadTouch;
}

void BeanSandbox::setPushButtonMode( byte nButton, byte nMode )
{
  // If we have a valid button number (1-16) ...
  if( (nButton>=1) && (nButton<=16) )
  {
    switch(nMode)
    {
      // If mode is immediate or toggle set the button's mode value.
      case SBX_BTNMODE_IMMEDIATE:
      case SBX_BTNMODE_TOGGLE:
      case SBX_BTNMODE_LED:
      {
        _nPushButtonMode[nButton-1] = nMode;
        break;
      }
      // If the mode passed in was invalid, do nothing.
      default:
      {
        break;
      }
    }
  }
}

boolean BeanSandbox::isBtnPressed( byte nButton )
{
  // Process serial input
  _processSerial();
  // Initialize return value to false.
  boolean bReturnValue = false;
  // If we have a valid button number (1-16)
  if( (nButton>=1) && (nButton<=16) )
  {
    // If the button's mode is toggle ...
    if(_nPushButtonMode[nButton-1]==SBX_BTNMODE_TOGGLE)
    {
      // ... return the button's current toggle value.
      bReturnValue = _bPushButtonToggle[nButton-1];
    }
    else
    {
      // Otherwise return the button's current immediate value.
      bReturnValue = _bPushButtonImmediate[nButton-1];
    }
  }
  return bReturnValue;
}

boolean BeanSandbox::setButton( byte nButton, boolean bPressed )
{
  // Default return value to false
  boolean bReturnValue = false;  

  // If button number is valid (1-16) ...
  if( (nButton>=1) && (nButton<=16) )
  {
    // ... set the appropriate control number.
    byte nControl = SBX_BTN1+(nButton-1);
    // Set Value based on boolean input
    byte nValue = 0;
    if(bPressed)
    {
      nValue = 1;
    }
    // ... try to send the value
    bReturnValue = _sendControlValueToBean( nControl, nValue );
    // If success ... 
    if(bReturnValue)
    {
      // ... store the new status in our arrays.
      _bPushButtonImmediate[nButton-1] = bPressed;
      if(bPressed && (_nPushButtonMode[nButton-1] == SBX_BTNMODE_TOGGLE) )
      {
        _bPushButtonToggle[nButton-1] = !_bPushButtonToggle[nButton-1];
      }
      else
      {
        _bPushButtonToggle[nButton-1] = bPressed;
      }
    }
  }
  return bReturnValue;
}

boolean BeanSandbox::isLedOn( byte nLed )
{
  // Default return value to false
  boolean bReturnValue = false;  

  // If LED number is valid (1-16) ...
  if( (nLed>=1) && (nLed <=16) )
  {
    // If the specified button control’s mode is set to SBX_BTNMODE_LED
    if( _nPushButtonMode[nLed-1] == SBX_BTNMODE_LED )
    {
       bReturnValue = isBtnPressed( nLed );
    }
  }

  return bReturnValue;
}

boolean BeanSandbox::setLed( byte nLed, boolean bOnOff )
{
  // Default return value to false
  boolean bReturnValue = false;  

  // If LED number is valid (1-16) ...
  if( (nLed>=1) && (nLed <=16) )
  {
    // If the specified button control’s mode is set to SBX_BTNMODE_LED
    if( _nPushButtonMode[nLed-1] == SBX_BTNMODE_LED )
    {
       bReturnValue = setButton( nLed, bOnOff );
    }
  }

  return bReturnValue;
}

boolean BeanSandbox::_sendControlValueToBean( byte nControl, byte nValue )
{
  char sendBuffer[2];
  
  // Process any incoming serial input before sending
  _processSerial();

  // Prepare send buffer
  sendBuffer[0] = nControl;
  sendBuffer[1] = nValue;

  // Send the info to the sandbox
  Serial.write( (uint8_t*) sendBuffer, 2 );
  Bean.sleep(5);

  return true;  
}

void BeanSandbox::_updateAllControls()
{
  char sendBuffer[60];
  uint8_t length = 60;

  // First, we’ll send slider values
  sendBuffer[0] = SBX_SLIDER1;
  sendBuffer[1] = getSliderValue(1);
  sendBuffer[2] = SBX_SLIDER2;
  sendBuffer[3] = getSliderValue(2);
  sendBuffer[4] = SBX_SLIDER3;
  sendBuffer[5] = getSliderValue(3);
  sendBuffer[6] = SBX_SLIDER4;
  sendBuffer[7] = getSliderValue(4);
  sendBuffer[8] = SBX_SLIDER5;
  sendBuffer[9] = getSliderValue(5);
  sendBuffer[10] = SBX_SLIDER6;
  sendBuffer[11] = getSliderValue(6);

  // Next, we’ll send checkbox values
  sendBuffer[12] = SBX_CHKBOX1;
  sendBuffer[13] = (byte) isChecked(1);
  sendBuffer[14] = SBX_CHKBOX2;
  sendBuffer[15] = (byte) isChecked(2);
  sendBuffer[16] = SBX_CHKBOX3;
  sendBuffer[17] = (byte) isChecked(3);
  sendBuffer[18] = SBX_CHKBOX4;
  sendBuffer[19] = (byte) isChecked(4);
  sendBuffer[20] = SBX_CHKBOX5;
  sendBuffer[21] = (byte) isChecked(5);
  sendBuffer[22] = SBX_CHKBOX6;
  sendBuffer[23] = (byte) isChecked(6);

  // Next, we’ll send checkbox values
  for(int i=0; i<16; i++)
  {
    sendBuffer[(i*2)+24] = (byte) (i+13);
    sendBuffer[(i*2)+25] = (byte) isBtnPressed(i+1);
  }

  // Only send updated touchpad values when touchpad is not active
  if(!isTouchpadActive())
  {
    // Add the touchpad values
    sendBuffer[56] = SBX_PADX;
    sendBuffer[57] = getTouchpadX();
    sendBuffer[58] = SBX_PADY;
    sendBuffer[59] = 255-getTouchpadY();
  }
  else
  {
    length = 56;
  }

  // Send the info to the sandbox
  Serial.write( (uint8_t*) sendBuffer, length );
  delay(10);
  Bean.sleep(50);
}

