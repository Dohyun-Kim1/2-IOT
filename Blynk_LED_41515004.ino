#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "5XhwOs2M5RAzWumDhgg19fwgT9c5YfOT";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "U+NetC7C0";
char pass[] = "DD83027895";

int LD1 = D3;
int LD2 = D4;

void setup()
{
  Serial.begin(115200);
  pinMode(LD1, OUTPUT);
  pinMode(LD2, OUTPUT);
  digitalWrite(LD1, LOW);
  digitalWrite(LD2, LOW);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE (V0) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite (LD1, HIGH);
  } else{
    digitalWrite (LD1, LOW);
    }
}

BLYNK_WRITE (V2) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite (LD2, HIGH);
  } else{
    digitalWrite (LD2, LOW);
    }
}
