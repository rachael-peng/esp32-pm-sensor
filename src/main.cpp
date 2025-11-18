// Pins: PM Sensor Pin ( TX - GPIO 17, RX - GPIO 16

#include <Arduino.h>
#include <Adafruit_PM25AQI.h> 

Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

void setup() {
  // Wait for serial monitor to open
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("Adafruit PMSA003I Air Quality Sensor");
  
  // Change default Serial1 pins (TX=GPIO 10, RX=GPIO 9) to safer pins:
  // Serial.begin(BaudRate, Configuration, RX_Pin, TX_Pin)
  Serial1.begin(9600, SERIAL_8N1, 16, 17); // Example: TX on GPIO 17, RX on GPIO 16

  // Wait three seconds for sensor to boot up!
  delay(3000);

  // Connectivity:
  if (! aqi.begin_I2C()) {      // connect to the sensor over I2C
    if (! aqi.begin_UART(&Serial1)) { // connect to the sensor over hardware serial
      Serial.println("Could not find PM 2.5 sensor!");
      while (1) delay(10);
    }
  Serial.println("PM25 found!");
}

void loop() {
  PM25_AQI_Data data;
  
  if (! aqi.read(&data)) {
    Serial.println("Could not read from AQI");
    
    delay(500);  // try again in a bit!
    return;
  }
  Serial.println("AQI reading success");

  Serial.println(F("---------------------------------------"));
  Serial.println(F("Concentration Units (environmental)"));
  Serial.print(F("PM 1.0: ")); Serial.print(data.pm10_env);
  Serial.print(F("\t\tPM 2.5: ")); Serial.print(data.pm25_env);
  Serial.print(F("\t\tPM 10: ")); Serial.println(data.pm100_env);
  Serial.println(F("AQI"));
  Serial.print(F("PM2.5 AQI US: ")); Serial.print(data.aqi_pm25_us);
  Serial.print(F("\tPM10  AQI US: ")); Serial.println(data.aqi_pm100_us);
  Serial.println(F("---------------------------------------"));
  Serial.println();

  delay(1000);
}