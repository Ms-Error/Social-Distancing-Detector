#include <Adafruit_NeoPixel.h>

#define PIN 6   

#define NUMPIXELS 12  

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int buzzPin=8;
float buzzTime, buzzFreq, metre=0 ;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  pinMode(echoPin, INPUT);
  
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
  pixels.begin();
}

void loop()
{
  metre = 0.0001723 * readUltrasonicDistance(2, 7);
  Serial.print(metre);
  Serial.println(" metre");
  delay(100); 

  buzzTime= 250-metre*100;
  buzzFreq= 550-metre*100;  
  if (metre<=2.0)
  tone(buzzPin, buzzFreq, buzzTime);
  
  for (int i=0; i < NUMPIXELS; i++) 
  { 
    if (metre>=2.0)
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    
    else
    tone(buzzPin, buzzFreq, buzzTime);
    
    if (metre<=2.0 && metre>1.5)
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    
    if (metre<=1.5 && metre>1.0)
    pixels.setPixelColor(i, pixels.Color(127, 127, 0));
    
    if (metre<=1.0)
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
   
    pixels.show();
    delay(100);
  }
}
