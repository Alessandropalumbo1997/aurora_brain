#include <ros.h>
#include <brain/hcsr04_msg.h>
#include <brain/ky037_msg.h>
#include <brain/hormone_msg.h>
#include <brain/motor_cortex_msg.h>
#include <Stepper.h>

// #############################
// ######### CONSTANTS #########
// #############################

// const int SPR = 200; // Steps Per Revolution
const int STEPPERS = 2; // number of stepper motors
// const int PINS = STEPPERS * 4; // number of pins of stepper motors

// #############################
// ######### VARIABLES #########
// #############################

long del = 1500; // delay in microsecondi tra gli step 1, 2, 3 e 4 per ogni motore
int MP[STEPPERS][4] = {{10, 11, 12, 13}, {4, 5, 6, 7}};
// Stepper tongue_stepper = Stepper(SPR, MP[0][0], MP[0][1], MP[0][2], MP[0][3]);
// Stepper jaw_stepper = Stepper(SPR, MP[1][0], MP[1][1], MP[1][2], MP[1][3]);

// #############################
// ############ ROS ############
// #############################

// ######### Variables #########
ros::NodeHandle nh;

// ######### Callbacks #########
void stepper_callback(const brain::motor_cortex_msg &msg) {
  nh.loginfo("CACCHIO");

  int highest_impulse = 0;
  del = 1500 * STEPPERS;

  // riceviamo da ROS un array di 6 motori con impulsi (int) e direzioni (bool)
  // Qua vengono ciclati gli impulsi per ogni motore e viene ricavato il maggiore tra essi.
  for (int i = 0; i < STEPPERS; i++) {
    int impulse = msg.stepper_motors[i].impulse;
    if (impulse > highest_impulse) {
      highest_impulse = impulse;
    }
  }

  highest_impulse = map(highest_impulse, 0, 127, 0, 500);

  // La motor cortex in ROS manda valori di tipo int8 (max 127), quindi li rimappiamo singolarmente x avere un numero maggiore...
  // ...che porta conseguentemente a movimenti più lunghi
  // Tutto questo discorso è possibile xk conosciamo l'ordine preciso dei 6 motori all'interno del motor_cortex_msg
  // ORDINE DEI MOTORI:
  // 1. tongue
  // 2. jaw
  // 3. left_ear
  // 4. right_ear
  // 5. tail
  // 6. neck
  int tongue_impulse = map(msg.stepper_motors[0].impulse, 0, 127, 0, 500);
  int jaw_impulse = map(msg.stepper_motors[1].impulse, 0, 127, 0, 500);
  int left_ear_impulse = map(msg.stepper_motors[2].impulse, 0, 127, 0, 500);
  int right_ear_impulse = map(msg.stepper_motors[3].impulse, 0, 127, 0, 500);
  int tail_impulse = map(msg.stepper_motors[4].impulse, 0, 127, 0, 500);
  int neck_impulse = map(msg.stepper_motors[5].impulse, 0, 127, 0, 500);

  bool tongue_stopped = false;
  bool jaw_stopped = false;
  bool left_ear_stopped = false;
  bool righe_ear_stopped = false;
  bool tail_stopped = false;
  bool neck_stopped = false;


  // a questo punto faccio un ciclo che dura quanto l'impulso maggiore (cioè il motore che deve muoversi di più)
  // a ogni giro controllo se l'impulso per ogni motore è > 0
  // Se è true, allora vado a chiamare la funzione move_*nomestepper* passando il parametro forward di quel motore (bool) che serve per capire se devo andare avanti o indietro
  // Se è false, IL MOTORE INTERESSATO NON DOVREBBE MUOVERSI, MENTRE GLI ALTRI CHE HANNO ANCORA TRUE SI
  // Purtroppo però se mi trovo in una situazione in cui ho un motore con impulso > 0 (dovrebbe muoversi) e uno con impulso <= 0 (non dovrebbe muoversi)...
  // ... quello che dovrebbe muoversi invece si ferma insieme all'altro
  for (int i = 0; i <= highest_impulse; i++) {    
    if (tongue_impulse > 0) {
      nh.loginfo("TONGUE");
      move_tongue(msg.stepper_motors[0].forward);
      tongue_impulse--;
    } else if (!tongue_stopped && tongue_impulse <= 0) {
      del -= 1000;
      tongue_stopped = true;
    }
    
    if (jaw_impulse > 0) {
      nh.loginfo("JAW");
      move_jaw(msg.stepper_motors[1].forward);
      jaw_impulse--;
    }
    else if (!jaw_stopped && jaw_impulse <= 0) {
      del -= 1000;
      jaw_stopped = true;
    }
  }

  //    while (highest_impulse > 0) {
  //      move_steppers(msg.stepper_motors[0].forward, tongue_impulse,
  //                    msg.stepper_motors[1].forward, jaw_impulse,
  //                    msg.stepper_motors[2].forward, left_ear_impulse,
  //                    msg.stepper_motors[3].forward, right_ear_impulse,
  //                    msg.stepper_motors[4].forward, tail_impulse,
  //                    msg.stepper_motors[5].forward, neck_impulse);
  //
  //                    nh.loginfo("LOZZIO");
  //
  //      tongue_impulse--;
  //      jaw_impulse--;
  //      left_ear_impulse--;
  //      right_ear_impulse--;
  //      tail_impulse--;
  //      neck_impulse--;
  //      highest_impulse--;
  //      delay(10);
  //    }

  delay(1000);
}

