#!/usr/bin/env python
import rospy
import json_transport

if __name__ == '__main__':
    rospy.init_node('json_talker')
    pub = json_transport.Publisher('json', queue_size=1, latch=True)
    pub.publish({
        'this_is_json': 42
    })
    rospy.spin()
