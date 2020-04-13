# Aurora (beta version)

"Aurora" is a university project from Milan's IED's Media design course.

The code is written in ROS python

The "brain" package is a first test for a basic node/topic structure, supplied by custom ROS services and messages.
The main goal is to emulate the functionalities of a real brain.

The 4 hormones, epinephrine, dopamine, oxytocine and cortisol, inherit from Hormone class placed in the src/hormone folder.

## Usage

### Common steps

1. compile the package with catkin
2. start roscore

### hormones

1. run the receptor:

`rosrun brain hormone_receptor`

2. run one or more hormones (located in /bin)

`rosrun brain <hormone_name>`

3. set the hormone values

`rosrun brain set_hormone_client.py <hormone_name> <value>`

4. You can check the situation by running:

`rosrun rqt_graph rqt_graph`


### HC-SR04 ultrasonic sensor

1. set up your arduino IDE and install rosserial from here:

http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

2. upload the hcsr04_node sketch (located in /arduino) on your arduino board

3. run rosserial

`rosrun rosserial_python serial_node.py /dev/ttyUSB0`

4. run the receptor

`rosrun brain hcsr04_receptor`



### Auditory cortex

1. clone the auditory cortex repo:

https://github.com/leonardopaglia/aurora_auditory_cortex

2. launch the auditory cortex (command specified in its readme)

3. run the receptor

`rosrun brain auditory_cortex_receptor`

---

This code is being used for academic research
