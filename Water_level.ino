#define High 50
#define Low 5

#include <NewPing.h>

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 10, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int percen(void){
  int distance, depth, len;
  int per;
  distance = sonar.ping_cm();
  depth = High - distance;
  len = High - Low;
  per = (depth*100) / len;
  if(per < 0)
    per = 0;
  else if(per > 100)
    per = 100;

  return per;
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
}

void loop() {
  int per;
  per = percen();
  Serial.println(per);

  
  lcd.setCursor(0,0);
  lcd.print("Water Monitoring Sys.");
  lcd.setCursor(0,1);
  lcd.print("Level: ");
  lcd.setCursor(8,1);
  lcd.print(per*10);
  lcd.setCursor(12,1);
  lcd.print("Ltr.");
  
  if(per == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println("Pump is Running");
    lcd.print("Pump is Running");
    digitalWrite(13, HIGH);
    while(per < 100){
      lcd.setCursor(0,1);
      lcd.print("Level: ");
      lcd.setCursor(8,1);
      lcd.print(per*10);
      lcd.setCursor(12,1);
      lcd.print("Ltr.");
      delay(200);
//      lcd.clear();
      per = percen();
    }
    digitalWrite(13, LOW);
  }
  else if(per == 100){
    lcd.setCursor(0,1);
    Serial.println("turn off pump");
    lcd.print("Pump turned off..");
    
  }
  delay(200);
  lcd.clear();
}
