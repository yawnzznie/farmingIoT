#define BLYNK_TEMPLATE_ID "TMPL6UbLGe2xQ"
#define BLYNK_TEMPLATE_NAME "smartfarm"
#define BLYNK_AUTH_TOKEN "4RhGWUxAftbz3WeFFJ-R6niQcwHYL7NM"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "naganaga";
char pass[] = "buahlah";

#define LDR_PIN 36         // Sensor cahaya (ADC1)
#define LED_PIN 13         // Simulasi lampu pertanian
#define BUZZER_PIN 12      // Buzzer alarm

int ldrValue = 0;
bool ledManualState = true; 

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
      Blynk.virtualWrite(V2, 255); 
    } else {
      noTone(BUZZER_PIN);
      Blynk.virtualWrite(V2,0);
    }
  } else {
    noTone(BUZZER_PIN);
    Blynk.virtualWrite(V2, 0);
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
