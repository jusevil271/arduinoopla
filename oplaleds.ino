#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#define redLED 25
#define greenLED 26
#define blueLED 27
byte counter=0;

void setup() {
  // put your setup code here, to run once:
  WiFiDrv::pinMode(redLED,OUTPUT);
  WiFiDrv::pinMode(greenLED,OUTPUT);
  WiFiDrv::pinMode(blueLED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiDrv::digitalWrite(blueLED, bitRead(counter,0));
  WiFiDrv::digitalWrite(greenLED, bitRead(counter,1));
  WiFiDrv::digitalWrite(redLED, bitRead(counter,2));
  counter>6?counter=0:counter++;
  delay(1000);

}
