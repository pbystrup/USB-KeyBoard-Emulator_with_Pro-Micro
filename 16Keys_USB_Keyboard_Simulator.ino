
/*
Key USB Emulator.

   by: Peter Bystrup Jensen
   date: 28 Juli, 2018

   This code turns your ProMicro, with an ATmega32U4, into an HID USB Keypad.

   Only Testet with Sparkfun and Clone board with 32U4 Processor sometime call Leornardo Board but PinOut are for Sparkfun ProMicro board.
*/

//------------------------------------
// Set ONLY one of this to 1........
#define _Arduino_Nano 0          // NOT clone board, on clone there NO USB IC that can be programmet to USB Simulator. Work only on Orginal Arduino Nano Board. 
#define _SparkFun_Pro_Micro 1    // Only Testet with Sparkfun and Clone board with 32U4 Processor sometime call Leornardo Board but PinOut are for Sparkfun ProMicro board.
//------------------------------------

// Arduino Nano
/*
   Rows and columns are connected as such on the keypad:
   ---------------------------------------------------------
   | Enter        | Return         | ESC       | BackSpace | - MatrixInput1 - D5
   | Up           | Down           | Left      | Right     | - MatrixInput2 - D6
   | Page-up      | Page-dn        | Home      | End       | - MatrixInput3 - D7
   | Insert       | Delete         | F1        | F10       | - MatrixInput4 - D8
   ---------------------------------------------------------
         |             |              |              |
   MatrixOutput1 MatrixOutput2  MatrixOutput3  MatrixOutput4
         D9  .         D10            D11            D12

   Key Led Output on D4 ,  Catode at D4 and Anode + 470R up to VCC pin
   Repeat Switch = D13 ,  (Connect D4 to GND if NO Repeat function on ARROW Keys)
*/
#if (_Arduino_Nano==1)

#define Repeat_On_Off  13

#define KeyLed  4

#define MatrixOutput1  9    // D9
#define MatrixOutput2  10   // D10
#define MatrixOutput3  11   // D11
#define MatrixOutput4  12   // D12

#define MatrixInput1  5   // D5
#define MatrixInput2  6   // D6
#define MatrixInput3  7   // D7
#define MatrixInput4  8   // D8

#define ScanInputD5   0x20
#define ScanInputD6   0x40
#define ScanInputD7   0x80
#define ScanInputD8   0x100

#define ScanOutputD9  0x200
#define ScanOutputD10 0x400
#define ScanOutputD11 0x800
#define ScanOutputD12 0x1000

#define ScanKey_Enter   ScanInputD5+ScanOutputD9   // D5=0  D6=1  D7=1  D8=1  and  D9=0  D10=1  D11=1  D12=1
#define ScanKey_Return  ScanInputD5+ScanOutputD10  // D5=0  D6=1  D7=1  D8=1  and  D9=1  D10=0  D11=1  D12=1
#define ScanKey_ESC     ScanInputD5+ScanOutputD11  // D5=0  D6=1  D7=1  D8=1  and  D9=1  D10=1  D11=0  D12=1
#define ScanKey_F1      ScanInputD5+ScanOutputD12  // D5=0  D6=1  D7=1  D8=1  and  D9=1  D10=1  D11=1  D12=0

#define ScanKey_Up      ScanInputD6+ScanOutputD9   // D5=1  D6=0  D7=1  D8=1  and  D9=0  D10=1  D11=1  D12=1
#define ScanKey_Down    ScanInputD6+ScanOutputD10  // D5=1  D6=0  D7=1  D8=1  and  D9=1  D10=0  D11=1  D12=1
#define ScanKey_Home    ScanInputD6+ScanOutputD11  // D5=1  D6=0  D7=1  D8=1  and  D9=1  D10=1  D11=0  D12=1
#define ScanKey_Star    ScanInputD6+ScanOutputD12  // D5=1  D6=0  D7=1  D8=1  and  D9=1  D10=1  D11=1  D12=0

