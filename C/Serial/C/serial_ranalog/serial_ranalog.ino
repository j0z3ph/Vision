#define BAUD 115200
#define motor 15
#define analogx 13
#define analogy 12
#define button 14

String receivedString;
int sensorValue = 0;
char cstr[20];
int buttonState = 0;

void setup() {
  Serial.begin(BAUD);
  pinMode(button, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
}

void loop() {
  int ax = analogRead(analogx);
  int ay = analogRead(analogy);
  buttonState = digitalRead(button);

  sprintf(cstr, "%04d-%04d-%d\n\0", ax, ay, buttonState);
  Serial.write(cstr);

  digitalWrite(motor, LOW);

  if (Serial.available() > 0) {
    receivedString = Serial.readStringUntil('\n');
    if (receivedString.equals("on") || receivedString.equals("ON")) {
      digitalWrite(motor, HIGH);
    } 
  }
  delay(100);
}
