#include <SoftwareSerial.h>
#define LED 9

SoftwareSerial btSerial(2, 3); //RX, TX

void setup() {
  pinMode(LED, OUTPUT);
  btSerial.begin(9600);
}

void loop() {
  if (btSerial.available()) {
    char c = btSerial.read();

    switch (c) {
      case '1':
        digitalWrite(LED, HIGH);
        break;
      case '0':
        digitalWrite(LED, LOW);
        break;
    }
  }
}
