#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial (2, 3); // Rx Tx nano

RF24 radio(7, 8); // CE, CSN nano

const byte address[6] = "00001";
char text[32] = "";
char oldText[32] = "";


void setup() {
  Serial.begin(9600);

  ESPserial.begin(9600);


  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}
void loop() {
  if (ESPserial.available()) {
    Serial.write(ESPserial.read());
  }

  if (radio.available()) {

    radio.read(&text, sizeof(text));
    Serial.println(text);

  }

  ESPserial.write(text);
  delay(1000);
}




