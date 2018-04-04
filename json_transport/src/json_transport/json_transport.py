import rospy
import ubjson

from json_msg import msg as json_msg


class Publisher(rospy.Publisher):

    def __init__(self, *args, **kwargs):
        try:
            args[2] = 'json_msgs/Json'
        except IndexError:
            kwargs['data_class'] = 'json_msgs/Json'

        super(Publisher, self).__init__(*args, **kwargs)

    def publish(self, *args, **kwargs):
        # encoded = ubjson.dumpb({u'a': 1})
        if len(args) == 1:
            data = args[0]
        elif kwargs:
            data = kwargs
        else:
            super(Publisher, self).publish(*args, **kwargs)

        msg = json_msg.Json()
        msg.bytes = ubjson.dumpb(data)
        super(Publisher, self).publish(msg)


class Subscriber(rospy.Subscriber):

    def __init__(self, *args, **kwargs):
        try:
            callback = args[2]
            args[2] = _wrap_callback(callback)
        except IndexError:
            pass

        try:
            callback = kwargs['callback']
            kwargs['callback'] = _wrap_callback(callback)
        except KeyError:
            pass

        super(Subscriber, self).__init__(*args, **kwargs)


def _wrap_callback(callback):
    def wrapped(msg, cb_args=None):
        data = ubjson.loadb(msg.bytes)
        if cb_args is not None:
            callback(data, cb_args)
        else:
            callback(data)
    return wrapped
