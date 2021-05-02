# Doppler Shift Time-of-Flight Rocket Tracking
#### ECE 402 | Spring 2021 | Final Project

&copy; 2021 Nick Thompson, John Burns, Alex Nehls, and Hayden Worden

---

This code comes in two distinct sections:
- MATLAB code
  - Calculates the position and velocity of a rocket based on the frequency shift of a 433 MHz transmitter due to the Doppler Effect.
  - Requirements:
    - [MATLAB](https://www.mathworks.com/products/matlab.html) License.
    - Minimum of 3 base station [SDR receivers](https://www.rtl-sdr.com).
    - [433 MHz transmitter](https://www.tme.com/Document/a0d80ff7a085746caae3189a2150e296/CatalogoRadioControlli.pdf) attached to rocket.
    - [Data logging software](https://cubicsdr.com/) to record frequency received by each base station.

- Arduino code
  - Measures the altitude, pressure, acceleration, and temperature of a rocket in flight.
  - Requirements:
    - [Arduino software](https://www.arduino.cc/en/software).
    - Arduino board, e.g. [Arduino Nano 33 BLE](https://store.arduino.cc/usa/nano-33-ble).
    - Accelerometer ([builtin](https://store.arduino.cc/usa/nano-33-ble) or [standalone](https://www.adafruit.com/product/2019)).
    - [Barometric Pressure/Altitude sensor board](https://cdn-shop.adafruit.com/datasheets/1893_datasheet.pdf).
    - [SD Card Module](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-microsd-spi-sdio.pdf).
