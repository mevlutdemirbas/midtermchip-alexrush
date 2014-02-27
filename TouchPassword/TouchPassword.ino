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

//Enter the Code
char MyCode[] = {'1', '2', '3', '4'}; //<===================================PASSWORD
char Pressed[] = {'15', '15', '15', '15'};

int touchcount = 0;
boolean Code = false;
boolean flashing = false;
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
if((MyCode[0] == Pressed[0])&&(MyCode[1] == Pressed[1])&&(MyCode[2] == Pressed[2])&&(MyCode[3] == Pressed[3])&&(touchcount%4==0)){
  Code=true;
}
else{
  Code = false;
}
//checks to see if password is correct after every 4 keys entered
if((touchcount%4==0)&&(Code==false)&&(touchcount>0)){
  flashing = true;
  for (int i=0; i<4; i++){
      for (int i=0; i<9; i++)
      digitalWrite(i+3, HIGH);
      delay(1500);
      for (int i=0; i<9; i++)
      digitalWrite(i+3, LOW);
      delay(1500);
      }
  touchcount=0;
  flashing= false;
}
      else if((touchcount%4==0)&&(Code==true)){
      for (int i=0; i<9; i++)
      digitalWrite(i+3, HIGH);
      }



if(Code==true){
  for (int i=0; i<9; i++)
digitalWrite(i+3, HIGH);
}
else{
for (int i=0; i<9; i++)
digitalWrite(i+3, LOW);
}
}


void getNumber()
{
  if(flashing==false){
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
  
  if (touchNumber == 1)
  {
    touchcount++;
    if (touchstatus & (1<<SEVEN)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='7';
      digits[i] = '7';
  }
    else if (touchstatus & (1<<FOUR)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='4';
      digits[i] = '4';
    }
    else if (touchstatus & (1<<ONE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='1';
      digits[i] = '1';
    }
    else if (touchstatus & (1<<EIGHT)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='8';
      digits[i] = '8';
    }
    else if (touchstatus & (1<<FIVE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='5';
      digits[i] = '5';
    }
    else if (touchstatus & (1<<TWO)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='2';
      digits[i] = '2';
    }
    else if (touchstatus & (1<<NINE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='9';;
      digits[i] = '9';
    }
    else if (touchstatus & (1<<SIX)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='6';
      digits[i] = '6';
    }
    else if (touchstatus & (1<<THREE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='3';
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
}
