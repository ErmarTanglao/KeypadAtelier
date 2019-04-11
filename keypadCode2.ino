/*
 * Original sourse: https://playground.arduino.cc/Code/Keypad
 * This is the Arduino code for 4x4 keypad.
 * watch the video for details and demo http://youtu.be/qIDzzG2LUtg
 *  * 
 * Written by Ahmad Nejrabi for Robojax Video channel www.Robojax.com
 * Date: Dec 18, 2017, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * this code has been downloaded from http://robojax.com/learn/arduino/
 * 
 */
/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int correct = false;
char* answer = "8264";
int position = 0;
int redLED = 11; //The red LED is connected to pin 11

int greenLED = 12; //The green LED is connected to pin 12


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  setLocked(true);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}
  
void loop(){
  char key = keypad.getKey();

   if (key){
    Serial.print(key);
    Serial.print(',');
    Serial.println(position);

   } 

   if (key == '*' || key == '#'){
      position = 0;
      setLocked(true);
    }

   if (key == answer[position]){
      position ++;
      Serial.println("correct");
      
    } else if(key == '1'|| key == '2' || key == '3'|| key == '4' || key == '5'|| key == '6' || key == '7'|| key == '8' || key == '9') {
      
       position = 0;
       Serial.println("wrong");
    }


   if (position == 4){
      setLocked(false);
    }
    
  delay(100);
}

void setLocked(int locked){
  if (locked){   
    myservo.write(180); //and the servo should turn to a 90 degree position.
    digitalWrite(redLED, HIGH);    // turn the LED off by making the voltage HIGH
    digitalWrite(greenLED, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("Not Completed");
} else {
    myservo.write(0); //..and the servo should turn to a 0 degree position.
    digitalWrite(redLED, LOW);    // turn the LED off by making the voltage HIGH
    digitalWrite(greenLED, HIGH);    // turn the LED off by making the voltage LOW
    Serial.println("Completed");
  }
}
