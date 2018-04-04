#!/usr/bin/env python
import rospy
import json_transport


def callback(data):
    rospy.loginfo("Received {}".format(data))


if __name__ == '__main__':
    rospy.init_node('listener', anonymous=True)
    json_transport.Subscriber('json', callback=callback)
    rospy.spin()
