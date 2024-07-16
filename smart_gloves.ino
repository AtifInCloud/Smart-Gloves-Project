#include <Wire.h>
#include <SoftwareSerial.h>

#define sensor2  A1
#define sensor3  A2
#define sensor4  A3
#define sensor5  A4
#define sensor6  A5
float sensorVal[] = {0,0,0,0,0,0};

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
}

void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  
  sensorVal[1] = analogRead(sensor2);
  sensorVal[2] = analogRead(sensor3);
  sensorVal[3] = analogRead(sensor4);
  sensorVal[4] = analogRead(sensor5);
  sensorVal[5] = analogRead(sensor6);
  printData1();
  delay(500);
  recordAccelRegisters();
  recordGyroRegisters();
  sensorVal[1] = analogRead(sensor2);
  sensorVal[2] = analogRead(sensor3);
  sensorVal[3] = analogRead(sensor4);
  sensorVal[4] = analogRead(sensor5);
  sensorVal[5] = analogRead(sensor6);
  printData2();
  delay(500);
  Serial.print("\n");
  Serial.flush();
}

void setupMPU() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read();
  accelY = Wire.read()<<8|Wire.read();
  accelZ = Wire.read()<<8|Wire.read();
  processAccelData();
}

void processAccelData() {
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = Wire.read()<<8|Wire.read();
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData1() {
  Serial.print(String(sensorVal[1]));
  Serial.print(",");
  Serial.print(String(sensorVal[2]));
  Serial.print(",");
  Serial.print(String(sensorVal[3]));
  Serial.print(",");
  Serial.print(String(sensorVal[4]));
  Serial.print(",");
  Serial.print(String(sensorVal[5]));
  Serial.print(",");
  Serial.print(rotX);
  Serial.print(",");
  Serial.print(rotY);
  Serial.print(",");
  Serial.print(rotZ);
  Serial.print(",");
  Serial.print(gForceX);
  Serial.print(",");
  Serial.print(gForceY);
  Serial.print(",");
  Serial.print(gForceZ);
  Serial.print(",");
}

void printData2() {
  Serial.print(String(sensorVal[1]));
  Serial.print(",");
  Serial print(String(sensorVal[2]));
  Serial.print(",");
  Serial.print(String(sensorVal[3]));
  Serial.print(",");
  Serial.print(String(sensorVal[4]));
  Serial.print(",");
  Serial.print(String(sensorVal[5]));
  Serial.print(",");
  Serial.print(rotX);
  Serial.print(",");
  Serial.print(rotY);
  Serial.print(",");
  Serial.print(rotZ);
  Serial.print(",");
  Serial.print(gForceX);
  Serial.print(",");
  Serial.print(gForceY);
  Serial.print(",");
  Serial.print(gForceZ); 
  Serial.print(",");
}
