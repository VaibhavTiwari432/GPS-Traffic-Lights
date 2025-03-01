#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <math.h>

#define R 6371.0
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
SoftwareSerial gpsSerial(2, 3); // rx,tx

TinyGPSPlus gps; // create gps object

double lat1 = 26.250647; // Latitude of point 1
double lon1 = 78.172848;
double lat2 = 26.250739; // Latitude of point 2
double lon2 = 78.172474;
double distance=0;

void setup() {
  Serial.begin(9600); // connect serial
  gpsSerial.begin(9600); // connect gps sensor

  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  
  while (gpsSerial.available()) 
  { // check for gps data
    if (gps.encode(gpsSerial.read())) 
    { // encode gps data
      if (gps.location.isValid()) 
      { // Check if GPS data is valid
        lat2 = gps.location.lat();
        lon2 = gps.location.lng();
        
        double distance = haversine(lat2, lon2, lat1, lon1)*1000;
        Serial.print((double (distance)));
        Serial.println(" m");
        delay(2000);
        if (distance < 50.00) 
        {
          const int text = 1;
          radio.write(&text, sizeof(text));
          delay(1000);
          Serial.println("Green the light ");
        } 
        else 
        {
          const int text = 0;
          radio.write(&text, sizeof(text));
          delay(1000);
          Serial.println("No ambulance found");
        }
      }
    }
  }

  String latitude = String(lat1, 6);
  String longitude = String(lon1, 6);
  //Serial.println(latitude + ";" + longitude);
  //delay(1000);
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
  // Convert latitude and longitude from degrees to radians
  double lat1_rad = radians(lat1);
  double lon1_rad = radians(lon1);
  double lat2_rad = radians(lat2);
  double lon2_rad = radians(lon2);

  // Calculate the differences between latitudes and longitudes
  double dlat = lat2_rad - lat1_rad;
  double dlon = lon2_rad - lon1_rad;

  // Calculate the great-circle distance using Haversine formula
  double a = pow(sin(dlat / 2), 2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin(dlon / 2), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double distance = R * c;

  return distance;
}
