/******************************************************************************
* | File      	:   TX510_uart.cpp
* | Author      :   Yuvraj Sethia, @yuvs0
* | Function    :   Serial communication to TX510 AI Face Recognition Module
* | Info        :
*   Written using translated TX510 manual, available at 
*   https://github.com/blakadder/HLK-TX510/blob/main/HLK-TX510_User%20Manual_V1.0.pdf
*----------------
* |	This version:   V1.0
* | Date        :   2024-01-15
* | Info        :
* -----------------------------------------------------------------------------
* V1.0(2024-01-14):
*   Create library
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documnetation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to  whom the Software is
* furished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
******************************************************************************/

#include "TX510_uart.h"
#include "Arduino.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*
function: sendCommand

input:    a command of type TX510command_t

output:   if userID is returned by TX510, it is returned.
:         if DELETE_ALL is sent, 254 returned
:         all other cases, 255 is returned

remarks:  method for sending commands and passing on replies from TX510
*/
uint8_t TX510::sendCommand(TX510command_t command){
  switch (command) {
    case RECOGNITION:
      Serial.write(cmdRecognition,8);
      Serial.readBytes(inBuffer,12);
      return (getUserID() < 254) ? getUserID() : 255;
      break;
    case REGISTRATION:
      Serial.write(cmdRegistration,8);
      Serial.readBytes(inBuffer,12);
      return (getUserID() < 254) ? getUserID() : 255;
      break;
    case DELETE_ALL:
      Serial.write(cmdDeleteAll,8);
      Serial.readBytes(inBuffer,12);
      return 254;
      break;
  }
  return 255;
}

/*
function: getUserID

input:    none

output:   if a userID is found in the return buffer, it is returned

remarks:  method for extracting a userID of type int from TX510 reply
*/
uint8_t TX510::getUserID(){
  char success = inBuffer[8];
  if (success != 0){
    return 255; //return value of 255 (max) means fail
  } else {
    uint16_t userID = (inBuffer[9]<<8) + inBuffer[10];
    return userID; //any other return value is a success and userID is returned
  }
}