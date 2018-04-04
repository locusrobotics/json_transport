import rospy
import ubjson

from json_msgs import msg as json_msg


class Publisher(rospy.Publisher):

    def __init__(self, *args, **kwargs):
        args = list(args)
        args.insert(1, json_msg.Json)
        super(Publisher, self).__init__(*args, **kwargs)

    def publish(self, *args, **kwargs):
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
        args = list(args)
        args.insert(1, json_msg.Json)

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
