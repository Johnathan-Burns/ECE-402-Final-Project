//This program logs accelleration in X,Y,Z, altitude, Pressure and temperature 
//Once arduino is programmed/code uploaded, data will start logging to SD card as soon as it is powered. Data rate can be changed in the variable below.
//Data will create/keep logging to "TEST.txt" stored on micro SD card, file can be renamed after.
//Data output is formatted for easy copy/paste to excel/matlab
//Nick Thompson- Senior design group 28- 2021


#include <Arduino_LSM9DS1.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
#include <SPI.h>
#include <SD.h>
File myFile;

//Rate at which the arduino logs data (in milliseconds)
//**Theres is a small delay from proccessing speed to account for in any time-based calculations
float data_rate = 1000;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }


  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
  myFile = SD.open("test.txt", FILE_WRITE);

  myFile.println("Acceleration in G's");
  myFile.println("X\tY\tZ\tPressure(in Hg)\t\tAltitude(Ft)\t\tTemperature(F)");
  myFile.close();

  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ\tPressure(in Hg)\t\tAltitude(Ft)\t\tTemperature(F)");

}

void loop() {
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
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
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    
    float pascals = baro.getPressure();
    // Our weather page presents pressure in Inches (Hg)
    // Use http://www.onlineconversion.com/pressure.htm for other units
   
    myFile.print('\t');
    Serial.print('\t');
    Serial.print(pascals / 3377);
    myFile.print(pascals / 3377);

    float   altm = baro.getAltitude();
    altm = (altm * 3.28);
    myFile.print('\t');
    myFile.print('\t');
    myFile.print('\t');
    Serial.print('\t');
    Serial.print('\t');
    Serial.print('\t');

    Serial.print(altm);
    myFile.print(altm);

    float tempC = baro.getTemperature();
    tempC = ((tempC * (1.8)) + 32);
    myFile.print('\t');
    myFile.print('\t');
    myFile.print('\t');
    Serial.print('\t');
    Serial.print('\t');
    Serial.print('\t');
    
    Serial.println(tempC);
    myFile.println(tempC);
    
    delay(data_rate);
    myFile.close();


  }

}
