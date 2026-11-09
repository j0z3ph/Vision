#define pushButton_pin 13
#define LED_pin 2

// Interrupt Handler
void IRAM_ATTR toggleLED() {
  // Solo alternamos el estado del LED
  digitalWrite(LED_pin, !digitalRead(LED_pin));
}

void setup() {
  pinMode(LED_pin, OUTPUT);
  pinMode(pushButton_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pushButton_pin), toggleLED, FALLING);
}

void loop() {
  // Nothing
}