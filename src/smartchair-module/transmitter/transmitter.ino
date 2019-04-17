#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

#define sensorPin A0  // Analog input pin that the potentiometer is attached to
#define chargePin A1 // Analog input pint to get the batterycharge
#define greenPin 5 // Analog output pin that the LED is attached to
#define redPin 4
#define onPin 2

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int chargeValue = 0;
float voltage = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  //Serial.begin(9600);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(onPin, OUTPUT);
  digitalWrite(onPin, HIGH);
  radio.begin();
  radio.openWritingPipe(address);
  radio.printDetails();
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  // read the analog value of the resistor:
  sensorValue = analogRead(sensorPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  //read the analog value of the battery
  chargeValue = analogRead(chargePin);
  //convert it to value between 0 and 5V
  voltage = chargeValue * (5.0/ 1023.0) * 9.02;
  
 



  if (outputValue > 100) {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    
    char text[3] = {'0','9',chargeData(voltage)};
    //char text[32] = {chargeValue};
    radio.write(&text, sizeof(text));
    
    
  }
  else {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    
    char text[3] = {'0','8',chargeData(voltage)};
    //char text[32] = {chargeValue};
    radio.write(&text, sizeof(text));
  
    
    
  }
    

  delay(1000);
}

//converts voltage into sendable data the esp will read
char chargeData(float f) {
  if (f <= 5.5 && f >= 4.15) {
    return '4';
  }
  if (f < 4.15 && f >= 3.90) {
    return '3';
  }
  if (f < 3.90 && f >= 3.80) {
    return'2';
  }
  if (f < 3.80 && f >= 3.70) {
    return '1';
  }
  else {
    return '0';
  }
}

