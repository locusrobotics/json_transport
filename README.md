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

rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("json_talker");
auto publisher = node->create_publisher<json_transport::json_t>(
    "json", rclcpp::QoS(1).transient_local().reliable());
publisher->publish(sent);

json_transport::json_t received;
bool got_message = false;
auto sub = node->create_subscription<json_transport::json_t>(
    "json", rclcpp::QoS(1).transient_local().reliable(),
    [&](const json_transport::json_t & msg) {
      received = msg;
      got_message = true;
    });

while (rclcpp::ok() && !got_message) {
  rclcpp::spin_some(node);
}

assert(received == sent);
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
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

rclpy.init()
node = Node('json_talker')

qos = QoSProfile(
  depth=1,
  durability=DurabilityPolicy.TRANSIENT_LOCAL,
  reliability=ReliabilityPolicy.RELIABLE,
)
pub = node.create_publisher(json_transport.PackedJson, 'json', qos)

pub.publish(json_transport.PackedJson(1))
pub.publish(json_transport.PackedJson([1, 2, 3]))
pub.publish(json_transport.PackedJson({'a': 1, 'b': 2, 'c': 3}))

msg = None

def callback(incoming):
  global msg
  msg = incoming

sub = node.create_subscription(json_transport.PackedJson, 'json', callback, qos)
while rclpy.ok() and msg is None:
  rclpy.spin_once(node, timeout_sec=0.1)

assert msg.data == {'a': 1, 'b': 2, 'c': 3}
```

Nested `json_msg/Json` types can be packed/unpacked via helper methods:

```
msg = MyCustomMessage(
    json_field=json_transport.pack(serializable_data)
)

assert serializable_data == json_transport.unpack(msg.json_field)
```
