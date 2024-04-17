#include <ESPConnect.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <AsyncTCP.h>
#include <Preferences.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "Connection.h"
#include "index.h"

//Timer variables
unsigned long lastTime =millis();
unsigned long timerDelay = 30000;


// variables to get server connection and fields
const char* serverD = "serverD";
const char* susername = "susername";
const char* spassword = "spassword";
const char* restData[32] = {"get-post","serverD","susername","spassword","fieldC","field1","field1V","static1","field2","field2V","static2",   
"field3","field3V","static3","field4","field4V","static4","field5","field5V","static5","field6","field6V","static6",
"field7","field7V","static7","field8","field8V","static8","field9","field9V","static9"};
String fields[9][3];


// config for reset button
int buttonState = 0;     // current state of the button
int resettime = 10; // previous state of the button

//config for DHT sensor
#define DHTTYPE    DHT22  
#define DHTPIN 14     // Digital pin connected to the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//start a instance of preference to add strings to eeprom
Preferences preferences;

String readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature(true);
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

String readESPMac(){
  String m = WiFi.macAddress();
      Serial.println(m);
    return String(m);
}

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  } else if(var == "MAC"){
    return readESPMac();
  }
  return String();
}

void setup(){
  //that button again
  pinMode(27, INPUT);
  // Serial port for debugging purposes
  Serial.begin(115200);

  dht.begin();
  
  // Connect to Wi-Fi
 /*
    AutoConnect AP
    Configure SSID and password for Captive Portal
  */
  //code reset
  //ESPConnect.erase();
  ESPConnect.autoConnect("MonitorSetup");

  /* 
    Begin connecting to previous WiFi
    or start autoConnect AP if unable to connect
  */
  if(ESPConnect.begin(&server)){
    Serial.println("Connected to WiFi");
    Serial.println("IPAddress: "+WiFi.localIP().toString());
  }else{
    Serial.println("Failed to connect to WiFi");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
 // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 //   request->send_P(200, "text/html", index_html, processor);
//  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
    server.on("/mac", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readESPMac().c_str());
  });

  //routes for web pages

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Web Server: Homepage");
    String html = HTML_CONTENT_HOME;  // Use the HTML content from the index.h file
    request->send(200, "text/html", html);
  });

  server.on("/Connection.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Web Server: Connection 1");
    String html = HTML_CONTENT_Connection;  // Use the HTML content from the index.h file
    request->send(200, "text/html", html);
  });

  //capture the variables from the input form and write them to flash
  preferences.begin("snowString",false);
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
   // loop to capture all the form data.   
      for (int i = 0; i <= 31; i++) {
        if (request->hasParam(restData[i])) {
      inputMessage = request->getParam(restData[i])->value();
      preferences.putString(restData[i], inputMessage);
      }
    }
    request->send(200, "text/html", "Server set to "+ inputMessage +"<br><a href=""/index.html"">Click Here to go back to the homepage</a>");

});


//set up a array of the field values


  server.begin();
}

void loop() {
// reset script
  buttonState = digitalRead(27); // read the button input
 if (buttonState == LOW) {
  Serial.print("Reset Button is Pressed and device will reset in ");
 Serial.print(resettime); 
Serial.println(" seconds");
 delay(1000);
 resettime = resettime - 1;
 if (resettime <=0){
 Serial.println("Reseting");
 delay(1000);
  ESPConnect.erase();
  preferences.clear();
  ESP.restart();
 resettime = 10;
  }
} 

// Post requests

if ((millis() - lastTime) > timerDelay) {
if(WiFi.status()== WL_CONNECTED){
  HTTPClient httpClient;
//Post data back to service now
  httpClient.begin(preferences.getString("serverD","did not work"));
  String username = preferences.getString("susername","did not work");
  String password = preferences.getString("spassword","did not work");
  httpClient.addHeader("Accept","application/json");
  httpClient.addHeader("Content-Type","application/json");
  httpClient.setAuthorizationType("Basic");
  httpClient.setAuthorization(username.c_str(),password.c_str());
  //create a string array so I can customize the number and name variables sent
  int pCount = 5;
for (int a = 0; a <= 8; a++) {
  for (int b = 0; b <= 2; b++) { 
    fields[a][b]= preferences.getString(restData[pCount],"wrong");
    pCount = pCount + 1;
  }}
  //build the responce
  // determine number of fields
  int fieldNum = 0;
  String check = preferences.getString(restData[4],"wrong");
      for (char c : check) {
        if (c >= '0' && c <= '9') {
            fieldNum = fieldNum * 10 + (c - '0');
        }}

// build my string in a loop
String responceBuild2 = "{";
for (int i = 0; i<=fieldNum-1;i++){
  if (fields[i][1]=="Temperature") {
    responceBuild2 = responceBuild2+"\""+fields[i][0]+"\":\""+String(dht.readTemperature(true));
    } else {
      if (fields[i][1]=="Humidity") {
        responceBuild2 = responceBuild2+"\""+fields[i][0]+"\":\""+String(dht.readHumidity());
        } else {
          if (fields[i][1]=="MAC_address") {
            responceBuild2 = responceBuild2+"\""+fields[i][0]+"\":\""+WiFi.macAddress();
            } else {
              if (fields[i][1]=="Water_alert") {
                responceBuild2 = responceBuild2+"\""+fields[i][0]+"\":\""+"false";
                } else {
                  if (fields[i][1]=="reboot_time") {
                    responceBuild2 = responceBuild2+"\""+fields[i][0]+"\":\""+"not in play yet";
                    } else {
                      if (fields[i][1]=="static_entry") {
                        responceBuild2 = responceBuild2+"\""+fields[i][0]+"\":\""+fields[i][2];
                      } 
                  }
              }
          }
      }
     }
if (i <=fieldNum-2){
responceBuild2 = responceBuild2+"\",";
  }  
}

//
responceBuild2 = responceBuild2+"\"}";

    
    int httpResponseCode = httpClient.POST(responceBuild2); 
      Serial.println("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println (responceBuild2);
      httpClient.end();

  //Get data from ServiceNow (change update time) 
if(preferences.getString("get-post","did not work")=="getpost"){
  httpClient.begin(preferences.getString("serverD","did not work"));
  username = preferences.getString("susername","did not work");
  password = preferences.getString("spassword","did not work");
  httpClient.addHeader("Accept","application/json");
  httpClient.addHeader("Content-Type","application/json");
  httpClient.setAuthorizationType("Basic");
  httpClient.setAuthorization(username.c_str(),password.c_str());
  int httpResponseCode = httpClient.GET();

  String payload = "{}"; 

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = httpClient.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  httpClient.end();


//parse responce with JSON (change "refresh" to whatever the key name is)
Serial.println(payload);
JSONVar updateTime = JSON.parse(payload);
Serial.println(updateTime["refresh"]);
String suT = updateTime["refresh"];
unsigned long ut = suT.toInt();
//convert minutes to miliseconds
timerDelay = 60000*ut;
Serial.println(ut);
Serial.println(timerDelay);
}

}

lastTime = millis();
    
}

    }



