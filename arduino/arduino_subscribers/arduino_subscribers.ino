#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <brain/motor_cortex_msg.h>
#include <Stepper.h>

// defines pins
const int echoPin = 9;
const int trigPin = 8;

const int m1 = 7;
const int m2 = 6;
const int m3 = 5;
const int m4 = 4;

// defines variables
long duration;
float distance;

int motor_delay = 5;
const int sPR = 200; // Steps Per Revolution
const int steppers_count = 6;

int ky037_value = 0;
int ky037_abs_value = 0;
int ky037_thereshold = 552;
const int ky037_count = 2;

// defines motor object with the four IN pins
Stepper tongue_stepper = Stepper(sPR, m1, m2, m3, m4);
// Stepper tongue_stepper = Stepper(sPR, m5, m6, m7, m8);
// ...
// Stepper steppers = [tongue_stepper, jaw_stepper, left_ear_stepper, right_ear_stepper, tail_stepper, neck_stepper]

// Define ros variables
ros::NodeHandle nh;
brain::motor_cortex_msg Steppers;

// Callbacks
void stepper_callback(const brain::motor_cortex_msg &msg) {
  nh.loginfo("IN CALLBACK");
  if (msg.stepper_motors[0].impulse == 1) {
    tongue_stepper.step(sPR);
    delay(motor_delay);
  }
  else if (msg.stepper_motors[0].impulse == -1) {
    tongue_stepper.step(-sPR);
    delay(motor_delay);
  }
}

// Subscribers
ros::Subscriber<brain::motor_cortex_msg> stepper_sub("steppers", &stepper_callback);

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.subscribe(stepper_sub);

  // set pin modes
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output

  tongue_stepper.setSpeed(120);

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  nh.spinOnce();
}
