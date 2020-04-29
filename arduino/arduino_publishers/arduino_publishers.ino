#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/mpu6050_msg.h>
#include <Wire.h>
#include <Kalman.h>

#define TCAADDR 0x70 // Multiplexer physical address
#define MPUADDR 0b1101000 // MPU I2C physical address (0x68 -> 0b1101000, 0x69 -> 0b1101001)

// #############################
// ######### CONSTANTS #########
// #############################

const int ECHO = 2; // HC-SR02 echo pin
const int TRIG = 3; // HC-SR02 trigger pin
const int KY037 = 2; // Number of ky037 microphones connected
const uint8_t n = 2; // Number of MPUs connected
const char MPU_NAMES[n][50] = {"under_knee_left_posterior", "above_knee_left_posterior"};
// , "above_knee_left_posterior"

// #############################
// ######### VARIABLES #########
// #############################

// Gyro + Kalman
Kalman kalmanX[n];
Kalman kalmanY[n];

double accX[n], accY[n], accZ[n];
double gyroX[n], gyroY[n], gyroZ[n];
int16_t tempRaw[n];

double gyroXangle[n], gyroYangle[n];
double compAngleX[n], compAngleY[n];
double kalAngleX[n], kalAngleY[n];

double roll[n];
double pitch[n];
uint32_t timer;

// Hc-sr04
long duration;
float distance;

// Ky037
int ky037_value = 0;
int ky037_abs_value = 0;
int ky037_thereshold = 552;

// #############################
// ############ ROS ############
// #############################

ros::NodeHandle nh;

brain::hcsr04_msg Hcsr04_msg;
ros::Publisher hcsr04_pub("hcsr04", &Hcsr04_msg);

brain::ky037_msg Ky037_msg;
ros::Publisher ky037_pub("ky037", &Ky037_msg);

brain::mpu6050_msg Mpu6050_msg;
ros::Publisher mpu6050_pub("mpu6050", &Mpu6050_msg);

// #############################
// ########## METHODS ##########
// #############################

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.advertise(hcsr04_pub);
  nh.advertise(ky037_pub);
  nh.advertise(mpu6050_pub);

  Serial.begin(500000); // Starts the serial communication

  Wire.begin();
  for (int i = 0; i < n; i++) {
    setupMPU(i);
    timer = micros();
  }

  // set pin modes
  pinMode(ECHO, INPUT); // Sets the echoPin as an Input
  pinMode(TRIG, OUTPUT); // Sets the trigPin as an Output

  delay(100); // Wait for sensors to stabilize
}

void loop() {
  hcsr04();
  ky037();

  // ############# KALMAN ##############

  for (uint8_t i = 0; i < n; i++) {
    tcaselect(i);
    readAcc(i);
    readGyro(i);
    // Delta time
    // Serial.print("TIME 1: ");
    // Serial.println(timer);
    double dt = (double)(micros() - timer) / 1000000;
    timer = micros();
    // Serial.print("TIME 2: ");
    // Serial.println(dt);
    double roll[i]  = {atan2(accY[i], accZ[i]) * RAD_TO_DEG};
    double pitch[i] = {atan(-accX[i] / sqrt(accY[i] * accY[i] + accZ[i] * accZ[i])) * RAD_TO_DEG};
    double gyroXrate[i] = {gyroX[i] / 131.0}; // Convert to deg/s
    double gyroYrate[i] = {gyroY[i] / 131.0}; // Convert to deg/s
    // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    if ((roll[i] < -90 && kalAngleX[i] > 90) || (roll[i] > 90 && kalAngleX[i] < -90)) {
      kalmanX[i].setAngle(roll[i]);
      compAngleX[i] = roll[i];
      kalAngleX[i] = roll[i];
      gyroXangle[i] = roll[i];
    } else {
      // Gyro angle Kalman filter
      kalAngleX[i] = kalmanX[i].getAngle(roll[i], gyroXrate[i], dt);
    }
    // Invert rate, so it fits the restriced accelerometer reading
    if (abs(kalAngleX[i]) > 90) gyroYrate[i] = -gyroYrate[i];
    // Gyro angle no filter
    gyroXangle[i] += gyroXrate[i] * dt;
    gyroYangle[i] += gyroYrate[i] * dt;
    // Serial.println(gyroXrate[i]);
    // Serial.println(gyroYrate[i]);
    // Gyro angle complimentary filter
    compAngleX[i] = 0.93 * (compAngleX[i] + gyroXrate[i] * dt) + 0.07 * roll[i];
    compAngleY[i] = 0.93 * (compAngleY[i] + gyroYrate[i] * dt) + 0.07 * pitch[i];
    // Gyro angle Kalman filter
    // Serial.println(gyroYrate[i]);
    // Serial.println("DELTA TIME: ");
    // Serial.println(dt);
    kalAngleY[i] = kalmanY[i].getAngle(pitch[i], gyroYrate[i], dt);
    // Reset gyro angle when it has drifted too much
    if (gyroXangle[i] < -180 || gyroXangle[i] > 180)
      gyroXangle[i] = kalAngleX[i];
    if (gyroYangle[i] < -180 || gyroYangle[i] > 180)
      gyroYangle[i] = kalAngleY[i];
    float temperature = (float)tempRaw[i] / 340.0 + 36.53;

    mpu6050(i, temperature);
    // printData(i);
    delay(1000);
  }

  // ###################################

  nh.spinOnce();
  delay(500);
}

