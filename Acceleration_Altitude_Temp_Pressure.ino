/*
*	Arduino Program to log acceleration, altitude, temperature, and pressure
*	Copyright (C) 2021 Nick Thompson, John Burns, Alex Nehls, Hayden Worden
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*
* This program logs accelleration in X,Y,Z, altitude, Pressure and temperature 
* Once arduino is programmed/code uploaded, data will start logging to SD card
* as soon as it is powered. Data rate can be changed in the variable below.
* Data will create/keep logging to "log.txt" stored on micro SD card, file can
* be renamed after.
* Data output is formatted for easy copy/paste to excel/matlab
*/

#include <Arduino_LSM9DS1.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <SPI.h>
#include <SD.h>

#define DEBUG false

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
File myFile;

// Rate at which the arduino logs data (in milliseconds)
// Theres is a small delay from proccessing speed to account for in any time-based calculations
float data_rate = 1000;

// Function to log data to serial console for debugging purposes
inline void debugLog(String s) __attribute__((always_inline));
void debugLog(String s)
{
  if(DEBUG) Serial.println(s);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  debugLog("Started");

  if (!IMU.begin()) {
    debugLog("Failed to initialize IMU!");
    while (1);
  }

  if (!SD.begin(10)) {
    debugLog("Failed to initialize SD card!");
    while (1);
  }
  debugLog("Initialization successful!");

  myFile = SD.open("log.txt", FILE_WRITE);

  myFile.println("Acceleration in G's");
  myFile.println("X\tY\tZ\tPressure(in Hg)\t\tAltitude(Ft)\t\tTemperature(F)");
  myFile.close();

  debugLog("Acceleration in G's");
  debugLog("X\tY\tZ\tPressure(in Hg)\t\tAltitude(Ft)\t\tTemperature(F)");

}

void loop() {
  if (! baro.begin()) {
    debugLog("Couldnt find sensor");
    return;
  }
  myFile = SD.open("test.txt", FILE_WRITE);
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    myFile.print(x);
    myFile.print('\t');
    myFile.print(y);
    myFile.print('\t');
    myFile.print(z);

    if(DEBUG) {
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.print(z);
    }
    
    float pascals = baro.getPressure();
    // Our weather page presents pressure in Inches (Hg)
    // Use http://www.onlineconversion.com/pressure.htm for other units
   
    myFile.print('\t');
    myFile.print(pascals / 3377);

    if(DEBUG) {
      Serial.print('\t');
      Serial.print(pascals / 3377);
    }

    float   altm = baro.getAltitude();
    altm = (altm * 3.28);
    myFile.print('\t');
    myFile.print('\t');
    myFile.print('\t');
    myFile.print(altm);

    if(DEBUG) {
      Serial.print('\t');
      Serial.print('\t');
      Serial.print('\t');
      Serial.print(altm);
    }

    float tempC = baro.getTemperature();
    tempC = ((tempC * (1.8)) + 32);
    myFile.print('\t');
    myFile.print('\t');
    myFile.print('\t');
    myFile.println(tempC);

    if(DEBUG) {
      Serial.print('\t');
      Serial.print('\t');
      Serial.print('\t');
      Serial.println(tempC);
    }

    myFile.close();
    delay(data_rate);
  }
}
