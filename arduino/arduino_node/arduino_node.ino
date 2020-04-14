#include <ros.h>
#include <std_msgs/Float64.h>
#include <brain/hormone_msg.h>
#include <Stepper.h>

ros::NodeHandle nh;
std_msgs::Float64 Distance;
ros::Publisher hcsr04_pub("hcsr04", &Distance);

String name;

void hormoneCb(const brain::hormone_msg &msg) {
  name = msg.name;
  if (name == "dopamine") {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}

ros::Subscriber<brain::hormone_msg> hormone_sub("hormones", &hormoneCb);

// defines pins numbers
const int m1 = 2;
const int m2 = 3;
const int m3 = 4;
const int m4 = 5;
const int trigPin = 8;
const int echoPin = 9;

// defines variables
long duration;
float distance;
int motorSpeed = 2;
const int sPR = 200; // Steps per revolution

// defines motor object with the four IN pins
Stepper motor = Stepper(sPR, m1, m2, m3, m4);

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.advertise(hcsr04_pub);
  nh.subscribe(hormone_sub);

  // set pin modes
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(LED_BUILTIN, OUTPUT);

  
  motor.setSpeed(50);
  
  Serial.begin(57600); // Starts the serial communication
}

void loop() {
  distance = hcsr04();
  motorControl(distance);
}

float hcsr04() {
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
  Distance.data = distance;
  hcsr04_pub.publish(&Distance);
  nh.spinOnce();
  // Serial.println(distance);
  delay(100);
  return distance;
}

float motorControl(float dist) {
  if (dist <= 15) {
    motor.step(sPR);
    // delay(500);
  }
}
