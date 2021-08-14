
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>  
#include <DHT_U.h>                                                         
#define FIREBASE_HOST "temp-11218-default-rtdb.firebaseio.com"                          
#define FIREBASE_AUTH "AWg1VHH4LjdzG0rflZBa4AyUiH8Q429EEQtl0pv0"            

#define WIFI_SSID "Rithika"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "Pustu100"                                    //password of wifi ssid

#define DHTTYPE DHT11   
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 
const int analogInPin = A0; 

void setup() {
  Serial.begin(115200);
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();  
  float gassensorAnalog = analogRead(analogInPin);
    
  if (isnan(h) || isnan(t)|| isnan( gassensorAnalog)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println("Failed to read from the sensors!");
    return;
  }

  Serial.print("Humidity: ");  
  Serial.print(h);                                         //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
  Serial.print("Gas sensor: "); 
  Serial.print(gassensorAnalog);
  delay(4000);

  Firebase.setFloat("/gas", gassensorAnalog); 
  Firebase.setFloat("/humidity", h);                                  //setup path and send readings
  Firebase.setFloat("/temperature", t); 
   if (Firebase.failed()) {

      Serial.print("pushing /logs failed:");

       Serial.println("REASON: " + Firebase.error());

      return;
   } 
}
