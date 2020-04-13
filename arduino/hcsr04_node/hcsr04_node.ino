#include <ros.h>
#include <std_msgs/Float64.h>
#include <brain/hormone_msg.h>

ros::NodeHandle nh;
std_msgs::Float64 Distance;
ros::Publisher hcsr04_pub("hcsr04",&Distance);

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
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
float distance;

void setup() {
nh.initNode();
nh.advertise(hcsr04_pub);
nh.subscribe(hormone_sub);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(57600); // Starts the serial communication
}

void loop() {
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
distance= duration*0.034/2;
//publishing data

Distance.data=distance;
hcsr04_pub.publish(&Distance);
nh.spinOnce();
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
delay(100);
}
