#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <brain/motor_cortex_msg.h>
#include <Stepper.h>

// #############################
// ######### CONSTANTS #########
// #############################

const int M1 = 7;
const int M2 = 6;
const int M3 = 5;
const int M4 = 4;

const int M5 = 53;
const int M6 = 51;
const int M7 = 49;
const int M8 = 47;

const int SPR = 180; // Steps Per Revolution
const int STEPPERS = 2;

// defines variables
int motor_delay = 5;

int pins[STEPPERS*4];

// defines motor object with the four IN pins
Stepper tongue_stepper = Stepper(SPR, M1, M2, M3, M4);
Stepper jaw_stepper = Stepper(SPR, M5, M6, M7, M8);

Stepper steppers[STEPPERS] = {tongue_stepper, jaw_stepper};

// Define ros variables
ros::NodeHandle nh;
brain::motor_cortex_msg Steppers;

// Callbacks
void stepper_callback(const brain::motor_cortex_msg &msg) {
  if (msg.stepper_motors[0].impulse == 1) {
    tongue_stepper.step(SPR);
    nh.loginfo("forward");
  }
  else if (msg.stepper_motors[0].impulse == -1) {
    tongue_stepper.step(-SPR);
    nh.loginfo("backward");
  }
}

// Subscribers
ros::Subscriber<brain::motor_cortex_msg> stepper_sub("steppers", &stepper_callback);

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.subscribe(stepper_sub);

  for (int i = 0; i < STEPPERS; i++) {
//    Serial.println(steppers[i]);
  }

  tongue_stepper.setSpeed(95); // MAX 100

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  nh.spinOnce();
}
