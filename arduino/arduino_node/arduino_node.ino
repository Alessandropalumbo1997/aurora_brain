#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <Stepper.h>

// Define ros variables
ros::NodeHandle nh;
brain::hcsr04_msg Hcsr04_msg;
ros::Publisher hcsr04_pub("hcsr04", &Hcsr04_msg);
brain::ky037_msg Ky037_msg;
ros::Publisher ky037_pub("ky037", &Ky037_msg);

//==== ESEMPIO SUBSCRIBER E CALLBACK ====
      //
      //String hormone_name;
      //
      //void hormoneCb(const brain::hormone_msg &msg) {
      //  hormone_name = msg.name;
      //  if (hormone_name == "dopamine") {
      //    digitalWrite(LED_BUILTIN, HIGH);
      //    delay(100);
      //    digitalWrite(LED_BUILTIN, LOW);
      //    delay(100);
      //  } else {
      //    digitalWrite(LED_BUILTIN, HIGH);
      //    delay(1000);
      //    digitalWrite(LED_BUILTIN, LOW);
      //    delay(1000);
      //  }
      //}
      //
      //ros::Subscriber<brain::hormone_msg> hormone_sub("hormones", &hormoneCb);
      //
//=======================================


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

int motor_delay = 500;
const int sPR = 200; // Steps Per Revolution

int ky037_value = 0;
int ky037_abs_value = 0;
int ky037_thereshold = 552;

// defines motor object with the four IN pins
Stepper motor = Stepper(sPR, m1, m2, m3, m4);

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.advertise(hcsr04_pub);
  nh.advertise(ky037_pub);
  // nh.subscribe(hormone_sub);

  // set pin modes
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output

  motor.setSpeed(50);

  Serial.begin(57600); // Starts the serial communication
}

void loop() {
  hcsr04();
  ky037();
  motor_control();
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
  // Read analog output pin
  ky037_value = analogRead(A0);
  
  // Calculate absolute value
  ky037_abs_value = abs(ky037_value - ky037_thereshold);

  // Publishing data
  Ky037_msg.name = "micro_left";
  Ky037_msg.loudness = ky037_abs_value;
  ky037_pub.publish(&Ky037_msg);
  nh.spinOnce();
  delay(10);
}

void motor_control() {
  if (distance <= 100) { // ~ 1 metro 
    motor.step(sPR);
    delay(motor_delay);
  }
}
