#include <Bridge.h>
#include <YunClient.h>
#include <MQTTClient.h>
#include <eHealth.h> 

char charVal[10];               //temporarily holds data from vals 
String stringVal = "";     //data on buff is copied to this string


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
  while (!client.connect("jonas-arduino-sender", "41eb7ace", "3554ffc0d00d55c4")) {
    Serial.print(".");
  }

  Serial.println("\nconnected!");

  client.subscribe("/example");
  // client.unsubscribe("/example");
}

void loop() {
  

  float conductance = eHealth.getSkinConductance();
  float resistance = eHealth.getSkinResistance();
  float conductanceVol = eHealth.getSkinConductanceVoltage();
  
  Serial.print("Conductance : ");       
  Serial.print(conductance, 2);  
  Serial.println("");         
  
  Serial.print("Resistance : ");       
  Serial.print(resistance, 2);  
  Serial.println("");    
  
  Serial.print("Conductance Voltage : ");       
  Serial.print(conductanceVol, 4);  
  Serial.println("");
  
  Serial.print("\n");


  dtostrf(conductance, 10, 3, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff  
  
  // wait for a second  
  delay(1000); 

  client.loop();

  if(!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if(millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/jones-channel.n", charVal);
  }
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}







