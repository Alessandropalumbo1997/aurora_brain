#include <ros.h>
#include <brain/motor_cortex_msg.h>

// #############################
// ######### CONSTANTS #########
// #############################

const int STEPPERS = 3; // number of stepper motors
const int MP[STEPPERS][4] = {{10, 11, 12, 13}, {6, 7, 8, 9}, {2, 3, 4, 5}};
const int del = 1500;

// #############################
// ######### VARIABLES #########
// #############################

int cycle_sequence[STEPPERS][500];
int cycle_counter[STEPPERS];
int motor_impulse[STEPPERS];

// #############################
// ############ ROS ############
// #############################

// ######### Variables #########
ros::NodeHandle nh;

// ######### Callbacks #########
void stepper_callback(const brain::motor_cortex_msg &msg) {
  nh.loginfo("CACCHIO");
  for (int i = 0; i < STEPPERS; i++) {
    // int impulse = map(msg.stepper_motors[i].impulse, 0, 127, 0, 500);
    motor_impulse[i] = msg.stepper_motors[i].impulse;
    initializeMovementSequence(msg.stepper_motors[i].index, msg.stepper_motors[i].impulse);
  }
}

// ######## Subscribers ########
ros::Subscriber<brain::motor_cortex_msg> stepper_sub("steppers", &stepper_callback);

// #############################
// ########## METHODS ##########
// #############################

// when we receive a message from ros we initialize a sequence of steps
int j = 0;
void initializeMovementSequence(int motor, int steps) {
  if (steps > 0) {
    nh.loginfo("AVANTI");
    j = 1;
    for (int i = 0; i < steps * 4; i++) {
      if (j > 4) {
        j = 1;
      }
      // building motor sequence, result will be 0 1 2 3 0 1 2 3 ...
      cycle_sequence[motor][i] = j;
      j++;
    }
  }
  else if (steps < 0) {
    nh.loginfo("INDIETRO");
    j = 4;
    for (int i = 0; i < abs(steps * 4); i++) {
      if (j < 1) {
        j = 4;
      }
      // building motor sequence, result will be 3 2 1 0 3 2 1 0 ...
      cycle_sequence[motor][i] = j;
      j--;
    }
  }
}

void cycle(int motorIndex, int cycleIndex) {
  if (cycleIndex == 1) {
    digitalWrite(MP[motorIndex][0], LOW);
    digitalWrite(MP[motorIndex][1], HIGH);
    digitalWrite(MP[motorIndex][2], HIGH);
    digitalWrite(MP[motorIndex][3], LOW);
  }
  else if (cycleIndex == 2) {
    digitalWrite(MP[motorIndex][0], LOW);
    digitalWrite(MP[motorIndex][1], HIGH);
    digitalWrite(MP[motorIndex][2], LOW);
    digitalWrite(MP[motorIndex][3], HIGH);
  }
  else if (cycleIndex == 3) {
    digitalWrite(MP[motorIndex][0], HIGH);
    digitalWrite(MP[motorIndex][1], LOW);
    digitalWrite(MP[motorIndex][2], LOW);
    digitalWrite(MP[motorIndex][3], HIGH);
  }
  else if (cycleIndex == 4) {
    digitalWrite(MP[motorIndex][0], HIGH);
    digitalWrite(MP[motorIndex][1], LOW);
    digitalWrite(MP[motorIndex][2], HIGH);
    digitalWrite(MP[motorIndex][3], LOW);
  }
  else if (cycleIndex == 0) {
    digitalWrite(MP[motorIndex][0], LOW);
    digitalWrite(MP[motorIndex][1], LOW);
    digitalWrite(MP[motorIndex][2], LOW);
    digitalWrite(MP[motorIndex][3], LOW);
  }
}

void step() {
  // TONGUE MOTOR
  if (cycle_counter[0] < motor_impulse[0] * 4) {
    cycle_counter[0]++;
    cycle(0, cycle_sequence[0][cycle_counter[0]]);
  }
  else {
    cycle_counter[0] = 0;
    memset(cycle_sequence[0], 0, sizeof(cycle_sequence[0]));
  }

  // JAW MOTOR
  if (cycle_counter[1] < motor_impulse[1] * 4) {
    cycle_counter[1]++;
    cycle(1, cycle_sequence[1][cycle_counter[1]]);
  }
  else {
    cycle_counter[1] = 0;
    memset(cycle_sequence[1], 0, sizeof(cycle_sequence[1]));
  }

  // LEFT EAR MOTOR
  if (cycle_counter[2] < motor_impulse[2] * 4) {
    cycle_counter[2]++;
    cycle(2, cycle_sequence[2][cycle_counter[2]]);
  }
  else {
    cycle_counter[2] = 0;
    memset(cycle_sequence[2], 0, sizeof(cycle_sequence[2]));
  }

//  // RIGHT EAR MOTOR
//  if (cycle_counter[3] < motor_impulse[3] * 4) {
//    cycle_counter[3]++;
//    cycle(3, cycle_sequence[3][cycle_counter[3]]);
//  }
//  else {
//    cycle_counter[3] = 0;
//    memset(cycle_sequence[3], 0, sizeof(cycle_sequence[3]));
//  }
  
  delayMicroseconds(del);
  nh.spinOnce();
}

void setup() {
  nh.initNode();
  nh.subscribe(stepper_sub);

  for (int i = 0; i < STEPPERS; i++) {
    pinMode(MP[i][0], OUTPUT);
    pinMode(MP[i][1], OUTPUT);
    pinMode(MP[i][2], OUTPUT);
    pinMode(MP[i][3], OUTPUT);
  }

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  step();
}