#define ScanKey_PageUp  ScanInputD7+ScanOutputD9   // D5=1  D6=1  D7=0  D8=1  and  D9=0  D10=1  D11=1  D12=1
#define ScanKey_PageDn  ScanInputD7+ScanOutputD10  // D5=1  D6=1  D7=0  D8=1  and  D9=1  D10=0  D11=1  D12=1
#define ScanKey_End     ScanInputD7+ScanOutputD11  // D5=1  D6=1  D7=0  D8=1  and  D9=1  D10=1  D11=0  D12=1
#define ScanKey_Minus   ScanInputD7+ScanOutputD12  // D5=1  D6=1  D7=0  D8=1  and  D9=1  D10=1  D11=1  D12=0

#define ScanKey_Insert  ScanInputD8+ScanOutputD9   // D5=1  D6=1  D7=1  D8=0  and  D9=0  D10=1  D11=1  D12=1
#define ScanKey_Delete  ScanInputD8+ScanOutputD10  // D5=1  D6=1  D7=1  D8=0  and  D9=1  D10=0  D11=1  D12=1
#define ScanKey_F10     ScanInputD8+ScanOutputD11  // D5=1  D6=1  D7=1  D8=0  and  D9=1  D10=1  D11=0  D12=1
#define ScanKey_Plus    ScanInputD8+ScanOutputD12  // D5=1  D6=1  D7=1  D8=0  and  D9=1  D10=1  D11=1  D12=0
#endif




// Sparkfun Pro Micro
/*
   ---------------------------------------------------------
   | Enter        | Return         | ESC       | BackSpace | - MatrixInput1 - D6
   | Up           | Down           | Left      | Right     | - MatrixInput2 - D7
   | Page-up      | Page-dn        | Home      | End       | - MatrixInput3 - D8
   | Insert       | Delete         | F1        | F10       | - MatrixInput4 - D9
   ---------------------------------------------------------
         |             |              |              |
   MatrixOutput1 MatrixOutput2  MatrixOutput3  MatrixOutput4
         D10 .         D16            D14            D15
   Key Led Output on D5 ,  Catode at D5 and Anode + 470R up to VCC pin
   Repeat Switch = D4 ,  (Connect D4 to GND if NO Repeat function on ARROW Keys)
*/
#if (_SparkFun_Pro_Micro==1)

#define Repeat_On_Off  4

#define KeyLed  5

#define MatrixOutput1  10   // D10
#define MatrixOutput2  16   // D16
#define MatrixOutput3  14   // D14
#define MatrixOutput4  15   // D15

#define MatrixInput1  6   // D6
#define MatrixInput2  7   // D7
#define MatrixInput3  8   // D8
#define MatrixInput4  9   // D9


#define ScanInputD6  0x40
#define ScanInputD7  0x80
#define ScanInputD8  0x100
#define ScanInputD9  0x200

#define ScanOutputD10  0x400
#define ScanOutputD16  0x10000
#define ScanOutputD14  0x4000
#define ScanOutputD15  0x8000

#define ScanKey_Enter   ScanInputD6+ScanOutputD10  // D6=0  D7=1  D8=1  D9=1  and  D10=0  D16=1  D14=1  D15=1
#define ScanKey_Return  ScanInputD6+ScanOutputD16  // D6=0  D7=1  D8=1  D9=1  and  D10=1  D16=0  D14=1  D15=1
#define ScanKey_ESC     ScanInputD6+ScanOutputD14  // D6=0  D7=1  D8=1  D9=1  and  D10=1  D16=1  D14=0  D15=1
#define ScanKey_F1      ScanInputD6+ScanOutputD15  // D6=0  D7=1  D8=1  D9=1  and  D10=1  D16=1  D14=1  D15=0

#define ScanKey_Up      ScanInputD7+ScanOutputD10  // D6=1  D7=0  D8=1  D9=1  and  D10=0  D16=1  D14=1  D15=1
#define ScanKey_Down    ScanInputD7+ScanOutputD16  // D6=1  D7=0  D8=1  D9=1  and  D10=1  D16=0  D14=1  D15=1
#define ScanKey_Home    ScanInputD7+ScanOutputD14  // D6=1  D7=0  D8=1  D9=1  and  D10=1  D16=1  D14=0  D15=1
#define ScanKey_Star    ScanInputD7+ScanOutputD15  // D6=1  D7=0  D8=1  D9=1  and  D10=1  D16=1  D14=1  D15=0