void hcsr04() {
  // Clears the trigPin
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  //publishing data
  Hcsr04_msg.name = "lateral_left";
  Hcsr04_msg.distance = (int) distance;
  Hcsr04_msg.approaching_speed = 0;
  hcsr04_pub.publish(&Hcsr04_msg);
}

void ky037() {
  for (uint8_t i = 0; i < KY037; i++) {
    // Read analog output pin
    ky037_value = i == 0 ? analogRead(A0) : analogRead(A1);

    // Calculate absolute value
    ky037_abs_value = abs(ky037_value - ky037_thereshold);

    // Building msg
    Ky037_msg.name = i == 0 ? "micro_left" : "micro_right";
    Ky037_msg.loudness = ky037_abs_value;

    // Publish msg
    ky037_pub.publish(&Ky037_msg);
  }
}

void mpu6050(uint8_t i, float temp) {
  // Building msg
  Mpu6050_msg.name = MPU_NAMES[i];
  Mpu6050_msg.kal_angle_x = kalAngleX[i];
  Mpu6050_msg.kal_angle_y = kalAngleY[i];
  Mpu6050_msg.temperature = temp;

  // Publish msg
  mpu6050_pub.publish(&Mpu6050_msg);
}

// #############################
// ########### KALMAN ##########
// #############################

void printData(uint8_t i) {
  Serial.print("==== GYRO ");
  Serial.print(i + 1);
  Serial.println(" ====");
  Serial.print( (roll[i])); Serial.print("\t");
//  Serial.print(gyroXangle[i]); Serial.print("\t");
//  Serial.print(compAngleX[i]); Serial.print("\t");
//  Serial.print(kalAngleX[i]); Serial.print("\t");
//  Serial.print("\t");
  Serial.print( (pitch[i])); Serial.print("\t");
//  Serial.print(gyroYangle[i]); Serial.print("\t");
//  Serial.print(compAngleY[i]); Serial.print("\t");
//  Serial.print(kalAngleY[i]); Serial.print("\t");
//  Serial.print("\t");
//  Serial.print(kalmanX[i]); Serial.print("\t");
//  Serial.print(kalmanY[i]); Serial.print("\t");
//
//  Serial.print(temperature); Serial.print("\t");
//  Serial.println("\r\n");
}

void readAcc(uint8_t i) {
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x3B); // Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(MPUADDR, 6); // Request Accel Registers (3B - 40)
  while (Wire.available() < 6);
  accX[i] = Wire.read() << 8 | Wire.read(); // Store first two bytes into accelX
  accY[i] = Wire.read() << 8 | Wire.read(); // Store middle two bytes into accelY
  accZ[i] = Wire.read() << 8 | Wire.read(); // Store last two bytes into accelZ
}

void readGyro(uint8_t i) {
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x43); // Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(MPUADDR, 6); // Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  gyroX[i] = Wire.read() << 8 | Wire.read(); // Store first two bytes into accelX
  gyroY[i] = Wire.read() << 8 | Wire.read(); // Store middle two bytes into accelY
  gyroZ[i] = Wire.read() << 8 | Wire.read(); // Store last two bytes into accelZ
}

void setupMPU(uint8_t i) {
  tcaselect(i);
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x6B); // Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); // Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x1B); // Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000); // Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x1C); // Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000); // Setting the accel to +/- 2g
  Wire.endTransmission();
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x3B); // Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(MPUADDR, 6); // Request Accel Registers (3B - 40)
  while (Wire.available() < 6);
  accX[i] = Wire.read() << 8 | Wire.read(); // Store first two bytes into accelX
  accY[i] = Wire.read() << 8 | Wire.read(); // Store middle two bytes into accelY
  accZ[i] = Wire.read() << 8 | Wire.read(); // Store last two bytes into accelZ
  roll[i]  = {atan2(accY[i], accZ[i]) * RAD_TO_DEG};
  pitch[i] = {atan(-accX[i] / sqrt(accY[i] * accY[i] + accZ[i] * accZ[i])) * RAD_TO_DEG};
  // Set starting angle
  kalmanX[i].setAngle(roll[i]);
  kalmanY[i].setAngle(pitch[i]);
  gyroXangle[i] = roll[i];
  gyroYangle[i] = pitch[i];
  compAngleX[i] = roll[i];
  compAngleY[i] = pitch[i];
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
