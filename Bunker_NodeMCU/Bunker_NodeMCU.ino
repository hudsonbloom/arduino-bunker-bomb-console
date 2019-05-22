#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASEURL "eq-web-applicaiton.firebaseio.com"
#define AUTH "LY6DbxztwfPxKSpRRFekpozzgncTw0vG5bCCywVB"
#define WIFISSID "Hello Future"
#define PASS "turkeysausage"

const char* host = "https://eq-admin-2019.firebaseapp.com";


int sensor = D1;
int jibbyStatus = 0;
int sensorOpen = false;
#define GAME "scarebnb"
#define NAME "arduino2"


int beginLoop = '1';
int redButtonRight = '2';
int redbuttonLeft = '51';
int bothRedButtonsPressed = '4';
int systemActivated = '5';

int R = 'R';
int E = 'E';
int V = 'V';
int N = 'N';
int G = 'G';

int enterButton = '6';
int passwordCorrect = '7';
int passwordWrong = '8';

int bigRedButtonReady = '9';
int missionComplete = 'M';
int reset = 'X';


boolean beginLoopCount = false;
boolean redButtonRightCount;
boolean redbuttonLeftCount;
boolean bothRedButtonsPressedCount;
boolean systemActivatedCount;

boolean RCount;
boolean ECount;
boolean VCount;
boolean NCount;
boolean GCount;

boolean enterButtonEount;
boolean passwordCorrectCount;
boolean passwordWrongCount;

boolean bigRedButtonReadyCount;
boolean missionCompleteCount;
boolean resetCount;

String message;
int incomingByte = 0;



void setupFirebase() {
  Firebase.begin(FIREBASEURL, AUTH);
}

void setupWifi() {
  WiFi.begin(WIFISSID, PASS);
  Serial.println("CONNECTING TO WIFI NETOWRK");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("I 'm connected and my IP address: ");
  Serial.println(WiFi.localIP());

}


void setup() {
  Serial.begin(9600);
  setupWifi();
  setupFirebase();
  getConnectionData();
  pinMode(sensor, INPUT);
  // put your setup code here, to run once:

}

void getConnectionData() {
  String path = "/bunkerButton/";
  FirebaseObject object = Firebase.get(path);

  Serial.println("Connecting ");
  bool connection = object.getBool("connection");

  if (connection = NULL) {
    Firebase.setBool("bunkerButton/connection", true);
  } else

  if (connection == false){
    Serial.print("Connection: ");
    Serial.println(connection);
    loop();
  } else {
    return;
  }
  
   if (Firebase.failed()) {
      Serial.println("Firebase get failed");
      Serial.println(Firebase.error());
      setupWifi();
      delay(3000);
  }
}



void loop() {
  int status = digitalRead(sensor);

  Firebase.setBool("bunkerButton/connection", true);

  StaticJsonBuffer<50> jsonBuffer;
  StaticJsonBuffer<200> jsonBuffer2;
  JsonObject& timeStampObject = jsonBuffer.createObject();
  timeStampObject[".sv"] = "timestamp";


  while (Serial.available()) {
    incomingByte = Serial.read();
//    Serial.println(incomingByte);
  Serial.println(Serial.readString());

//    if (incomingByte == '1'){
//      message = "Begin loop";
//      Serial.println(message);
//      Firebase.pushString("bunkerButton/logs", message);
//    }
//
//    if (incomingByte == '2'){
//      message = "Right red button pressed";
//      Serial.println(message);
//      
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//
//    }
//  
//    if (incomingByte == '3'){
//      message = "Left red button pressed";
//      Serial.println(message);
//      
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == '4'){
//      message = "Both red buttons pressed";
//      Serial.println(message);
//      
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == '5'){
//      message = "System activated";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'R'){
//      message = "R - pressed";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'E'){
//      message = "E - pressed";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'V'){
//      message = "V - pressed";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'N'){
//      message = "N - pressed";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'G'){
//      message = "G - pressed";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == '6'){
//      message = "Enter button presssed";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//    
//    if (incomingByte == '7'){
//      message = "Password correct";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == '8'){
//      message = "Wrong password";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == '9'){
//      message = "Big Button Ready";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'M'){
//      message = "Mission complete";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }
//
//    if (incomingByte == 'X'){
//      message = "Prop reset";
//      Serial.println(message);
//
//      JsonObject& root = jsonBuffer2.createObject();
//      root["message"] = message;
//      root["timeStamp"] = timeStampObject;
//      root.printTo(Serial);
//      
//      Firebase.push("bunkerButton/logs", root);
//    }

    yield();
    
  }

}

