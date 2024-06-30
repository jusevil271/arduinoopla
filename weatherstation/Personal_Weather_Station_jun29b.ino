#include "arduino_secrets.h"

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
 
  // Defined in thingProperties.h
  initProperties();
 
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  //Get Cloud Info/errors , 0 (only errors) up to 4
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
 
  //Wait to get cloud connection to init the carrier
  while (ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    delay(500);
  }
  delay(500);
  CARRIER_CASE = false;
  carrier.begin();
  carrier.display.setRotation(0);
  delay(1500);
}
 
void loop() {
  ArduinoCloud.update();
  carrier.Buttons.update();
 
  while(!carrier.Light.colorAvailable()) {
    delay(5);
  }
  int none;
  carrier.Light.readColor(none, none, none, light);
  
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();
 
 
  //if (carrier.Buttons.onTouchDown(TOUCH0)) {
    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.setTextSize(2);
 
    carrier.display.setCursor(30, 110);
    carrier.display.print("Temp: ");
    carrier.display.print(temperature);
    carrier.display.print(" C");
    delay(2000);
  //}
 
  //if (carrier.Buttons.onTouchDown(TOUCH1)) {
    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.setTextSize(2);
 
    carrier.display.setCursor(30, 110);
    carrier.display.print("Humi: ");
    carrier.display.print(humidity);
    carrier.display.print(" %");
    delay(2000);
  //}
 
  //if (carrier.Buttons.onTouchDown(TOUCH2)) {
    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.setTextSize(2);
 
    carrier.display.setCursor(30, 110);
    carrier.display.print("Light: ");
    carrier.display.print(light);
    delay(2000);
  //}
 
  //if (carrier.Buttons.onTouchDown(TOUCH3)) {
    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.setTextSize(2);
 
    carrier.display.setCursor(30, 110);
    carrier.display.print("Pressure: ");
    carrier.display.print(pressure);
    delay(2000);
  //}
 
  if (humidity >= 60 && temperature >= 15) {
    weather_report = "It is very humid outside";
    
  }else if (temperature >= 15 && light >= 700) {
    weather_report = "Warm and sunny outside";
    
  }else if (temperature <= 16 && light >= 700) {
    weather_report = "A little cold, but sunny outside";
  }
  
  else{
   weather_report = "Weather is normal"; 
  }
 
}