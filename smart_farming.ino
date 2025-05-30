#define BLYNK_TEMPLATE_ID "TMPL6UbLGe2xQ"
#define BLYNK_TEMPLATE_NAME "smartfarmingIoT"
#define BLYNK_AUTH_TOKEN "4RhGWUxAftbz3WeFFJ-R6niQcwHYL7NM"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char ssid[] PROGMEM = "naganaga";
const char pass[] PROGMEM = "13571";

#define LDR_PIN A0       // Satu-satunya pin analog di ESP8266
#define LED_PIN D7       // GPIO13
#define BUZZER_PIN D6    // GPIO12

int ldrValue = 0;
bool ledManualState = true;

BlynkTimer timer;

BLYNK_WRITE(V0) {
  ledManualState = param.asInt();
  digitalWrite(LED_PIN, ledManualState);
}

void checkLDR() {
  ldrValue = analogRead(LDR_PIN);
  Blynk.virtualWrite(V1, ldrValue);

  if (ldrValue < 250) {
    if (!ledManualState) {
      tone(BUZZER_PIN, 1000);
    } else {
      noTone(BUZZER_PIN);
    }
  } else {
    noTone(BUZZER_PIN);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, ledManualState);
  digitalWrite(BUZZER_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, checkLDR);
}

void loop() {
  Blynk.run();
  timer.run();
}