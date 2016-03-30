#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

float temp; // temperature
int tempPin = 0; // pin A0
static char sprintfbuffer[15];
static char dtostrfbuffer[15];

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};


void setup() {
//analogReference(INTERNAL);
Serial.begin(57600);
printf_begin();
radio.begin();                          // Start up the radio
radio.setAutoAck(1);                    // Ensure autoACK is enabled
radio.setRetries(15,15);                // Max delay between retries & number of retries  
radio.startListening();                 // First, stop listening so we can talk.
radio.printDetails();                   // Dump the configuration of the rf unit for debugging

   radio.openWritingPipe(addresses[0]);    //*Edit to correct address assignments
   radio.openReadingPipe(1,addresses[1]);
   radio.stopListening(); 
  

}

char myArray[] = "This is not a test";

void loop() {
      bool ok = radio.write(&myArray,sizeof(myArray));
 
     if(ok){ Serial.println("Transfer OK");
     }else { Serial.println("Transfer Fail"); 
     }
     delay(1000);
  
} 
/*temp = analogRead(tempPin);
temp = temp * 0.48828125;
Serial.println(temp);
//sprintf(sprintfbuffer,"%f", temp);
//dtostrf(temp,8, 2, dtostrfbuffer);

//Serial.write(dtostrfbuffer);
radio.openWritingPipe(addresses[0]);
radio.openReadingPipe(1,addresses[1]);
radio.stopListening();                    // First, stop listening so we can talk

Serial.println(sizeof(temp));
// send temperature
if (!radio.write( &temp, sizeof( float )))
  {  printf("failed.\n\r");  
  }

radio.startListening();                                        // Now, continue listening
unsigned long started_waiting_at = micros();                   // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }
   }
   if ( timeout ){                                             // Describe the results
        printf("Failed, response timed out.\n\r");
    }else{
        printf("Sent \n\r");
    }
   
delay(5000);
}*/