#define ScanKey_PageUp  ScanInputD8+ScanOutputD10  // D6=1  D7=1  D8=0  D9=1  and  D10=0  D16=1  D14=1  D15=1
#define ScanKey_PageDn  ScanInputD8+ScanOutputD16  // D6=1  D7=1  D8=0  D9=1  and  D10=1  D16=0  D14=1  D15=1
#define ScanKey_End     ScanInputD8+ScanOutputD14  // D6=1  D7=1  D8=0  D9=1  and  D10=1  D16=1  D14=0  D15=1
#define ScanKey_Minus   ScanInputD8+ScanOutputD15  // D6=1  D7=1  D8=0  D9=1  and  D10=1  D16=1  D14=1  D15=0

#define ScanKey_Insert  ScanInputD9+ScanOutputD10  // D6=1  D7=1  D8=1  D9=0  and  D10=0  D16=1  D14=1  D15=1
#define ScanKey_Delete  ScanInputD9+ScanOutputD16  // D6=1  D7=1  D8=1  D9=0  and  D10=1  D16=0  D14=1  D15=1
#define ScanKey_F10     ScanInputD9+ScanOutputD14  // D6=1  D7=1  D8=1  D9=0  and  D10=1  D16=1  D14=0  D15=1
#define ScanKey_Plus    ScanInputD9+ScanOutputD15  // D6=1  D7=1  D8=1  D9=0  and  D10=1  D16=1  D14=1  D15=0
#endif



// Keyboard keys define
#define KEY_LEFT_CTRL    0x80
#define KEY_LEFT_SHIFT   0x81
#define KEY_LEFT_ALT     0x82
#define KEY_LEFT_GUI     0x83
#define KEY_RIGHT_CTRL   0x84
#define KEY_RIGHT_SHIFT  0x85
#define KEY_RIGHT_ALT    0x86
#define KEY_RIGHT_GUI    0x87

#define KEY_UP_ARROW     0xDA
#define KEY_DOWN_ARROW   0xD9
#define KEY_LEFT_ARROW   0xD8
#define KEY_RIGHT_ARROW  0xD7
#define KEY_BACKSPACE    0xB2
#define KEY_TAB          0xB3
#define KEY_RETURN       0xB0
#define KEY_ESC          0xB1
#define KEY_INSERT       0xD1
#define KEY_DELETE       0xD4
#define KEY_PAGE_UP      0xD3
#define KEY_PAGE_DOWN    0xD6
#define KEY_HOME         0xD2
#define KEY_END          0xD5
#define KEY_CAPS_LOCK    0xC1
#define KEY_F1           0xC2
#define KEY_F2           0xC3
#define KEY_F3           0xC4
#define KEY_F4           0xC5
#define KEY_F5           0xC6
#define KEY_F6           0xC7
#define KEY_F7           0xC8
#define KEY_F8           0xC9
#define KEY_F9           0xCA
#define KEY_F10          0xCB
#define KEY_F11          0xCC
#define KEY_F12          0xCD

//----------------------------------------------------------------
// Repeat the key if the value Repeat = 1
// The keys that can be set to repeat mode are only the Arrow keys
//
int Repeat = 0;  // Repeat Key On/Off
//----------------------------------------------------------------

//-------------------------------------------------------------------------------
// Set Debug mode. if _DEBUG = 1 then the keys can be show on the Serial Monitor
// BaudRate on Serial port can be set from 9600 to 115200.
//-------------------------------------------------------------------------------
#define _DEBUG 0   // Uses Debug or Not  Set to 1 if Debug and 0 if No Debug

#if (_DEBUG==0)
  #include <Keyboard.h>
#endif
//-----------------------------------------------

// Adding this line before the library is included will cause a warning in the compile output window containing the identified board
#define BOARD_IDENTIFY_WARNING
// If warnings still don't display, ensure "File->Preferences->compiler warnings" is set to "Default".
// Even doing this, some boards still won't display the warning in the compile window but the constant will still be created.

// Include the library
//#include <Board_Identify.h>


int RXLED = 17;  // The RX LED has a defined Arduino pin
// The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too -- RXLED1,
// and RXLED0.)
// TXLED = D30

