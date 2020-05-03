#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <brain/motor_cortex_msg.h>

// #############################
// ######### CONSTANTS #########
// #############################

const int SPR = 180; // Steps Per Revolution
const int STEPPERS = 2; // number of stepper motors
// const int PINS = STEPPERS * 4; // number of pins of stepper motors
int MP[STEPPERS][4] = {{10, 11, 12, 13}, {6, 7, 8, 9}};

// #############################
// ######### VARIABLES #########
// #############################

long del = 1500; // delay in microseconds

// #############################
// ############ ROS ############
// #############################

// ######### Variables #########
ros::NodeHandle nh;

// ######### Callbacks #########
void stepper_callback(const brain::motor_cortex_msg &msg) {
  nh.loginfo("CACCHIO");

  for (int j = 0; j < STEPPERS; j++) {
    int impulse = map(msg.stepper_motors[j].impulse, 0, 127, 0, 500);
    nh.loginfo("SONO UN CAzzo DI MOTORE");

    for (int i = 0; i <= impulse; i++) {
      if (msg.stepper_motors[j].forward == 1) {
        one(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
        two(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
        three(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
        four(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
      }
      else if (msg.stepper_motors[j].forward == 0) {
        four(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
        three(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
        two(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
        one(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
      }
    }

    zero(MP[j][0], MP[j][1], MP[j][2], MP[j][3]);
  }

  delay(1000);
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

  // initialize all stepper pins
  for (int i = 0; i < STEPPERS; i++) {
    pinMode(MP[i][0], OUTPUT);
    pinMode(MP[i][1], OUTPUT);
    pinMode(MP[i][2], OUTPUT);
    pinMode(MP[i][3], OUTPUT);
  }

  Serial.begin(500000); // Starts the serial communication
}

void zero(int A, int B, int C, int D) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
}
void one(int A, int B, int C, int D) {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  delayMicroseconds(del);
}
void two(int A, int B, int C, int D) {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  delayMicroseconds(del);
}
void three(int A, int B, int C, int D) {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  delayMicroseconds(del);
}
void four(int A, int B, int C, int D) {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  delayMicroseconds(del);
}

void loop() {
  nh.spinOnce();
}
