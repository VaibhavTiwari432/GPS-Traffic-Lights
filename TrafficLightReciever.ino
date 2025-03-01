#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup(){
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int j=0;
void loop() 
{
  
  if (radio.available())
  {
    
    const int text;
    radio.read(&text, sizeof(text));
    Serial.println(text);
    delay(2000);
    j=text;
    digitalWrite(4,HIGH);//Green LED Light
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    delay(2000);
    digitalWrite(4,LOW);
    digitalWrite(3,LOW);
    //Serial.println("Green the Light");
  }

  if(j==1)
  {
    digitalWrite(2,HIGH);//Green LED Light
    digitalWrite(4,LOW);
    digitalWrite(3,LOW);
    delay(2000);
    digitalWrite(4,LOW);
    digitalWrite(3,LOW);
    Serial.println("Green the Light");
    //delay(5000);
    
    //delay(5000);
  //}
  
  if(j>9)
  {
    digitalWrite(4,HIGH);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    Serial.println("Green the Light");
    delay(2000);
    
    

  }
  
  else
  {
    digitalWrite(4,HIGH);
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    delay(500);
    Serial.println("No Ambulance Found");
    j++;
  }
  
}