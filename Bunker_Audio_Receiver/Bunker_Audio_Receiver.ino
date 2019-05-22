char mystr[10];


uint8_t incomingByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {

                // read the incoming byte:
                incomingByte = Serial.read();
                Serial.println(incomingByte);

                if(incomingByte=='H'){  //if incoming data is the expected request (request code = 'Q' in this example)
                        Serial.println("Yes, it worked!");       
                }
        }

}