// ######## Subscribers ########
ros::Subscriber<brain::motor_cortex_msg> stepper_sub("steppers", &stepper_callback);

// #############################
// ########## METHODS ##########
// #############################

//void move_steppers(bool tongue_f, int tongue_i,
//                   bool jaw_f, int jaw_i,
//                   bool left_ear_f, int left_ear_i,
//                   bool right_ear_f, int righe_ear_i,
//                   bool tail_f, int tail_i,
//                   bool neck_f, int neck_i) {
//
//  if (tongue_i > 0) tongue_stepper.step(tongue_f ? 1 : -1);
//  if (jaw_i > 0) jaw_stepper.step(jaw_f ? 1 : -1);
//  //  if (left_ear_i > 0) left_ear_stepper.step(left_ear_forward ? 1 : -1);
//  //  if (right_ear_i > 0) right_ear_stepper.step(right_ear_forward ? 1 : -1);
//  //  if (tail_i > 0) tail_stepper.step(tail_forward ? 1 : -1);
//  //  if (neck_i > 0) neck_stepper.step(neck_forward ? 1 : -1);
//
//}

// #############################
// ########### TONGUE ##########
// #############################

void tongue_1() {
  // 1
  digitalWrite(MP[0][0], LOW);
  digitalWrite(MP[0][1], HIGH);
  digitalWrite(MP[0][2], HIGH);
  digitalWrite(MP[0][3], LOW);
  delayMicroseconds(del);
}

void tongue_2() {
  // 2
  digitalWrite(MP[0][0], LOW);
  digitalWrite(MP[0][1], HIGH);
  digitalWrite(MP[0][2], LOW);
  digitalWrite(MP[0][3], HIGH);
  delayMicroseconds(del);
}

void tongue_3() {
  // 3
  digitalWrite(MP[0][0], HIGH);
  digitalWrite(MP[0][1], LOW);
  digitalWrite(MP[0][2], LOW);
  digitalWrite(MP[0][3], HIGH);
  delayMicroseconds(del);
}

void tongue_4() {
  // 4
  digitalWrite(MP[0][0], HIGH);
  digitalWrite(MP[0][1], LOW);
  digitalWrite(MP[0][2], HIGH);
  digitalWrite(MP[0][3], LOW);
  delayMicroseconds(del);
}

void tongue_0() {
  digitalWrite(MP[0][0], LOW);
  digitalWrite(MP[0][1], LOW);
  digitalWrite(MP[0][2], LOW);
  digitalWrite(MP[0][3], LOW);
}

// Questa funzione riceve in input il boolean che indica la direzione ed esegue le funzioni 1, 2, 3, 4 per ogni motore, oppure le fa al contrario se devo andare all'indietro
void move_tongue(bool tongue_f) {
  if (tongue_f) {
    tongue_1();
    tongue_2();
    tongue_3();
    tongue_4();
  } else {
    tongue_4();
    tongue_3();
    tongue_2();
    tongue_1();
  }
}

// #############################
// ############ JAW ############
// #############################

void jaw_1() {
  // 1
  digitalWrite(MP[1][0], LOW);
  digitalWrite(MP[1][1], HIGH);
  digitalWrite(MP[1][2], HIGH);
  digitalWrite(MP[1][3], LOW);
  delayMicroseconds(del);
}

void jaw_2() {
  // 2
  digitalWrite(MP[1][0], LOW);
  digitalWrite(MP[1][1], HIGH);
  digitalWrite(MP[1][2], LOW);
  digitalWrite(MP[1][3], HIGH);
  delayMicroseconds(del);
}

void jaw_3() {
  // 3
  digitalWrite(MP[1][0], HIGH);
  digitalWrite(MP[1][1], LOW);
  digitalWrite(MP[1][2], LOW);
  digitalWrite(MP[1][3], HIGH);
  delayMicroseconds(del);
}

void jaw_4() {
  // 4
  digitalWrite(MP[1][0], HIGH);
  digitalWrite(MP[1][1], LOW);
  digitalWrite(MP[1][2], HIGH);
  digitalWrite(MP[1][3], LOW);
  delayMicroseconds(del);
}

void jaw_0() {
  // 4
  digitalWrite(MP[1][0], LOW);
  digitalWrite(MP[1][1], LOW);
  digitalWrite(MP[1][2], LOW);
  digitalWrite(MP[1][3], LOW);
}

void move_jaw(bool jaw_f) {
  if (jaw_f) {
    jaw_1();
    jaw_2();
    jaw_3();
    jaw_4();
  } else {
    jaw_4();
    jaw_3();
    jaw_2();
    jaw_1();
  }
}

void setup() {
  // initialize ROS stuff
  nh.initNode();
  nh.subscribe(stepper_sub);

  //  tongue_stepper.setSpeed(80);
  //  jaw_stepper.setSpeed(80);
  //  left_ear_stepper.setSpeed(80);
  //  right_ear_stepper.setSpeed(80);
  //  tail_stepper.setSpeed(80);
  //  neck_stepper.setSpeed(80);

  Serial.begin(500000); // Starts the serial communication
}

void loop() {
  nh.spinOnce();
}
