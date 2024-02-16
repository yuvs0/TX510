/******************************************************************************
* | File      	:   TX510_uart.h
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

#ifndef TX510_uart
#define TX510_uart

#include <stdint.h>

typedef enum {
RECOGNITION,
REGISTRATION,
DELETE_ALL
} TX510command_t;
//extern TX510command_t TX510command_t;

class TX510 {
  public:

  // Buffer for storing TX510 UART replies
  char inBuffer[12];

  // Command Hex Definitions
  char cmdRecognition[8] = {0xEF,0xAA,0x12,0x00,0x00,0x00,0x00,0x12};
  char cmdRegistration[8] = {0xEF,0xAA,0x13,0x00,0x00,0x00,0x00,0x13};
  char cmdDeleteAll[8] = {0xEF,0xAA,0x21,0x00,0x00,0x00,0x00,0x21};

  // I/O Methods
  uint8_t sendCommand(TX510command_t command);
  uint8_t getUserID();
};

#endif