// RXLED0; //digitalWrite(RXLED, LOW);   // set the RX LED ON
// TXLED0; // TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF

// RXLED1; //digitalWrite(RXLED, HIGH);    // set the RX LED OFF
// TXLED1; // TX LED macro to turn LED ON

// SDA = D2
// SCL = D3

// Pins MatrixInput1-MatrixOutput4 of the Board connected respectively:
int keypadPins[8] = {MatrixInput1, MatrixInput2, MatrixInput3, MatrixInput4 , MatrixOutput1, MatrixOutput2, MatrixOutput3, MatrixOutput4};
int keypadStatus;  // Used to monitor which buttons are pressed.
int timeout;       // timeout variable used in loop
int lastKeypadStatus = 0;  // Remember last keypad status.

void setup()
{
#if (_DEBUG==1)
  {
    Serial.begin(115200);
    Serial.println("<setup>");
    delay(100);

   /*
    *  Board_Identify.cpp
    *  Identify the microcontroller that the code has been compiled for.
    *  Created by Matt Fryer on 2017-10-04.
    *  Licensed under LGPL (free to modify and use as you wish)
    */
    // Print the board information to the serial using the defined terms
//    Serial.print(F("Board Make: "));
//    Serial.println(BoardIdentify::make); 
//    Serial.print(F("Board Model: "));
//    Serial.println(BoardIdentify::model); 
//    Serial.print(F("Board MCU: "));
//    Serial.println(BoardIdentify::mcu); 
    // Board Indentify uses the namespace BoardIdentify to prevent varibale name conflicts

    pinMode(RXLED, OUTPUT);  // Set RX LED as an output
    // TX LED is set as an output behind the scenes
  }
 #endif

  for (int i = 0; i < 8; i++)
  {
    pinMode(keypadPins[i], INPUT);  // Set all keypad pins as inputs
    digitalWrite(keypadPins[i], HIGH);  // pull all keypad pins high
  }
  digitalWrite(KeyLed, HIGH);  // Turn KeyLed Off
  lastKeypadStatus = 0;  // Remember last keypad status.
}

void loop()
{
  keypadStatus = getKeypadStatus();  // read which buttons are pressed
  if (lastKeypadStatus == 0)             // If a button is NOT pressed go into here
  {
    lastKeypadStatus = keypadStatus;
    sendKeyPress(keypadStatus);      // send the button over USB
    timeout = 1000;                  // top of the repeat delay
    if (keypadStatus != 0)             // If a button is pressed go into here
    {
    while ((getKeypadStatus() == keypadStatus) && (--timeout))  // Decrement timeout and check if key is being held down
      {
        delayMicroseconds(1);
        digitalWrite(KeyLed, LOW);    // Turn KeyLed On
      }
      if (!digitalRead(Repeat_On_Off))  // if High then Repeat mode for Arrow keys.
      {
        if (Repeat != 0)             // If a button is pressed go into here
        {
          while (getKeypadStatus() == keypadStatus)  // while the same button is held down
          {
            sendKeyPress(keypadStatus);  // continue to send the button over USB
            digitalWrite(KeyLed, LOW);   // Turn KeyLed On
            delay(100);                  // 100ms repeat rate
            digitalWrite(KeyLed, HIGH);  // Turn KeyLed Off
            Flash_RXled();
          }
        }
      }
      digitalWrite(KeyLed, HIGH);      // Turn KeyLed Off
      Flash_TXled();
    }
  }
  if (keypadStatus == 0)             // If a button is NOT pressed go into here
  {
    lastKeypadStatus = keypadStatus;
  }
  delay(100);                      // 100ms repeat rate
}

