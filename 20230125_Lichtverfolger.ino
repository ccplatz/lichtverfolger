// C++ code
#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo_13;
LiquidCrystal lcd_1(3, 4, 8, 9, 10, 11);

int wait = 200;

// solar paneel
double rawVoltage = 0;
int voltage = 0;
int maxVoltage = 5;
double outputVoltage = 0;

// light detection
int leftLightIntensity = 0;
int rightLightIntensity = 0;
int tolerance = 40;

// turning tower
int angle = 45;
int maxAngle = 90;
int minAngel = 0;

#define SOLAR_PANEEL A0
#define RIGHT_EYE A1
#define LEFT_EYE A2

void setup()
{
  // setup the number of columns and rows on the LCD.
  lcd_1.begin(16, 2);

  // setup serial monitor
  Serial.begin(9600);

  // setup servo engine
  servo_13.attach(13, 500, 2500);
  servo_13.write(maxAngle / 2);

  // setup analog pins
  pinMode(SOLAR_PANEEL, INPUT);
  pinMode(RIGHT_EYE, INPUT);
  pinMode(LEFT_EYE, INPUT);
}

void loop()
{
  // Calculate voltage of solar paneel
  rawVoltage = analogRead(SOLAR_PANEEL);
  outputVoltage = (rawVoltage * 5 / 1024);
  Serial.print("Ausgangsspannung Paneel: ");
  Serial.println((String)outputVoltage + " Volt");
  
  // output voltage on LCD
  lcd_1.print("Spannung:");
  lcd_1.setCursor(0, 1);
  lcd_1.print((String)outputVoltage + " Volt");
  lcd_1.setCursor(0, 0);

  // detect light intensity
  leftLightIntensity = analogRead(RIGHT_EYE);
  rightLightIntensity = analogRead(LEFT_EYE);
  Serial.print("Left eye: ");
  Serial.println(leftLightIntensity);
  Serial.print("Right eye: ");
  Serial.println(rightLightIntensity);
  
  // turn the tower
  if (rightLightIntensity > leftLightIntensity + tolerance) {
    angle = (angle + 2);
    if (angle < minAngel) {
      angle = minAngel;
    }
  }
  if (leftLightIntensity > rightLightIntensity + tolerance) {
    angle = (angle - 2);
    if (angle > maxAngle) {
      angle = maxAngle;
    }
  }
  servo_13.write(angle);
  
  // wait for some millisecond(s)
  delay(wait); 
}
