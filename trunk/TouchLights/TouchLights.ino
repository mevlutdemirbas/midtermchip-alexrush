/* 
 Touch Shield Example using the MPR121 touch sensor IC 

 by: Aaron Weiss, based on the MPR121 Keypad Example by Jim Lindblom
     
 SparkFun Electronics
 created on: 5/12/11
 license: OSHW 1.0, http://freedomdefined.org/OSHW
 
 Pressing a pad will print the corresponding number.
 
 Hardware: 3.3V or 5V Arduino

 Notes: The Wiring library is not used for I2C, a default atmel I2C lib
        is used. Be sure to keep the .h files with the project. 
*/

// include the atmel I2C libs
#include "mpr121.h"
#include "i2c.h"

// 11 max digits used
#define DIGITS 11 

// Match key inputs with electrode numbers
#define ONE 8
#define TWO 5
#define THREE 2
#define FOUR 7
#define FIVE 4
#define SIX 1
#define SEVEN 6
#define EIGHT 3
#define NINE 0

//extras (not used)
#define ELE9 9
#define ELE10 10
#define ELE11 11

//interupt pin
int irqpin = 2;  // D2
boolean Lightone = false;
boolean Lighttwo = false;
boolean Lightthree = false;
boolean Lightfour = false;
boolean Lightfive = false;
boolean Lightsix = false;
boolean Lightseven = false;
boolean Lighteight = false;
boolean Lightnine = false;
void setup()
{
  //make sure the interrupt pin is an input and pulled high
 pinMode(irqpin, INPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT); 
  digitalWrite(irqpin, HIGH);
  
  //configure serial out
  Serial.begin(9600);
  
  //output on ADC4 (PC4, SDA)
  DDRC |= 0b00010011;
  // Pull-ups on I2C Bus
  PORTC = 0b00110000; 
  // initalize I2C bus. Wiring lib not used. 
  i2cInit();
  
  delay(100);
  // initialize mpr121
  mpr121QuickConfig();
  
  // Create and interrupt to trigger when a button
  // is hit, the IRQ pin goes low, and the function getNumber is run. 
  attachInterrupt(0,getNumber,LOW);
  
  // prints 'Ready...' when you can start hitting numbers
  Serial.println("Ready...");
}

void loop()
{

//turns on lights according to key press
if(Lightone == true)
   digitalWrite(3, HIGH);
   else
   digitalWrite(3, LOW);
if(Lighttwo == true)
   digitalWrite(4, HIGH);
   else
   digitalWrite(4, LOW);
if(Lightthree == true)
   digitalWrite(5, HIGH);
   else
   digitalWrite(5, LOW);
if(Lightfour == true)
   digitalWrite(6, HIGH);
   else
   digitalWrite(6, LOW);
if(Lightfive == true)
   digitalWrite(7, HIGH);
   else
   digitalWrite(7, LOW);
if(Lightsix == true)
   digitalWrite(8, HIGH);
   else
   digitalWrite(8, LOW);
if(Lightseven == true)
   digitalWrite(9, HIGH);
   else
   digitalWrite(9, LOW);
if(Lighteight == true)
   digitalWrite(10, HIGH);
   else
   digitalWrite(10, LOW);
 if(Lightnine == true)
   digitalWrite(11, HIGH);
   else
   digitalWrite(11, LOW); 
   
}

void getNumber()
{
  int i = 0;
  int touchNumber = 0;
  uint16_t touchstatus;
  char digits[DIGITS];
  
  touchstatus = mpr121Read(0x01) << 8;
  touchstatus |= mpr121Read(0x00);
  
  for (int j=0; j<12; j++)  // Check how many electrodes were pressed
  {
    if ((touchstatus & (1<<j)))
      touchNumber++;
  }
  
  //activates appropiate lights when key pressed
  if (touchNumber == 1)
  {
    if (touchstatus & (1<<SEVEN)){
      Lightseven = !Lightseven;
      digits[i] = '7';
  }
    else if (touchstatus & (1<<FOUR)){
      Lightfour = !Lightfour;
      digits[i] = '4';
    }
    else if (touchstatus & (1<<ONE)){
      Lightone = !Lightone;
      digits[i] = '1';
    }
    else if (touchstatus & (1<<EIGHT)){
      Lighteight = !Lighteight;
      digits[i] = '8';
    }
    else if (touchstatus & (1<<FIVE)){
      Lightfive = !Lightfive;
      digits[i] = '5';
    }
    else if (touchstatus & (1<<TWO)){
      Lighttwo = !Lighttwo;
      digits[i] = '2';
    }
    else if (touchstatus & (1<<NINE)){
      Lightnine = !Lightnine;
      digits[i] = '9';
    }
    else if (touchstatus & (1<<SIX)){
      Lightsix = !Lightsix;
      digits[i] = '6';
    }
    else if (touchstatus & (1<<THREE)){
      Lightthree = !Lightthree;
      digits[i] = '3';
    }
      
  
    Serial.print(digits[i]);
 
    i++;
  }
  //do nothing if more than one button is pressed
  else if (touchNumber == 0)
  
    ;
  else
    ;
    
    
   
}
