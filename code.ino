/*
  Landslide Early Warning Alert System - hardware prototype
  components:- soil moisture sensor, vibration sensor, buzzer, LCD display (16*2) 
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
#define soilPin  A0      // Soil moisture analog output
#define vibrationPin A1   // Vibration sensor analog output
#define buzzerPin 8     // Buzzer control pin


int soil;    // read the value of soil moisture sensor
int vibrate; // vibration sensor value read

void setup() {
  Serial.begin(9600);
  pinMode(vibrationPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Landslide Alert");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  soil = analogRead(A0);
  vibrate = analogRead(A1);
  Serial.print("Soil: ");
  Serial.print(soil);
  Serial.print(" | Vibration Count: ");
  Serial.println(vibrate);
  delay(500);
  lcd.setCursor(0,0);

  if (soil>=500 && vibrate>=300) //asumed values of risky situation
   {
    lcd.print("DANGER!");
    triggerAlert();
  }

  else if (soil<500 &&  soil >=300 || vibrate<300 && vibrate>=200) //slightly less dangerous situation
{
    lcd.print("MODERATE!");
    digitalWrite(buzzerPin, LOW);
  } 
  
  else {
    lcd.print("SAFE!");
    digitalWrite(buzzerPin, LOW);
  }

}

void triggerAlert() {
  // Pulsed buzzer pattern for landslide risk
  digitalWrite(buzzerPin, HIGH);
  delay(5000);
  digitalWrite(buzzerPin, LOW);
}
