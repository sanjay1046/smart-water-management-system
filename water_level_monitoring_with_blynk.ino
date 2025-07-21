#include <LiquidCrystal_I2C.h>

//Include the library files
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
#define LED1 2
#define LED2 4
#define LED3 5
#define LED4 18
#define trig 12
#define echo 13
#define relay 14
#define BLYNK_TEMPLATE_ID "TMPL3ZbWLLD1s"
#define BLYNK_TEMPLATE_NAME "Water Level Monitoring System"

//Enter your tank max value(CM)
int MaxLevel = 13;

int Level1 = (MaxLevel * 75) / 100;
int Level2 = (MaxLevel * 65) / 100;
int Level3 = (MaxLevel * 55) / 100;
int Level4 = (MaxLevel * 35) / 100;

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27,16,2);

BlynkTimer timer;

// Enter your Auth token
char auth[] = "WMojxJ-b6VzB0b4G4Ovi3dep6BPTbwJc";

//Enter your WIFI SSID and password
char ssid[] = "OnePlus 12R Sher";
char pass[] = "f5g2gkg7";

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  lcd.init();
  lcd.backlight();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  lcd.setCursor(3,0);
  lcd.print("System");
  lcd.setCursor(3,1);
  lcd.print("Loading..");
  delay(4000);
  lcd.clear();
}

//Get the ultrasonic sensor values
void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  int distance = t / 29 / 2;

  Serial.println(distance);

  int blynkDistance = (distance - MaxLevel) * -1;
  if (distance <= MaxLevel) {
    Blynk.virtualWrite(V2, blynkDistance);
  } else {
    Blynk.virtualWrite(V2, 0);
  }
  lcd.setCursor(1, 0);
  lcd.print("WLevel:");

  if (Level1 <= distance) {
    lcd.setCursor(8, 0);
    lcd.print("Very Low");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  } else if (Level2 <= distance && Level1 > distance) {
    lcd.setCursor(8, 0);
    lcd.print("Low");
    lcd.print("      ");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  } else if (Level3 <= distance && Level2 > distance) {
    lcd.setCursor(8, 0);
    lcd.print("Medium");
    lcd.print("      ");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  } else if (Level4 <= distance && Level3 > distance) {
    lcd.setCursor(8, 0);
    lcd.print("Full");
    lcd.print("      ");
    digitalWrite(relay, HIGH);
    lcd.setCursor(1, 1);
    lcd.print("Motor is OFF");
    Blynk.virtualWrite(V1, 0);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
}

//Get the button value
BLYNK_WRITE(V1) {
  int Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
    lcd.setCursor(1, 1);
    lcd.print("Motor is ON ");
    Blynk.virtualWrite(V1,0);
  } else {
    digitalWrite(relay, HIGH);
    lcd.setCursor(1, 1);
    lcd.print("Motor is OFF");
  }
}

void loop() {
  ultrasonic();
  Blynk.run();//Run the Blynk library
}
