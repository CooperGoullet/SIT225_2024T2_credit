#include "arduino_secrets.h"
#include <DHT.h>
#include "thingProperties.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define ALARM_TEMP_THRESHOLD 25.0
#define ALARM_HUMID_THRESHOLD 60.0

DHT dht(DHTPIN, DHTTYPE);
bool alarm = false;  // Variable to track alarm state

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  dht.begin();

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // Read temperature and humidity
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  if (temp > ALARM_TEMP_THRESHOLD || hum > ALARM_HUMID_THRESHOLD) {
    alarm = true;  // Trigger the alarm
  } else {
    alarm = false;  // Turn off the alarm
  }

  // Update the alarm state in the cloud
  alarmstate = alarm;

  Serial.println("Temperature: " + String(temp) + " °C");
  Serial.println("Humidity: " + String(hum) + " %");
  Serial.println("Alarm State: " + String(alarm ? "ON" : "OFF"));
  Serial.println("=============================================\n");
  delay(3000);  // Wait for 2 seconds before reading again
}

void onTempChange() {
  // Handle temperature change
}

void onHumChange() {
  // Handle humidity change
}

void onAlarmstateChange()  {
  // Add your code here to act upon Alarmstate change
}