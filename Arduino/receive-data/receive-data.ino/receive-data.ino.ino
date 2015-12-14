#include <Bridge.h>
#include <YunClient.h>
#include <MQTTClient.h>
#include <eHealth.h> 

#define MOTORPIN 11 // PWM fähiger PIN


char charVal[10];               //temporarily holds data from vals 
String stringVal = "";     //data on buff is copied to this string
float value;
int motorvalue = 0;


YunClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  client.begin("broker.shiftr.io", net);

  connect();
}

void connect() {
  Serial.print("connecting...");
  while (!client.connect("jonas-arduino-receiver", "41eb7ace", "3554ffc0d00d55c4")) {
    Serial.print(".");
  }

  Serial.println("\nconnected!");

  client.subscribe("/jones-channel.n");
  // client.unsubscribe("/example");
}

void loop() {
  
  // wait for a second  
  // delay(1000); 

  // map input value to 0 - 255
  motorvalue = map(value, -1, 40, 0, 255);

  
  
  // control servo motor
  analogWrite(MOTORPIN, motorvalue);

  client.loop();

  if(!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
//  if(millis() - lastMillis > 1000) {
//    lastMillis = millis();
//    client.publish("/jones-channel.n", charVal);
//  }
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
  value = payload.toFloat();
  Serial.print("Motorvalue: ");
  Serial.println(motorvalue); 
}







