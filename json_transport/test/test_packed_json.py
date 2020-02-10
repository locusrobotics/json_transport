#!/usr/bin/env python
# Software License Agreement (BSD)
#
# \file      test_packed_json
# \authors   Andrew Blakey <ablakey@locusrobotics.com>
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
import json_transport
import unittest


TEST_DATA = [
    ["a", "json", "array"],
    {"a": "json", "object": ["with", "nested", False, 1.23]},
    0,
    1,
    True,
    False,
    None
]


class TestPackedJson(unittest.TestCase):

    def test_init_packed_json(self):
        for d in TEST_DATA:
            msg = json_transport.PackedJson(d)
            self.assertEquals(d, msg.data)

    def test_init_packed_json_schema(self):
        data = ["a", "json", "array"]

        json_transport.PackedJson(data=data, schema={"maxItems": 3})

        with self.assertRaises(json_transport.ValidationError):
            json_transport.PackedJson(data=data, schema={"maxItems": 2})


if __name__ == '__main__':
    import rosunit
    rosunit.unitrun('json_transport', 'test_packed_json', TestPackedJson)
