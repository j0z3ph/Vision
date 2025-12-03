#include <WiFi.h>
#define ANALOG_IN_PORT 32
#define DIGITAL_OUT_PORT 2
#define ANALOG_OUT_PORT 2


TaskHandle_t Task1;
TaskHandle_t Task2;

WiFiClient localClient;

const char* ssid = "Wi-Fi IPN";
const char* password = "";

const uint port = 80;
const char* ip = "3.149.222.108";


void setup() {
  Serial.begin(115200);

  pinMode(DIGITAL_OUT_PORT, OUTPUT);
  pinMode(ANALOG_IN_PORT, INPUT);

  Serial.println("Conectando a Internet");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());


  // Tarea a ejecutarse en el core 0. Enviar mensajes al servidor.
  xTaskCreatePinnedToCore(
    Task1code, /* Task function. */
    "Task1",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task1,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */

  delay(500);

  //c Tarea a ejecutarse en el core 1. Recibir mensajes del servidor.
  xTaskCreatePinnedToCore(
    Task2code, /* Task function. */
    "Task2",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task2,    /* Task handle to keep track of created task */
    1);        /* pin task to core 1 */

  delay(500);
}

void loop() {
  if (!localClient.connected()) {
    Serial.println("Conectando al servidor");
    while (!localClient.connect(ip, port)) {
      Serial.print(".");
      delay(500);
    }
    localClient.print("<name>ESP32");
  }
}



// Tarea 1. Mandar mensajes al server
void Task1code(void* pvParameters) {
  Serial.print("Tarea 1 corriendo en el core ");
  Serial.println(xPortGetCoreID());
  int analogread;
  while (1) {
    if (localClient.connected()) {
      analogread = analogRead(ANALOG_IN_PORT);
      Serial.println(analogread);
      localClient.print("<analog_read>" + String(analogread));
    }
    delay(100);
  }
}

// Tarea 2. Esperar mensajes del server
void Task2code(void* pvParameters) {
  Serial.print("Tarea 2 corriendo en el core ");
  Serial.println(xPortGetCoreID());

  while (1) {
    if (localClient.connected()) {
      while (!localClient.available());
      String str = localClient.readStringUntil('\n');
      if(str.startsWith("<digital_write>on")) {
        pinMode(DIGITAL_OUT_PORT, OUTPUT);
        digitalWrite(DIGITAL_OUT_PORT, HIGH);
      } else if(str.startsWith("<digital_write>off")) {
        pinMode(DIGITAL_OUT_PORT, OUTPUT);
        digitalWrite(DIGITAL_OUT_PORT, LOW);
      } else if(str.startsWith("<analog_write>")) {
        str.remove(0, 14);
        analogWrite(ANALOG_OUT_PORT, str.toInt());
      } else {
        Serial.println(str);
      }
    }
    //delay(100);
  }
}

