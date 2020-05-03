#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <brain/motor_cortex_msg.h>

// #############################
// ######### CONSTANTS #########
// #############################

const int SPR = 180; // Steps Per Revolution
const int STEPPERS = 1;
int MP[4] = {10, 11, 12, 13};
//int A = 10;
//int B = 11;
//int C = 12;
//int D = 13;

// #############################
// ######### VARIABLES #########
// #############################

long del = 1500; // delay in microseconds

// #############################
// ############ ROS ############
// #############################

// Define ros variables
ros::NodeHandle nh;

// Callbacks
void stepper_callback(const brain::motor_cortex_msg &msg) {
  nh.loginfo("CACCHIO");
  int impulse = map(msg.stepper_motors[0].impulse, 0, 127, 0, 500);
  for (int i = 0; i <= impulse; i++) {
    if (msg.stepper_motors[0].forward == 1) {
      one();
      two();
      three();
      four();
    }
    else if (msg.stepper_motors[0].forward == 0) {
      four();
      three();
      two();
      one();
    }
  }

  motorOff();
  delay(1000);
}

// Subscribers
ros::Subscriber<brain::motor_cortex_msg> stepper_sub("steppers", &stepper_callback);

// #############################
// ########## METHODS ##########
// #############################

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.subscribe(stepper_sub);

  //  for (int i = 0; i < STEPPERS*4; i++) {
  //    pinMode(MP[i], OUTPUT);
  //  }

  pinMode(MP[0], OUTPUT);
  pinMode(MP[1], OUTPUT);
  pinMode(MP[2], OUTPUT);
  pinMode(MP[3], OUTPUT);

  Serial.begin(500000); // Starts the serial communication
}

void one() {
  digitalWrite(MP[0], LOW);
  digitalWrite(MP[1], HIGH);
  digitalWrite(MP[2], HIGH);
  digitalWrite(MP[3], LOW);
  delayMicroseconds(del);
}
void two() {
  digitalWrite(MP[0], LOW);
  digitalWrite(MP[1], HIGH);
  digitalWrite(MP[2], LOW);
  digitalWrite(MP[3], HIGH);
  delayMicroseconds(del);
}
void three() {
  digitalWrite(MP[0], HIGH);
  digitalWrite(MP[1], LOW);
  digitalWrite(MP[2], LOW);
  digitalWrite(MP[3], HIGH);
  delayMicroseconds(del);
}
void four() {
  digitalWrite(MP[0], HIGH);
  digitalWrite(MP[1], LOW);
  digitalWrite(MP[2], HIGH);
  digitalWrite(MP[3], LOW);
  delayMicroseconds(del);
}
void motorOff() {
  digitalWrite(MP[0], LOW);
  digitalWrite(MP[1], LOW);
  digitalWrite(MP[2], LOW);
  digitalWrite(MP[3], LOW);
}

void loop() {
  nh.spinOnce();
}