/* sendKeyPress(int key): This function sends a single key over USB
   It requires an int, of which the 16 LSbs are used. Each bit in
   key represents a single button on the keypad.
   This function will only send a key press if a single button
   is being pressed

   ---------------------------------------------------------
   | Enter        | Return         | ESC       | BackSpace | - MatrixInput1
   | Up           | Down           | Left      | Right     | - MatrixInput2
   | Page-up      | Page-dn        | Home      | End       | - MatrixInput3
   | Insert       | Delete         | F1        | F10       | - MatrixInput4
   ---------------------------------------------------------
         |             |              |              |
   MatrixOutput1 MatrixOutput2  MatrixOutput3  MatrixOutput4
*/
#if (_DEBUG==1)
void sendKeyPress(int key)
{
  switch (key)
  {
    case 1:  // 0x001
      Serial.println("KEY_RETURN");
      Repeat = 0;
      break;
    case 2:  // 0x002
      Serial.println("KEY_RETURN");
      Repeat = 0;
      break;
    case 4:  // 0x004
      Serial.println("KEY_ESC");
      Repeat = 0;
      break;
    case 8:  // 0x008
      Serial.println("KEY_BACKSPACE");
      Repeat = 0;
      break;
    case 16:  // 0x010
      Serial.println("KEY_UP_ARROW");
      Repeat = 1;
      break;
    case 32:  // 0x020
      Serial.println("KEY_DOWN_ARROW");
      Repeat = 1;
      break;
    case 64:  // 0x040
      Serial.println("KEY_LEFT_ARROW");
      Repeat = 1;
      break;
    case 128:  // 0x080
      Serial.println("KEY_RIGHT_ARROW");
      Repeat = 1;
      break;
    case 256:  // 0x100
      Serial.println("KEY_PAGE_UP");
      Repeat = 0;
      break;
    case 512:  // 0x200
      Serial.println("KEY_PAGE_DOWN");
      Repeat = 0;
      break;
    case 1024:  // 0x400
      Serial.println("KEY_HOME");
      Repeat = 0;
      break;
    case 2048:  // 0x800
      Serial.println("KEY_END");
      Repeat = 0;
      break;
    case 4096:  // 0x1000
      Serial.println("KEY_DELETE");
      Repeat = 0;
      break;
    case 8192:  // 0x2000
      Serial.println("KEY_INSERT");
      Repeat = 0;
      break;
    case 16384: // 0x4000
      Serial.println("KEY_F1");
      Repeat = 0;
      break;
    case 32768:  // 0x8000
      Serial.println("KEY_F10");
      Repeat = 0;
      break;
  }
}
#endif


/* sendKeyPress(int key): This function sends a single key over USB
   It requires an int, of which the 16 LSbs are used. Each bit in
   key represents a single button on the keypad.
   This function will only send a key press if a single button
   is being pressed

   ---------------------------------------------------------
   | Enter        | Return         | ESC       | BackSpace | - MatrixInput1
   | Up           | Down           | Left      | Right     | - MatrixInput2
   | Page-up      | Page-dn        | Home      | End       | - MatrixInput3
   | Insert       | Delete         | F1        | F10       | - MatrixInput4
   ---------------------------------------------------------
         |             |              |              |
   MatrixOutput1 MatrixOutput2  MatrixOutput3  MatrixOutput4
*/
#if (_DEBUG==0)
void sendKeyPress(int key)
{
  switch (key)
  {
    case 1:  // 0x001
      Keyboard.write(KEY_RETURN);       // Sends a keyboard Enter-tast
      Repeat = 0;
      break;
    case 2:  // 0x002
      Keyboard.write(KEY_RETURN);       // Sends a keyboard Return-tast
      Repeat = 0;
      break;
    case 4:  // 0x004
      Keyboard.write(KEY_ESC);          // Sends a keyboard ESC-tast
      Repeat = 0;
      break;
    case 8:  // 0x008
      Keyboard.write(KEY_BACKSPACE);    // Sends a keyboard Backspace-tast
      Repeat = 0;
      break;
    case 16:  // 0x010
      Keyboard.write(KEY_UP_ARROW);     // Sends a keyboard UP-tast
      Repeat = 1;
      break;
    case 32:  // 0x020
      Keyboard.write(KEY_DOWN_ARROW);   // Sends a keyboard Down-tast
      Repeat = 1;
      break;
    case 64:  // 0x040
      Keyboard.write(KEY_LEFT_ARROW);   // Sends a keyboard Left-tast
      Repeat = 1;
      break;
    case 128:  // 0x080
      Keyboard.write(KEY_RIGHT_ARROW);  // Sends a keyboard Right-tast
      Repeat = 1;
      break;
    case 256:  // 0x100
      Keyboard.write(KEY_PAGE_UP);      // Sends a keyboard PageUp-tast
      Repeat = 0;
      break;
    case 512:  // 0x200
      Keyboard.write(KEY_PAGE_DOWN);    // Sends a keyboard PageDown-tast
      Repeat = 0;
      break;
    case 1024:  // 0x400
      Keyboard.write(KEY_HOME);         // Sends a keyboard Home-tast
      Repeat = 0;
      break;
    case 2048:  // 0x800
      Keyboard.write(KEY_END);          // Sends a keyboard End-tast
      Repeat = 0;
      break;
    case 4096:  // 0x1000
      Keyboard.write(KEY_DELETE);       // Sends a keyboard Delete-tast
      Repeat = 0;
      break;
    case 8192:  // 0x2000
      Keyboard.write(KEY_INSERT);       // Sends a keyboard Insert-tast
      Repeat = 0;
      break;
    case 16384: // 0x4000
      Keyboard.write(KEY_F1);           // Sends a keyboard F1-tast
      Repeat = 0;
      break;
    case 32768:  // 0x8000
      Keyboard.write(KEY_F10);          // Sends a keyboard F10-tast
      Repeat = 0;
      break;
  }
}
#endif


