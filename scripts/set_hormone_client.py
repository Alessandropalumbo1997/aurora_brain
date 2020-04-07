#!/usr/bin/env python

import sys
import rospy
from brain.srv import *

def set_hormone_client(name, val):
    rospy.wait_for_service('{}/set_hormone_srv'.format(name))
    try:
        hormone_srv = rospy.ServiceProxy('{}/set_hormone_srv'.format(name), SetHormone)
        resp1 = hormone_srv(name, val)
        return resp1.new_value
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

# this function is called if the script is executed
# with the wrong number of arguments
def usage():
    return "%s [name] [val]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 3:
        name = str(sys.argv[1])
        val = int(sys.argv[2])
    else:
        print usage()
        sys.exit(1)
    print "Requesting value change for %s"%(name)
    set_hormone_client(name, val)
    # print "Set new value for \'%s\': %s"%(name, set_hormone_client(name, val))