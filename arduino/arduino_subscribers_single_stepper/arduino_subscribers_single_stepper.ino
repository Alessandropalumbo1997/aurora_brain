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
int MP[4] = {0, 1, 2, 3};
int A = 10;
int B = 11;
int C = 12;
int D = 13;

// #############################
// ######### VARIABLES #########
// #############################

boolean increase = true;
long positions[STEPPERS];
long del = 1500; // delay in microseconds
int motor_delay = 5;

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
    one();
    two();
    three();
    four();
    nh.loginfo("VAFFANCULO");
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

  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT); 
  
  Serial.begin(500000); // Starts the serial communication
}

void one(){
  digitalWrite(A, LOW);   
  digitalWrite(B, HIGH);   
  digitalWrite(C, HIGH);   
  digitalWrite(D, LOW);   
  delayMicroseconds(del);
}
void two(){
  digitalWrite(A, LOW);   
  digitalWrite(B, HIGH);   
  digitalWrite(C, LOW);   
  digitalWrite(D, HIGH);   
  delayMicroseconds(del);
}
void three(){
  digitalWrite(A, HIGH);   
  digitalWrite(B, LOW);   
  digitalWrite(C, LOW);   
  digitalWrite(D, HIGH);   
  delayMicroseconds(del);
}
void four(){
  digitalWrite(A, HIGH);   
  digitalWrite(B, LOW);   
  digitalWrite(C, HIGH);   
  digitalWrite(D, LOW);   
  delayMicroseconds(del);
}
void motorOff(){
  digitalWrite(A, LOW);   
  digitalWrite(B, LOW);   
  digitalWrite(C, LOW);   
  digitalWrite(D, LOW);   
}

void loop() {
//   for (int i=0; i<=510; i++){
//    een(); 
//    twee();
//    drie();
//    vier();
//  }
//  motorOff();
//  
//  delay(2000);
  
  nh.spinOnce();
}
