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

// Publishers
brain::hcsr04_msg Hcsr04_msg;
ros::Publisher hcsr04_pub("hcsr04", &Hcsr04_msg);
brain::ky037_msg Ky037_msg;
ros::Publisher ky037_pub("ky037", &Ky037_msg);

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
  nh.advertise(hcsr04_pub);
  nh.advertise(ky037_pub);
  nh.subscribe(stepper_sub);

  // set pin modes
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output

  tongue_stepper.setSpeed(120);

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  hcsr04();
  ky037();
}

void hcsr04() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  //publishing data
  Hcsr04_msg.name = "lateral_left";
  Hcsr04_msg.distance = (int) distance;
  Hcsr04_msg.approaching_speed = 0;
  hcsr04_pub.publish(&Hcsr04_msg);
  nh.spinOnce();
  delay(10);
}

void ky037() {
  for (int i = 0; i < ky037_count; i++) {
    // Read analog output pin
    ky037_value = i==0 ? analogRead(A0) : analogRead(A1);
    
    // Calculate absolute value
    ky037_abs_value = abs(ky037_value - ky037_thereshold);
  
    // Building msg
    Ky037_msg.name = i==0 ? "micro_left" : "micro_right";
    Ky037_msg.loudness = ky037_abs_value;

    // Publish msg
    ky037_pub.publish(&Ky037_msg);
  }
  nh.spinOnce();
  delay(10);
}
