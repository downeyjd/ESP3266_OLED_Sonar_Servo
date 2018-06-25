#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   13
#define OLED_CLK   16
#define OLED_DC    4
#define OLED_CS    5
#define OLED_RESET 15
#define pwPin     14
#define trigPin   12
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

long pulse, cm, barHeight;

void setup()   {
  Serial.begin(9600);
  Serial.println("And we're off!");
  pinMode(pwPin, INPUT);
  pinMode(trigPin, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setRotation(1); //Portrait mode
  display.setTextSize(1);
  display.setTextColor(WHITE);
}


void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  
  // pulse the trigger pin, at least 10usec
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // pull in echo pulse, conv. usec travel time to cm
  pulse = pulseIn(pwPin, HIGH, 8890);
  if (pulse == 0) cm = 120;
  else cm = pulse / (2*29.1);
  Serial.println(cm);

  //draw graph
  barHeight = map(cm, 0, 120, 0, display.height()-10);
  display.fillRect(0, display.height()-barHeight, display.width(), display.height() - 10, WHITE);
  display.setCursor(0, display.height()-8);
  display.print(cm);
  display.print(" cm");
  display.display();
  delay(100);
}
