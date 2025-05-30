#define BLYNK_TEMPLATE_ID "TMPL6UbLGe2xQ"
#define BLYNK_TEMPLATE_NAME "smartfarm"
#define BLYNK_AUTH_TOKEN "4RhGWUxAftbz3WeFFJ-R6niQcwHYL7NM"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "naganaga";
char pass[] = "buahnaga";

#define LDR_PIN A0          // ADC ESP8266 hanya di A0
#define LED_PIN 13          // Sesuaikan dengan pin ESP8266
#define BUZZER_PIN 12       // Sesuaikan dengan pin ESP8266

int ldrValue = 0;
bool ledManualState = true;  // Status default: lampu ON

BlynkTimer timer;

BLYNK_WRITE(V0) {
  ledManualState = param.asInt();
  digitalWrite(LED_PIN, ledManualState);
}

void checkLampAndLDR() {
  ldrValue = analogRead(LDR_PIN);
  Blynk.virtualWrite(V1, ldrValue);

  bool ledStatus = digitalRead(LED_PIN);

  if (ldrValue < 250) {
    if (ledStatus == LOW) {
      tone(BUZZER_PIN, 1000);
      Blynk.virtualWrite(V2, "Lampu Mati!");
      Blynk.virtualWrite(V3, 255);
    } else {
      noTone(BUZZER_PIN);
      Blynk.virtualWrite(V2, "Lampu Nyala");
      Blynk.virtualWrite(V3, 0);
    }
  } else {
    noTone(BUZZER_PIN);
    Blynk.virtualWrite(V2, "Terang - Aman");
    Blynk.virtualWrite(V3, 0);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  digitalWrite(LED_PIN, ledManualState);
  digitalWrite(BUZZER_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, checkLampAndLDR);
}

void loop() {
  Blynk.run();
  timer.run();
}
