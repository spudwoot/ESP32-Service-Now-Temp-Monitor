#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESPConnect.h>	
#include <AsyncTCP.h>
#include <Preferences.h>
#include <HTTPClient.h>
#include "Connection.h"
#include "Connection2.h"
#include "Connection3.h"


//Timer variables
unsigned long lastTime =millis();
unsigned long timerDelay = 600000;


// variables to get server connection
const char* serverD = "serverD";
const char* susername = "susername";
const char* spassword = "spassword";


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
//html for home page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Current Monitor Status</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;F</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
    <p>
    <i class="fas fa-wifi" style="color:#00add6;"></i> 
    <span class="dht-labels">Mac</span>
    <span id="mac">%MAC%</span>
  </p>
  <p>
  <h1><li><a href="/Connection.html">Set up Service Now Rest API</a></li></h1>
  </P>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  //routes for other pages
  server.on("/Connection.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Web Server: Connection 1");
    String html = HTML_CONTENT_Connection;  // Use the HTML content from the index.h file
    request->send(200, "text/html", html);
  });

    server.on("/Connection2.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Web Server: Connection 2");
    String html = HTML_CONTENT_Connection2;  // Use the HTML content from the index.h file
    request->send(200, "text/html", html);
  });

    server.on("/Connection3.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Web Server: Connection 3");
    String html = HTML_CONTENT_Connection3;  // Use the HTML content from the index.h file
    request->send(200, "text/html", html);
  });



  //test to see if I captured the variables as well as read them into EEProm
  preferences.begin("snowString",false);
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    String page;
    // GET server value on <ESP_IP>/get?server=<inputMessage>
    if (request->hasParam(serverD)) {
      inputMessage = request->getParam(serverD)->value();
      inputParam = serverD;
      preferences.putString("snowServer", inputMessage);
      Serial.println(inputMessage);
    request->send(200, "text/html", "Server set to "+ inputMessage +"<br><a href=""/Connection2.html"">Click Here to input the Username</a>");

    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(susername)) {
      inputMessage = request->getParam(susername)->value();
      inputParam = susername;
      preferences.putString("snowUser", inputMessage);
      Serial.println(inputMessage);
    request->send(200, "text/html", "Username set to "+ inputMessage +"<br><a href=""/Connection3.html"">Click Here to input the Password</a>");
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(spassword)) {
      inputMessage = request->getParam(spassword)->value();
      inputParam = spassword;
      preferences.putString("snowPassword", inputMessage);
      Serial.println(inputMessage);
      Serial.println(preferences.getString("snowServer","did not work"));
    request->send(200, "text/html", "Password set to "+ inputMessage +"<br><a href=""/"">Click Here to go back to the Home Page</a>"); 
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
});
  // Start server
  // build get string


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
  ESP.restart();
 resettime = 10;
  }
} 

// Post and Get requests

if ((millis() - lastTime) > timerDelay) {
if(WiFi.status()== WL_CONNECTED){
  HTTPClient httpClient;
//Post data back to service now
  httpClient.begin(preferences.getString("snowServer","did not work"));
  String username = preferences.getString("snowUser","did not work");
  String password = preferences.getString("snowPassword","did not work");
  httpClient.addHeader("Accept","application/json");
  httpClient.addHeader("Content-Type","application/json");
  httpClient.setAuthorizationType("Basic");
  httpClient.setAuthorization(username.c_str(),password.c_str());
  //create a string array so I can customize the number and name variables sent
  String fieldValue[3][2] = {
    {"temperature", String(dht.readTemperature(true))},  
    {"humidity", String(dht.readHumidity())},
    {"mac_address", WiFi.macAddress()}
  };

    String responceBuild = "{\""+fieldValue[0][0]+"\":\""+fieldValue[0][1]+"\",\""+fieldValue[1][0]+"\":\""+fieldValue[1][1]+"\",\""+fieldValue[2][0]+"\":\""+fieldValue[2][1]+"\"}";
    int httpResponseCode = httpClient.POST(responceBuild); 
      Serial.print("HTTP Response code: ");
      Serial.println (responceBuild);
      Serial.println(httpResponseCode);

  //Get data from ServiceNow (change update time)    
      httpClient.end();
}
else {
      Serial.println("WiFi Disconnected");
    }
      lastTime = millis();
    }
  }



