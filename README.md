# MPU6050_LM393_BMP280_ThingSpeak
Data acquisition system using MPU6050, LM393 motor speed sensor and BMP280 with ThingSpeak visualization
# MPU6050_LM393_BMP280_ThingSpeak

## Project Description
This project implements a data acquisition system using MPU6050, LM393 motor speed sensor, and BMP280 sensor. The system collects real-time sensor data and uploads it to ThingSpeak for graphical visualization.

## Sensors Used
- MPU6050: Measures acceleration values
- LM393: Measures motor speed using pulse counting
- BMP280: Measures temperature and pressure

## Working
The sensors are interfaced with a microcontroller and data is continuously collected.  
Motor speed is calculated using interrupt-based pulse counting.  
All sensor values are uploaded to ThingSpeak at regular intervals.

## Data Recording
- Data was recorded for a minimum duration of 30 minutes
- Motor speed variation was applied during recording
- Due to motor limitations, continuous operation was managed safely

## Files Included
- Arduino source code (.ino)
- Recorded sensor data (.csv)
- Screenshots of ThingSpeak graphs
- README file

## Visualization
Sensor data visualization was performed using ThingSpeak.  
Screenshots of the graphs are attached in this repository.
