#include <LCD_Launchpad.h>

#include <AddicoreRFID.h>

// Example sketch to read the ID from an Addicore 13.56MHz RFID tag
// as found in the RFID AddiKit found at: 
// http://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm




#include <AddicoreRFID.h>
#include <SPI.h>
#define  uchar unsigned char
#define uint  unsigned int
#define LED BIT5
#define LED_OUT P1OUT
#define LED_DIR P1DIR
#include "LCD_Launchpad.h"


LCD_LAUNCHPAD myLCD;
AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

/////////////////////////////////////////////////////////////////////
//set the pins
/////////////////////////////////////////////////////////////////////
 uint day=0;

//Maximum length of the array
#define MAX_LEN 16

void setup() {                
    Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps 
    SPI.begin();
    myRFID.AddicoreRFID_Init();
    LED_DIR = LED; // Set  P1.5 to output direction
    myLCD.init();
    myLCD.clear();    
  
   // Serial.println("welcome to the rfid attendace system");

}

void loop()
{

LED_OUT &= ~LED;
//myLCD.clear();

   
    uchar i, tmp, checksum1;
 
  uchar status;
        uchar str[MAX_LEN];
        uchar RC_size;
        uchar blockAddr;  //Selection operation block address 0 to 63
        String mynum = "";

//        str[1] = 0x4400;
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str); 
 status = myRFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK)
  {
      Serial.println("welcome to the rfid attendace system");
          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
          Serial.print("The tag's number is:\t");
          Serial.print(str[0], HEX);
            Serial.print(" , ");
          Serial.print(str[1],HEX);
            Serial.print(" , ");
          Serial.print(str[2], HEX);
            Serial.print(" , ");
          Serial.println(str[3],HEX);

        



          //Serial.print("Read Checksum:\t\t");
         //   Serial.println(str[4],HEX);
        //  Serial.print("Calculated Checksum:\t");
          //  Serial.println(checksum1);
            
            // Should really check all pairs, but for now we'll just use the first
            if(str[0] == 0xD9)                     
            {
                day=day+1;  //day update
              Serial.print("DAY= ");
               Serial.println(day);
                Serial.println("Hello sifat!\n");
                 myLCD.displayText("SIFAT");
                  delay(1000);
                  myLCD.clear();  
                LED_OUT = LED;
                delay(1000); 
            
            }else if(str[0] == 0x63)                     
            {   day=day+1;  //day update
              Serial.print("DAY= ");
               Serial.println(day);
                Serial.println("Hello ADIB!\n");
                 myLCD.displayText("ADIB");
                 delay(1000);
                  myLCD.clear();  
                LED_OUT = LED;
                delay(1000); 
            } 
            else  
            {     
              Serial.print("DAY= ");
               Serial.println(day);
              Serial.println("Intruder\n");  
              myLCD.displayText("Intruder");
              delay(1000);
                  myLCD.clear();  

               for (int i=1; i <= 3; i++){
                LED_OUT = LED;     
//                digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(1000);               // wait for a second
//                digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
                LED_OUT &= ~LED;
                delay(1000);  
                } //end of for loop
                           
          
                 
            }
            Serial.println();
            delay(1000);
  }
    
        myRFID.AddicoreRFID_Halt();      //Command tag into hibernation              

}

