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

// Pin del sensor PIR
const int PIR_PIN = A5;

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
  carrier.display.setRotation(0);
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);

  // Configura el pin del sensor PIR como entrada
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Lee el estado del sensor PIR
  bool motionDetected = digitalRead(PIR_PIN) == HIGH;

  // Muestra el estado del sensor en la pantalla
  carrier.display.fillScreen(ST77XX_BLACK);
  if (motionDetected) {
    carrier.display.setCursor(20, 50);
    carrier.display.print("Movimiento detectado");
    carrier.Buzzer.sound(500); // Activa la alarma
    delay(1000);
    carrier.Buzzer.noSound(); // Desactiva la alarma
  } else {
    carrier.display.setCursor(20, 50);
    carrier.display.print("No hay movimiento");
    carrier.Buzzer.noSound(); // Desactiva la alarma
  }
  //carrier.display.display();


  // Enviar los datos a ThingSpeak
  ThingSpeak.setField(2, motionDetected ? 1 : 0);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Actualización exitosa.");
  } else {
    Serial.println("Error al enviar los datos: " + String(x));
  }

  // Espera 15 segundos antes de enviar nuevamente
  delay(4000);
}

