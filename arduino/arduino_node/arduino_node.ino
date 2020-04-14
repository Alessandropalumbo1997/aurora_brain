// RIGHE DA SCOMMENTARE:
// - La riga di inclusione di hcsr04_msg qua sotto
// - Le due righe sotto "ros::NodeHandle nh;"
// - Nel metodo void setup() la seguente riga "nh.advertise(hcsr04_pub);"
// - Nel metodo float hcsr04() le 4 righe sopra "nh.spinOnce();"
// PORCODIO


#include <ros.h>
// #include <brain/hcsr04_msg.h>
#include <brain/hormone_msg.h>
#include <Stepper.h>

ros::NodeHandle nh;
//brain::hcsr04_msg Msg;
//ros::Publisher hcsr04_pub("hcsr04", &Msg);

String hormone_name;

void hormoneCb(const brain::hormone_msg &msg) {
  hormone_name = msg.name;
  if (hormone_name == "dopamine") {
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
int motorDelay = 500;
const int sPR = 200; // Steps per revolution

// defines motor object with the four IN pins
Stepper motor = Stepper(sPR, m1, m2, m3, m4);

void setup() {
  // initialize ROS stuff
  nh.initNode();
  // nh.advertise(hcsr04_pub);
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
  // Msg.name = "lateral_left";
  // Msg.distance = distance;
  // Msg.approaching_speed = 0;
  // hcsr04_pub.publish(&Distance);
  nh.spinOnce();
  delay(100);
  return distance;
}

float motorControl(float dist) {
  if (dist <= 15) {
    motor.step(sPR);
    delay(motorDelay);
  }
}
