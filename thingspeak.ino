#include <stdlib.h>
#include <ESP8266WiFi.h>
//#include <DHT.h>

/*------------------------DHT SENSOR------------------------*/
//#define DHTPIN 2         // DHT data pin connected to Arduino pin 2
//#define DHTTYPE DHT22     // DHT 22 (or AM2302)
//DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor
/*----------------------------------------------------------*/

/*-----------------ESP8266 Serial WiFi Module---------------*/
#define SSID "yourssid"     // "" 
#define PASS "Yourpassword"       // ""
#define IP "184.106.153.149"// thingspeak.com ip
String msg = "7OZA0UCFWYJPYVHK"; //your api key
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 10;  // threshold value to decide when the detected sound is a knock or not
char buffer[10];
WiFiServer server(80);//Service Port


// these variables will change:
int sensorReading = 0;      
int ledState = LOW; 
/*-----------------------------------------------------------*/

//Variables
float vibe;
//int hum;
String vibeC;
int error;
void setup()
{
  Serial.begin(9600);
   Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);
   
  WiFi.begin(SSID, PASS);
   
  while (WiFi.status() != WL_CONNECTED) {
    //delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  //Serial.println("AT");
  //delay(5000);
  //if(Serial.find("OK")){
    //connectWiFi();
    // WiFi.begin(SSID, PASS);
  }


void loop(){
 sensorReading = analogRead(knockSensor);
  if (sensorReading >= threshold) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.println("Knock!");
        Serial.println(sensorReading);
        delay(1000);
  //vibeC = dtostrf(sensorReading, 4, 1, buffer); 

  }
  
  delay(5000); 
}

void updateTemp(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(200);
  if(Serial.find("Error")){
    return;
  }
  cmd = msg ;
  cmd += "&field1=";    //field 1 for temperature
  //cmd += vibeC;
  cmd +=sensorReading;
  //cmd += "&field2=";  //field 2 for humidity
 // cmd += 10;
  //cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
 // Serial.println(cmd.length());
  //if(Serial.find(">")){
    Serial.print(cmd);
  //}
  //else{
   // Serial.println("AT+CIPCLOSE");
    //Resend...
  //  error=1;
  //}
}

 
/*boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
  if(Serial.find("OK")){
    return true;
  }else{
    return false;
  }
}*/
