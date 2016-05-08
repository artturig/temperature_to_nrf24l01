#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// temperature
float temp; 
// pin A0 where the LM35 is read from
int tempPin = 0; 

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9, 10);

byte addresses[][6] = {"1Node", "2Node"};

void setup() {
  //analogReference(INTERNAL);
  Serial.begin(57600);
  printf_begin();
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15, 15);               // Max delay between retries & number of retries
  radio.startListening();                 // First, stop listening so we can talk.
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  radio.openWritingPipe(addresses[0]);    //*Edit to correct address assignments
  radio.openReadingPipe(1, addresses[1]);
  radio.stopListening();
}

void loop() {
// read temp from pin
temp = analogRead(tempPin);

// convert to celcius
temp = temp * 0.48828125;

  // define empty string
String stringOne = "";

// add node name to string  
stringOne = "1Node:";

// add temperature to sting
stringOne += temp;

// add leading ; to notify receiver
stringOne += ";";

// get stingOne length
int length = stringOne.length()+1;

// define charBuf size
char charBuf[length];

// convert stringOne to char array
stringOne.toCharArray(charBuf, length);

// write charBuf and length to radio aka send stuff
  bool ok = radio.write(&charBuf, length);

  if (ok) {
    Serial.println("Transfer OK");
  } else {
    Serial.println("Transfer Fail");
  }
  // delay before sending new packet
  delay(1000);
}
