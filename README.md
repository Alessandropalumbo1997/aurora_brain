# Aurora (beta version)

"Aurora" is a university project from Milan's IED's Media design course.

The code is written in ROS python

The "brain" package is a first test for a basic node/topic structure, supplied by custom ROS services and messages.
The main goal is to emulate the functionalities of a real brain.

The 4 hormones, epinephrine, dopamine, oxytocine and cortisol, inherit from Hormone class placed in the src/hormone folder.

## Usage

1. compile the package with catkin
2. start roscore
3. run the receptor:

`rosrun brain receptor`

4. run one or more hormones (located in /bin)

`rosrun brain <hormone_name>`

5. set the hormone values

`rosrun brain set_hormone_client.py <hormone_name> <value>`

6. You can check the situation by runnung:

`rosrun rqt_graph rqt_graph`

---

This code is being used for academic research

