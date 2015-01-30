/*

  BeanSandbox - A library for use with PunchThrough Design’s LightBlue Bean microcontroller board to interact 
                with the sandbox controls in PunchThrough Design’s LightBlue IOS app

  Copyright (c) 2015 Bruce Walker

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

*/

#ifndef BEANSANDBOX_H
#define BEANSANDBOX_H

#include "Arduino.h"

// Define touchpad modes
#define SBX_PADMODE_IMMEDIATE 0       // Touchpad values will update as they change
#define SBX_PADMODE_ONRELEASE 1       // Touchpad values will update only when finger is raised

// Define push button modes
#define SBX_BTNMODE_IMMEDIATE 0       // Push button acts as momentary switch
#define SBX_BTNMODE_TOGGLE 1          // Push button acts as push-on/push-off switch
#define SBX_BTNMODE_LED 2             // Push button will be used as an LED.

class BeanSandbox
{
  public:
    BeanSandbox();
    ~BeanSandbox();

    void initializeValues();
    boolean autoUpdateSandbox( boolean bYesNo );
    boolean autoUpdateSandbox();
    byte getSliderValue( byte nSlider );
    boolean setSliderValue( byte nSlider, byte nValue );
    boolean isChecked( byte nCheckbox );
    boolean setCheckbox( byte nCheckbox, boolean bChecked );
    void setTouchpadMode( byte nMode );
    byte getTouchpadX();
    byte getTouchpadY();
    boolean setTouchpadX( byte nValue );
    boolean setTouchpadY( byte nValue );
    boolean setTouchpad( byte nX, byte nY );
    boolean isTouchpadActive();
    void setPushButtonMode( byte nButton, byte nMode );
    boolean isBtnPressed( byte nButton );
    boolean setButton( byte nButton, boolean bPressed );
    boolean isLedOn( byte nLed );
    boolean setLed( byte nLed, boolean bOnOff );
    
  private:
    boolean _bAutoUpdateSandbox;
    byte _nSlider[6];
    boolean _bCheckbox[6];
    byte _nTouchpadMode;
    boolean _bTouchpadTouch;    
    byte _nTouchpadValuesImmediate[2];
    byte _nTouchpadValuesOnRelease[2];
    byte _nPushButtonMode[16];
    boolean _bPushButtonImmediate[16];
    boolean _bPushButtonToggle[16];
    unsigned long _nLastProcessed;
    unsigned long _nLastControlUpdate;

    void _processSerial();
    boolean _sendControlValueToBean( byte nControl, byte nValue );
    void _updateAllControls();
};

#endif
