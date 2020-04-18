#! /usr/bin/env python

import roslib
import rospy

class Personality:

    # Aurora brain is tuned to support values between 1 and 10, with other values the behaviour will be highly unpredictable

    """
    This regulates how much epinephrine the amygdala secretes in a fight or flight scenario
    - a higher value will get the dog scared at everything, a dreadful life in constant fear
    - a lower value will produce a very brave (but sometimes in a dangerous way) dog
    """
    amygdala_sensitivity = 5;

    """
    This regulates how much oxytocin the hypothalamus secretes in the affection response
    - a higher value will get the dog always wanting affection and more scared when left alone
    - a lower value will produce a very dog that could very well live without anyone (basically a psycho)
    """
    loving_parameter = 5;

    """
    This regulates how much dopamine the hypothalamus secretes in the motivation response
    - a higher value will produce a VERY active dog, you will hanker to shut it down
    - a lower value will produce a dog that will want to just sleep all day (basically a slacker)
    """
    motivation_parameter = 5;

    """
    This regulates how much cortisol the hypothalamus secretes in the stress response
    - a higher value will produce a dog that will easily develop depression (don't do that please)
    - a lower value will produce a dog that would witness the apocalypse from the sofa, with a beer and a joint
    """
    stress_parameter = 5;

    """
    This regulates how fast the hippocampus associates memories
    - a higher value will produce a really responsive dog, that will inevitably become very confused at what is good and what is bad because everything can change rapidly
    - a lower value will produce a dog that would need to see a tiger 10 times before he understands that he should run the fuck away from it
    """
    hippocampus_sensitivity = 5;
