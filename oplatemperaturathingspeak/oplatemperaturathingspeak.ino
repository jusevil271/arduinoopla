#include <WiFiNINA.h>
#include <Arduino_MKRIoTCarrier.h>
#include <ThingSpeak.h>

MKRIoTCarrier carrier;

// Configuración de la red WiFi
char ssid[] = "Avatel_4C";           // Reemplaza con el nombre de tu red WiFi
char pass[] = "gs5cp88R";     // Reemplaza con la contraseña de tu red WiFi

// Configuración de ThingSpeak
unsigned long myChannelNumber = 2412452; // Reemplaza con tu número de canal
const char * myWriteAPIKey = "VUN733LIZQFXS1DN"; // Reemplaza con tu clave de escritura API

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Conecta a WiFi
  Serial.print("Conectando a WiFi...");
  int status = WiFi.begin(ssid, pass);
  while (status != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("Conectado a WiFi");

  // Inicializa la conexión con ThingSpeak
  ThingSpeak.begin(client);

  // Inicializa el MKR IoT Carrier
  carrier.begin();
}

void loop() {
  // Lee la temperatura desde el sensor del MKR IoT Carrier
  float temperature = carrier.Env.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Enviar los datos a ThingSpeak
  ThingSpeak.setField(1, temperature);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Actualización exitosa.");
  } else {
    Serial.println("Error al enviar los datos: " + String(x));
  }

  // Espera 20 segundos antes de enviar nuevamente
  delay(20000);
}

