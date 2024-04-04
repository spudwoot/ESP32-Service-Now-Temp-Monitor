# ESP32-Service-Now-Temp-Monitor #
## Code to make a ESP 32 read temp and post to a Service Now instance.  Features include: ##
*Built-in captive portal to set up to wifi
*forms to capture the server path and password/username 
*ability to reset the wifi settings without changing code
*ability to POST results back to a ServiceNow instance (or any other platform with a similar table structure)

Still in progress:
* Ability to change field names
* Ability to GET a new refresh time
* code optimization
* captive portal customization

Libaries needed in Arduino IDE:
.For the DHT sensor
Adafruit Unified Sensor - https://github.com/adafruit/Adafruit_Sensor
DHT sensor library - https://github.com/adafruit/DHT-sensor-library

.for the captive portal
ESP Connect - https://github.com/ayushsharma82/ESPConnect - simple connect portal
AsyncTCP - https://github.com/dvarrel/AsyncTCP
ESPAsyncWebServer - https://github.com/lacamera/ESPAsyncWebServer

.for the REST and other config
HTTP Client -https://github.com/amcewen/HttpClient
Preferences (to write settings to the EEPROM) - https://github.com/vshymanskyy/Preferences
WiFi.H  https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi

Known bug at this time 
.Can't get the delay to work properly
