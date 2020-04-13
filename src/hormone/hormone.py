#! /usr/bin/env python

import roslib
import rospy
from std_msgs.msg import String
from brain.msg import hormone_msg
from brain.srv import SetHormone, SetHormoneResponse

class Hormone:
    def __init__(self, name, val):
        self.name = name
        self.value = val
        self.old_value = self.value
        self.pub = rospy.Publisher('hormones', hormone_msg, queue_size=10)
        self.msg = hormone_msg()

    def hormonize(self):
        rospy.init_node("{}_node".format(self.name), anonymous=True)
        # rate = rospy.Rate(0.5) # 5hz
        s = rospy.Service('{}/set_hormone_srv'.format(self.name), SetHormone, self.set_values)
        while not rospy.is_shutdown():
            # if self.value != self.old_value:
            # rate.sleep()
            rospy.spin()

    def set_values(self, req):
        if self.name == req.name:
            if self.value != req.value:
                self.value = req.value
                self.old_value = self.value
                self.msg.name = self.name
                self.msg.value = self.value
                rospy.loginfo(self.msg)
                self.pub.publish(self.msg)
                print("New value for {}: {}".format(self.name, self.value))
            else:
                print("Please enter a different value from the current one")
        else:
            print("No hormone named {}".format(req.name))

        return SetHormoneResponse(self.value)
