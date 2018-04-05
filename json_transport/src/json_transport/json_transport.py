# Software License Agreement (BSD)
#
# \file      json_transport.py
# \authors   Paul Bovbel <pbovbel@locusrobotics.com>
# \copyright Copyright (c) (2018,), Locus Robotics, All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted
# provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of conditions
# and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice, this list of
# conditions and the following disclaimer in the documentation and/or other materials provided with
# the distribution.
# 3. Neither the name of the copyright holder nor the names of its contributors may be used to
# endorse or promote products derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
# IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
import rospy
import json

from json_msgs import msg as json_msg


class Publisher(rospy.Publisher):

    def __init__(self, *args, **kwargs):
        args = list(args)
        args.insert(1, json_msg.Json)
        super(Publisher, self).__init__(*args, **kwargs)

    def publish(self, *args, **kwargs):
        if len(args) == 1:
            data = args[0]
        elif args:
            data = args
        elif kwargs:
            data = kwargs
        else:
            super(Publisher, self).publish(*args, **kwargs)

        msg = json_msg.Json()
        msg.bytes = json.dumps(data)
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
        data = json.loads(msg.bytes)
        if cb_args is not None:
            callback(data, cb_args)
        else:
            callback(data)
    return wrapped
