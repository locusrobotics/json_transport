# json_transport

[![Build Status](https://travis-ci.org/locusrobotics/json_transport.svg?branch=devel)](https://travis-ci.org/locusrobotics/json_transport)

Providing schemaless transport over ROS pub/sub via JSON. This is useful when schema is enforced elsewhere, or the data is truly schemaless (i.e. parameters, diagnostics).

## C++

The provided serializers allow publishing and subscribing `json_transport::json_t` datatypes, which are [`nlohmann::json`](https://github.com/nlohmann/json) under the hood.

The [`nlohmann/json.hpp`](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp) library is bundled in, but can be dropped for an apt dependency in artful, or if the package is bloomed into the rosdistro.

```
#include "json_transport/json_transport.hpp"

json_transport::json_t sent = {
  {"this_is_json", true},
  {"pi", 3.141},
  {"list_of_plugins", {
    "every_kind",
    "of_plugin",
    "you_can_imagine"
  }},
};

ros::NodeHandle nh;
auto publisher = nh.advertise<json_transport::json_t>("json", 1, true);
publisher.publish(sent);

auto received = ros::topic::waitForMessage<json_transport::json_t>("json");

assert(*received == sent);
```

Nested `json_msg/Json` types can be packed/unpacked via helper methods:

```
MyCustomMessage message();
message.json_field = json_transport::pack(json_data)

assert(json_data == json_transport::unpack(message.json_field))
```


## Python

The provided `json_transport.PackedJson` data type allows publishing and subscribing anything that can be serialized/deserialized natively via the stdlib `json` module.

```
import json_transport
import rospy

rospy.init_node('json_talker')
pub = rospy.Publisher('json', json_transport.PackedJson, queue_size=1, latch=True)
pub.publish(1)
pub.publish([1, 2, 3])
pub.publish({'a': 1, 'b': 2, 'c': 3})

msg = rospy.wait_for_message('json', json_transport.PackedJson)

assert msg.data == {'a': 1, 'b': 2, 'c': 3}
```

Nested `json_msg/Json` types can be packed/unpacked via helper methods:

```
msg = MyCustomMessage(
    json_field=json_transport.pack(serializable_data)
)

assert serializable_data == json_transport.unpack(msg.json_field)
```
