#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
//CARRIER_CASE = 0;

float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);
  carrier.begin();
  carrier.display.setRotation(2);
}

void loop() {

  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  carrier.Buttons.update();

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  printTemperature();
  printHumidity();
  delayMicroseconds(2000);    
}


void printTemperature() {
  carrier.display.fillScreen(ST77XX_BLUE); //red background
  carrier.display.setTextColor(ST77XX_WHITE); //white text
  carrier.display.setTextSize(2); //medium sized text

  carrier.display.setCursor(30, 110); //sets position for printing (x and y)
  carrier.display.print("Temperatura: ");
  carrier.display.print(temperature);
  carrier.display.println(" C");

}

void printHumidity() {
  carrier.display.fillScreen(ST77XX_BLUE); //red background
  carrier.display.setTextColor(ST77XX_WHITE); //white text
  carrier.display.setTextSize(2); //medium sized text

  carrier.display.setCursor(30, 110); //sets new position for printing (x and y)
  carrier.display.print("Humedad: ");
  carrier.display.print(humidity);
  carrier.display.println(" %");
}
