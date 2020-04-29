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

const int SPR = 180; // Steps Per Revolution
const int STEPPERS = 3;
const int MP[STEPPERS*4] = {13, 12, 53, 51, 11, 10, 47, 45, 9, 8, 41, 39};
// const int MP[4] = {13, 12, 53, 51};

// #############################
// ######### VARIABLES #########
// #############################

// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper tongue_stepper(AccelStepper::FULL4WIRE, MP[0], MP[1], MP[2], MP[3]);
AccelStepper jaw_stepper(AccelStepper::FULL4WIRE, MP[4], MP[5], MP[6], MP[7]);
AccelStepper left_ear_stepper(AccelStepper::FULL4WIRE, MP[8], MP[9], MP[10], MP[11]);

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
  nh.loginfo("CACCHIO");
  for (int i = 0; i < STEPPERS; i++) {
    if (msg.stepper_motors[i].impulse == 0)
      positions[i] = 0;
    else if (msg.stepper_motors[i].impulse == 1) {
      positions[i] = 600;
      nh.loginfo("FORWARD ->");
    }
    else if (msg.stepper_motors[i].impulse == -1) {
      positions[i] = -600;
      nh.loginfo("<- BACKWARD");
    }
  }

  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
//  nh.spinOnce();
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
  // tongue_stepper.run();
  
  jaw_stepper.setMaxSpeed(300.0);
  jaw_stepper.setAcceleration(100.0);
  jaw_stepper.moveTo(0);

  left_ear_stepper.setMaxSpeed(300.0);
  left_ear_stepper.setAcceleration(100.0);
  left_ear_stepper.moveTo(0);

  steppers.addStepper(tongue_stepper);
  steppers.addStepper(jaw_stepper);
  steppers.addStepper(left_ear_stepper);
  // steppers.runSpeedToPosition();

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  nh.spinOnce();
}
