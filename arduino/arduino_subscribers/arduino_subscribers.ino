#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <brain/motor_cortex_msg.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// #############################
// ######### CONSTANTS #########
// #############################

const int M1 = 7;
const int M2 = 6;
const int M3 = 5;
const int M4 = 4;

const int M5 = 11;
const int M6 = 10;
const int M7 = 9;
const int M8 = 8;

const int SPR = 180; // Steps Per Revolution
const int STEPPERS = 2;

// #############################
// ######### VARIABLES #########
// #############################

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper tongue_stepper(AccelStepper::FULL4WIRE, M1, M2, M3, M4);
AccelStepper jaw_stepper(AccelStepper::FULL4WIRE, M5, M6, M7, M8);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

long positions[STEPPERS];
int motor_delay = 5;

// #############################
// ############ ROS ############
// #############################

// Define ros variables
ros::NodeHandle nh;
brain::motor_cortex_msg Steppers;

// Callbacks
void stepper_callback(const brain::motor_cortex_msg &msg) {
  for (uint8_t i = 0; i < STEPPERS; i++) {
    if (msg.stepper_motors[i].impulse == 0)
      positions[i] = 0;
    else if (msg.stepper_motors[i].impulse == 1) {
      positions[i] = 200;
      nh.loginfo("FORWARD ->");
    }
    else if (msg.stepper_motors[i].impulse == -1) {
      positions[i] = -200;
      nh.loginfo("<- BACKWARD");
    }
  }
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
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
  
 // Configure each stepper
  tongue_stepper.setMaxSpeed(300.0);
  tongue_stepper.setAcceleration(100.0);
  tongue_stepper.moveTo(0);
  
  jaw_stepper.setMaxSpeed(300.0);
  jaw_stepper.setAcceleration(100.0);
  jaw_stepper.moveTo(0);

  steppers.addStepper(tongue_stepper);
  steppers.addStepper(jaw_stepper);
  
  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  // nh.loginfo("SONO NEL LOOP");
  
//  tongue_stepper.moveTo(positions[0]);
//  jaw_stepper.moveTo(positions[1]);
//
//  tongue_stepper.run();
//  jaw_stepper.run();
  
//  tongue_stepper.runSpeedToPosition();
//  jaw_stepper.runSpeedToPosition();
  
  
  nh.spinOnce();
}