/* getKeypadStatus(): This function returns an int that represents
  the status of the 16-button keypad. Only the 16 LSb's of the return
  value hold any significange. Each bit represents the status of a single
  key on the button pad. '1' is bit 0, '2' is bit 1, '3' is bit 2, ...,
  '#' is bit 11.

  This function doesn't work for multitouch.
*/
int getKeypadStatus()
{
  int rowPins[4] = {MatrixOutput1, MatrixOutput2, MatrixOutput3, MatrixOutput4}; // row pins are define as MatrixOutputX of the keypad
  int columnPins[4] = {MatrixInput1, MatrixInput2, MatrixInput3, MatrixInput4};  // column pins are MatrixInputX of the keypad
  int keypadStatus = 0;  // this will be what's returned

  /* initialize all pins, inputs w/ pull-ups */
  for (int i = 0; i < 8; i++)
  {
    pinMode(keypadPins[i], INPUT);
    digitalWrite(keypadPins[i], HIGH);
  }

  for (int row = 0; row < 4; row++)
  { // initial for loop to check all 4 rows
    pinMode(rowPins[row], OUTPUT);  // set the row pin as an output
    digitalWrite(rowPins[row], LOW);  // pull the row pins low
    for (int col = 0; col < 4; col++)
    { // embedded for loop to check all 4 columns of each row
      if (!digitalRead(columnPins[col]))
      {
        keypadStatus |= 1 << ((row + 1) * 3 + (col + 1) - 4); // set the status bit of the keypad return value
      }
    }
    pinMode(rowPins[row], INPUT);  // reset the row pin as an input
    digitalWrite(rowPins[row], HIGH);  // pull the row pin high
  }

  return keypadStatus;
}


// Flash RXled when there data from USB port
// Read from SDA, when go High then flash Led
// RXled from SDA from SDA pin on Processor
void Flash_RXled()
{
// RXLED0;  //digitalWrite(RXLED, LOW);     // set the RX LED ON
// RXLED1;  //digitalWrite(RXLED, HIGH);    // set the RX LED OFF

// D+ = 4
// D- = 3
// USB_CFG_IOPORTNAME
// USB_CFG_DMINUS_BIT
// USB_CFG_DPLUS_BIT

   if (!digitalRead(SDA))
   {
     RXLED0; // set the RXLED ON
   }
   else
   {
     RXLED1; // set the RXLED OFF
   }
}
   

// Flash TXled when there data from USB port
// Read from SCL, when go High then flash Led.
// TXled from SCL pin on Processor
void Flash_TXled()
{
// TXLED0;  // TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF
// TXLED1;  // TX LED macro to turn LED ON

// D+ = 4
// D- = 3
// USB_CFG_IOPORTNAME
// USB_CFG_DMINUS_BIT
// USB_CFG_DPLUS_BIT

   if (!digitalRead(SCL))
   {
     TXLED0; // set the TXLED ON
   }
   else
   {
     TXLED1; // set the TXLED OFF
   }
}
