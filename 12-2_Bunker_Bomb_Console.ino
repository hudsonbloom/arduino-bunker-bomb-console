/*************************************************** 
  This is an example for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to  
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!`

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_TLC5947.h"

// How many boards do you have chained?
#define NUM_TLC5974 2

#define data   11
#define clock   13
#define latch   10
#define oe  -1  // set to -1 to not use the enable pin (its optional)

Adafruit_TLC5947 tlc = Adafruit_TLC5947(2, clock, data, latch);

// Alphabet Buttons & Magnet
int buttonE = 4;
int buttonECounter = 0;

int buttonG = 8;
int buttonGCounter = 0;

int buttonN = 3;
int buttonNCounter = 0;

int buttonR = 12;
int buttonRCounter = 0;

int buttonV = 9;
int buttonVCounter = 0;

int enterButton = 7;
int bigRedButton = 6;


// 2 Red Buttons
int redButton_Right = A2;
int redButton_Left = A3;

int soundArduino = A5;

int redLights = 5;
int magnet = 2;

int systemActivated = false;
int missionComplete = false;
int bigRedButtonReady = false;



// Password Info
int pwcount;
byte combination[] = "REVENGE";
byte userInput[100];


//Sender Information
char mystr[5] = "ALARM";


boolean redButtonR_Pushed = false;
boolean redButtonL_Pushed = false;

int redButtonR_Count;
int redButtonL_Count;
int bothButtons_Count;


void setup() {

  pinMode (buttonR, INPUT_PULLUP);
  pinMode (buttonE, INPUT_PULLUP);
  pinMode (buttonV, INPUT_PULLUP);
  pinMode (buttonN, INPUT_PULLUP);
  pinMode (buttonG, INPUT_PULLUP);

  
  pinMode (enterButton, INPUT_PULLUP);
  pinMode (bigRedButton, INPUT_PULLUP);
  pinMode (magnet, OUTPUT);
  pinMode (redLights, OUTPUT);
  pinMode (soundArduino, OUTPUT);

  pinMode (redButton_Right, INPUT_PULLUP);
  pinMode (redButton_Left, INPUT_PULLUP);


  digitalWrite(magnet, LOW);
  digitalWrite(redLights, HIGH);
  digitalWrite(soundArduino, HIGH);
  systemActivated = false;

  Serial.begin(115200);
  delay(200);
  Serial.println("Bunker Bomb - v1.0");
  delay(200);
  Serial.println("START");
  tlc.begin();
  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, LOW);
  }
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {
  //Serial.println("Loop");
  
  int redButtonR_State = digitalRead(redButton_Right);
  int redButtonL_State = digitalRead(redButton_Left);
  
  lightsOFF();

  
   if (redButtonL_State == 0){
    redButtonL_Count ++;
  } else if (redButtonL_State == 1) {
    redButtonL_Count = 0;
  }

  if (redButtonR_State == 0){
    redButtonR_Count ++;
   } else if (redButtonR_State == 1){
    redButtonR_Count = 0;
   }


  if (redButtonR_State == 0 && redButtonR_Count > 0 && redButtonR_Count < 2){
        Serial.println("Right Red Button Pressed");
  }


  if (redButtonL_State == 0 && redButtonL_Count > 0 && redButtonL_Count < 2){
      Serial.println("Left Red Button Pressed");
  }
  

  // Press Both Red Buttons
  if (redButtonR_State == 0 && redButtonL_State == 0){
      Serial.println("Both Red Buttons Right Pressed");
    
      delay(200);
      flicker();
      flicker();
      
      // System Activation
      systemActivated = true;
      Serial.println("System Activated");
  }




  while (bigRedButtonReady == true){
  
  int bigRedButtonState = digitalRead(bigRedButton);
  
     if (bigRedButtonState == 0){
        digitalWrite(redLights, LOW);
        Serial.println("Sounding Alarm...");
        missionComplete = true;
        Serial.println("Mission Complete");
        bigRedButtonReady = false;
        return loop();
      }
  }

  while (missionComplete == true){
    lightsOFF();

    int buttonR_State = digitalRead(buttonR);
    int buttonE_State = digitalRead(buttonE);
    delay(20000);
    Serial.println("Reset Prop...");
    delay(100);
    resetFunc();

//    if (buttonR_State == 0 && buttonE_State == 0){
//      Serial.println("Reset Prop...");
//      flicker();
//      Serial.println("...");
//      delay(1200);
//      resetFunc();  //call reset
//    }
  }


  while (systemActivated == true && missionComplete == false) {

  int buttonE_State = digitalRead(buttonE);
  int buttonG_State = digitalRead(buttonG);
  int buttonN_State = digitalRead(buttonN);
  int buttonR_State = digitalRead(buttonR);
  int buttonV_State = digitalRead(buttonV);
  int enterButtonState = digitalRead(enterButton);

  lightsON();

  int buttonRCount;
  int buttonECount;
  int buttonVCount;
  int buttonNCount;
  int buttonGCount;

  
  if (buttonR_State == 0){
    buttonRCount ++;
  } else {
    buttonRCount = 0;
  }
  if (buttonE_State == 0){
    buttonECount ++;
  } else {
    buttonECount = 0;
  }
  if (buttonV_State == 0){
    buttonVCount ++;
  } else {
    buttonVCount = 0;
  }
  if (buttonN_State == 0){
    buttonNCount ++;
  } else {
    buttonNCount = 0;
  }
  if (buttonG_State == 0){
    buttonGCount ++;
  } else {
    buttonGCount = 0;
  }

       if (buttonR_State == 0 && buttonRCount > 0 && buttonRCount < 2) {
        if (buttonR_State == 0){
          tlc.setPWM(17, 0);
          tlc.write();
        }
          userInput[pwcount] = 'R';
          pwcount++;
          delay(200);
          Serial.println("R was pressed");
      }

  if (buttonE_State == 0 && buttonECount > 0 && buttonECount < 2 ) {
    if (buttonE_State == 0){
          tlc.setPWM(4, 0);
          tlc.write();
    }
          userInput[pwcount] = 'E';
          pwcount++;
          delay(200);
          Serial.println("E was pressed");
      } 

   if (buttonV_State == 0 && buttonVCount > 0 && buttonVCount < 2 ) {
    if (buttonV_State == 0){
          tlc.setPWM(21, 0);
          tlc.write();
    }
          userInput[pwcount] = 'V';
          pwcount++;
          delay(200);
          Serial.println("V was pressed");
      }

    if (buttonN_State == 0 && buttonNCount > 0 && buttonNCount < 2 ) {
      if (buttonN_State == 0){
          tlc.setPWM(13, 0);
          tlc.write();
      }
          userInput[pwcount] = 'N';
          pwcount++;
          delay(200);
          Serial.println("N was pressed");

      }

    if (buttonG_State == 0 && buttonGCount > 0 && buttonGCount < 2 ) {
      if (buttonG_State == 0){
          tlc.setPWM(6, 0);
          tlc.write();
      }
          userInput[pwcount] = 'G';
          pwcount++;
          delay(200);
          Serial.println("G was pressed");
    
      }


      if (enterButtonState == 0){
          Serial.println("Password Entered...");
          delay(100);
          enterPassword();
      }


    systemActivated = true;
  }


}


void enterPassword(){

 for (byte n = 0; n <= 7; n++) {

    if (userInput[n] == combination[n] && pwcount >= 7) {
      lightsOFF();
      digitalWrite(magnet, HIGH);
      Serial.println(String(userInput[n]));
      delay(200);
      Serial.println("Password Correct");
      delay(200);
      pwcount = 0;
      n = 0;
      bigRedButtonReady = true;
      Serial.println("Big Red Button Ready");
      delay(1000);
      return loop();

    }
    else if (userInput[n] != combination[n]) {
        //digitalWrite(magnet, HIGH);
        flicker();
        Serial.println(String(userInput[n]));
        delay(200);
        Serial.println("Wrong Password.");
        delay(2000);
        pwcount = 0;

        buttonRCounter = 0;
        buttonECounter = 0;
        buttonVCounter = 0;
        buttonNCounter = 0;
        buttonGCounter = 0;
        
        n = 0;
        return;
      }
    
    //return;
  }
  
}

void flicker(){
  int ON = 755;
  int OFF = 0;

  //OFF    
  tlc.setPWM(0, OFF);
  tlc.setPWM(1, OFF);
  tlc.setPWM(2, OFF);
  tlc.setPWM(3, OFF);
  tlc.setPWM(4, OFF);
  tlc.setPWM(5, OFF);
  
  tlc.setPWM(6, OFF);
  tlc.setPWM(7, OFF);
  tlc.setPWM(8, OFF);
  tlc.setPWM(9, OFF);
  tlc.setPWM(10, OFF);
  tlc.setPWM(11, OFF);
  tlc.setPWM(12, OFF);
  tlc.setPWM(13, OFF);
  
  tlc.setPWM(14, OFF);
  tlc.setPWM(15, OFF);
  tlc.setPWM(16, OFF);
  tlc.setPWM(17, OFF);
  tlc.setPWM(18, OFF);
  tlc.setPWM(19, OFF);
  tlc.setPWM(20, OFF);
  
  tlc.setPWM(21, OFF);
  tlc.setPWM(22, OFF);
  tlc.setPWM(23, OFF);
  tlc.setPWM(24, OFF);
  tlc.setPWM(25, OFF);
  tlc.setPWM(26, OFF);
  tlc.write();
  delay(100);

  //ON
  tlc.setPWM(0, ON);
  tlc.setPWM(1, ON);
  tlc.setPWM(2, ON);
  tlc.setPWM(3, ON);
  tlc.setPWM(4, ON);
  tlc.setPWM(5, ON);
  
  tlc.setPWM(6, ON);
  tlc.setPWM(7, ON);
  tlc.setPWM(8, ON);
  tlc.setPWM(9, ON);
  tlc.setPWM(10, ON);
  tlc.setPWM(11, ON);
  tlc.setPWM(12, ON);
  tlc.setPWM(13, ON);
  
  tlc.setPWM(14, ON);
  tlc.setPWM(15, ON);
  tlc.setPWM(16, ON);
  tlc.setPWM(17, ON);
  tlc.setPWM(18, ON);
  tlc.setPWM(19, ON);
  tlc.setPWM(20, ON);
  
  tlc.setPWM(21, ON);
  tlc.setPWM(22, ON);
  tlc.setPWM(23, ON);
  tlc.setPWM(24, ON);
  tlc.setPWM(25, ON);
  tlc.setPWM(26, ON);
  tlc.write();
  delay(100);
      
  //OFF
  tlc.setPWM(0, OFF);
  tlc.setPWM(1, OFF);
  tlc.setPWM(2, OFF);
  tlc.setPWM(3, OFF);
  tlc.setPWM(4, OFF);
  tlc.setPWM(5, OFF);
  
  tlc.setPWM(6, OFF);
  tlc.setPWM(7, OFF);
  tlc.setPWM(8, OFF);
  tlc.setPWM(9, OFF);
  tlc.setPWM(10, OFF);
  tlc.setPWM(11, OFF);
  tlc.setPWM(12, OFF);
  tlc.setPWM(13, OFF);
  
  tlc.setPWM(14, OFF);
  tlc.setPWM(15, OFF);
  tlc.setPWM(16, OFF);
  tlc.setPWM(17, OFF);
  tlc.setPWM(18, OFF);
  tlc.setPWM(19, OFF);
  tlc.setPWM(20, OFF);
  
  tlc.setPWM(21, OFF);
  tlc.setPWM(22, OFF);
  tlc.setPWM(23, OFF);
  tlc.setPWM(24, OFF);
  tlc.setPWM(25, OFF);
  tlc.setPWM(26, OFF);
  tlc.write();
  delay(100);

  //ON
  tlc.setPWM(0, ON);
  tlc.setPWM(1, ON);
  tlc.setPWM(2, ON);
  tlc.setPWM(3, ON);
  tlc.setPWM(4, ON);
  tlc.setPWM(5, ON);
  
  tlc.setPWM(6, ON);
  tlc.setPWM(7, ON);
  tlc.setPWM(8, ON);
  tlc.setPWM(9, ON);
  tlc.setPWM(10, ON);
  tlc.setPWM(11, ON);
  tlc.setPWM(12, ON);
  tlc.setPWM(13, ON);
  
  tlc.setPWM(14, ON);
  tlc.setPWM(15, ON);
  tlc.setPWM(16, ON);
  tlc.setPWM(17, ON);
  tlc.setPWM(18, ON);
  tlc.setPWM(19, ON);
  tlc.setPWM(20, ON);
  
  tlc.setPWM(21, ON);
  tlc.setPWM(22, ON);
  tlc.setPWM(23, ON);
  tlc.setPWM(24, ON);
  tlc.setPWM(25, ON);
  tlc.setPWM(26, ON);
  tlc.write();
  delay(100);

  //OFF
  tlc.setPWM(0, OFF);
  tlc.setPWM(1, OFF);
  tlc.setPWM(2, OFF);
  tlc.setPWM(3, OFF);
  tlc.setPWM(4, OFF);
  tlc.setPWM(5, OFF);
  
  tlc.setPWM(6, OFF);
  tlc.setPWM(7, OFF);
  tlc.setPWM(8, OFF);
  tlc.setPWM(9, OFF);
  tlc.setPWM(10, OFF);
  tlc.setPWM(11, OFF);
  tlc.setPWM(12, OFF);
  tlc.setPWM(13, OFF);
  
  tlc.setPWM(14, OFF);
  tlc.setPWM(15, OFF);
  tlc.setPWM(16, OFF);
  tlc.setPWM(17, OFF);
  tlc.setPWM(18, OFF);
  tlc.setPWM(19, OFF);
  tlc.setPWM(20, OFF);
  
  tlc.setPWM(21, OFF);
  tlc.setPWM(22, OFF);
  tlc.setPWM(23, OFF);
  tlc.setPWM(24, OFF);
  tlc.setPWM(25, OFF);
  tlc.setPWM(26, OFF);
  tlc.write();
  delay(100);

  //ON
  tlc.setPWM(0, ON);
  tlc.setPWM(1, ON);
  tlc.setPWM(2, ON);
  tlc.setPWM(3, ON);
  tlc.setPWM(4, ON);
  tlc.setPWM(5, ON);
  
  tlc.setPWM(6, ON);
  tlc.setPWM(7, ON);
  tlc.setPWM(8, ON);
  tlc.setPWM(9, ON);
  tlc.setPWM(10, ON);
  tlc.setPWM(11, ON);
  tlc.setPWM(12, ON);
  tlc.setPWM(13, ON);
  
  tlc.setPWM(14, ON);
  tlc.setPWM(15, ON);
  tlc.setPWM(16, ON);
  tlc.setPWM(17, ON);
  tlc.setPWM(18, ON);
  tlc.setPWM(19, ON);
  tlc.setPWM(20, ON);
  
  tlc.setPWM(21, ON);
  tlc.setPWM(22, ON);
  tlc.setPWM(23, ON);
  tlc.setPWM(24, ON);
  tlc.setPWM(25, ON);
  tlc.setPWM(26, ON);
  tlc.write();
  delay(100);
}


void lightsOFF(){
  tlc.setPWM(0, 0);
  tlc.setPWM(1, 0);
  tlc.setPWM(2, 0);
  tlc.setPWM(3, 0);
  tlc.setPWM(4, 0);
  tlc.setPWM(5, 0);
  tlc.setPWM(6, 0);
  
  tlc.setPWM(7, 0);
  tlc.setPWM(8, 0);
  tlc.setPWM(9, 0);
  tlc.setPWM(10, 0);
  tlc.setPWM(11, 0);
  tlc.setPWM(12, 0);
  tlc.setPWM(13, 0);
  
  tlc.setPWM(14, 0);
  tlc.setPWM(15, 0);
  tlc.setPWM(16, 0);
  tlc.setPWM(17, 0);
  tlc.setPWM(18, 0);
  tlc.setPWM(19, 0);
  tlc.setPWM(20, 0);
  
  tlc.setPWM(21, 0); // works
  tlc.setPWM(22, 0);// works
  tlc.setPWM(23, 0);// works
  tlc.setPWM(24, 0);// DOES NOT WORK
  tlc.setPWM(25, 0); // DOES NOT WORK
  tlc.write();
}


void lightsON(){
  int ON = 755;
  
  tlc.setPWM(0, ON);
  tlc.setPWM(1, ON);
  tlc.setPWM(2, ON);
  tlc.setPWM(3, ON);
  tlc.setPWM(4, ON);
  tlc.setPWM(5, ON);
  
  tlc.setPWM(6, ON);
  tlc.setPWM(7, ON);
  tlc.setPWM(8, ON);
  tlc.setPWM(9, ON);
  tlc.setPWM(10, ON);
  tlc.setPWM(11, ON);
  tlc.setPWM(12, ON);
  tlc.setPWM(13, ON);
  
  tlc.setPWM(14, ON);
  tlc.setPWM(15, ON);
  tlc.setPWM(16, ON);
  tlc.setPWM(17, ON);
  tlc.setPWM(18, ON);
  tlc.setPWM(19, ON);
  tlc.setPWM(20, ON);
  
  tlc.setPWM(21, ON);
  tlc.setPWM(22, ON);
  tlc.setPWM(23, ON);
  tlc.setPWM(24, ON);
  tlc.setPWM(25, ON);
  tlc.setPWM(26, ON);
  tlc.write();
}


void soundAlarm(){
  digitalWrite(soundArduino, LOW);
}

