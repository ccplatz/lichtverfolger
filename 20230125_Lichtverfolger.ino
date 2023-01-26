// C++ code
//
#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo_13;
LiquidCrystal lcd_1(3, 4, 8, 9, 10, 11);

int wait = 100;

int rawVoltage = 0;
int voltage = 0;
int maxVoltage = 5;

int leftLightIntensity = 0;
int rightLightIntensity = 0;
int tolerance = 20;
int angle = 90;
int maxAngle = 179;
int minAngel = 0;

// TODOS
// Eingänge auf Variablen umschreiben
// Kommentare auf Englisch



void setup()
{
  // Set up the number of columns and rows on the LCD.
  lcd_1.begin(16, 2);
  
  Serial.begin(9600);
  
  servo_13.attach(13, 500, 2500);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop()
{
  // Berechnung der Spannung des Photovoltaik Paneels
  rawVoltage = analogRead(A0);
  //Serial.print("Ausgangsspannung Paneel: ");
  //Serial.print(rawVoltage);
  //Serial.println(" V");
  
  // Anzeige der Spannung auf dem LCD
  lcd_1.print("Spannung:");
  lcd_1.setCursor(0, 1);
  lcd_1.print(rawVoltage);
  lcd_1.setCursor(0, 0);

  // Einlesen der Lichtstärke
  leftLightIntensity = analogRead(A1);
  rightLightIntensity = analogRead(A2);
  Serial.print("Left eye: ");
  Serial.println(leftLightIntensity);
  Serial.print("Right eye: ");
  Serial.println(rightLightIntensity);
  
  delay(1000); // ENTFERNEN!!!!!!!!!!!!!!!!!

  // Drehung des Podests
  if (rightLightIntensity > leftLightIntensity + tolerance) {
    angle = (angle - 2);
    if (angle < minAngel) {
      angle = minAngel;
    }
  }
  if (leftLightIntensity > rightLightIntensity + tolerance) {
    angle = (angle + 2);
    if (angle > maxAngle) {
      angle = maxAngle;
    }
  }
  servo_13.write(angle);
  
  // Wait for some millisecond(s)
  delay(wait); 
}
