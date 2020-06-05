#include <ros.h>
#include <Stepper.h>
#include <brain/motor_cortex_msg.h>

// #############################
// ######### CONSTANTS #########
// #############################

const int SPR = 2048; // Steps Per Revolution
const int STEPPERS = 3; // number of stepper motors
// const int PINS = STEPPERS * 4; // number of pins of stepper motors
// int MP[STEPPERS][4] = {{10, 11, 12, 13}, {6, 7, 8, 9}, {2, 3, 4, 5}};

// #############################
// ######### VARIABLES #########
// #############################

int highest = 0;
long del = 1500; // delay in microseconds
Stepper tongue_step(SPR, 10, 11, 12, 13);
Stepper jaw_step(SPR, 6, 7, 8, 9);
Stepper lear_step(SPR, 2, 3, 4, 5);

// #############################
// ############ ROS ############
// #############################

// ######### Variables #########
ros::NodeHandle nh;

// ######### Callbacks #########
void stepper_callback(const brain::motor_cortex_msg &msg) {
  //nh.loginfo("CACCHIO");
  highest = 0;
  
  for (int j = 0; j < STEPPERS; j++) {
    // int impulse = map(msg.stepper_motors[j].impulse, 0, 127, 0, 500);
    int impulse = msg.stepper_motors[j].impulse;
    if (impulse > highest) {
      highest = impulse;
    }
  }
}

// ######## Subscribers ########
ros::Subscriber<brain::motor_cortex_msg> stepper_sub("steppers", &stepper_callback);

// #############################
// ########## METHODS ##########
// #############################

void setup() {  
  // initialize ROS stuff
  nh.initNode();
  nh.subscribe(stepper_sub);
  
  tongue_step.setSpeed(22);
  jaw_step.setSpeed(22);
  lear_step.setSpeed(22);

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  if (highest > 0) {
    for (int i = 0; i <= SPR; i++) {
      tongue_step.step(1);
      jaw_step.step(1);
      lear_step.step(1);  
    }
    highest--;
  }
  nh.spinOnce();
}
