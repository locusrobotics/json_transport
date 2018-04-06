# json_transport

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
auto publisher = nh.advertise<json_transport::json_t>("json", 1);
publisher.publish(sent);

boost::shared_ptr<const json_transport::json_t> received = ros::topic::waitForMessage<json_transport::json_t>("json");

assert(*received == sent);
```

## Python

The provided `json_transport.PackedJson` message type allows publishing and subscribing anything that can be serialized/deserialized natively via the stdlib `json` module.

```
import json_transport
import rospy

rospy.init_node('json_talker')
pub = rospy.Publisher('json', json_transport.PackedJson, queue_size=1, latch=True)
pub.publish(1)
pub.publish([1, 2, 3])
pub.publish({'a': 1, 'b': 2, 'c': 3})

def callback(self, msg):
  assert msg.data == {'a': 1, 'b': 2, 'c': 3}

json_transport.Subscriber('json', json_transport.PackedJson, callback=callback)
```
