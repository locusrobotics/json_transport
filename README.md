# json_transport

Providing schemaless transport over ROS pub/sub via JSON. This is useful when schema is enforced elsewhere, or the data is truly schemaless (i.e. parameters, diagnostics).

## C++

The provided adapters allows publishing and subscribing [`nlohmann::json`](https://github.com/nlohmann/json) datatypes.

```
#include "json_transport/json_transport.hpp"

auto sent = R"(
  {
    "this_is_json": true,
    "pi": 3.141
  }
)"_json;

ros::NodeHandle nh;
auto publisher = nh.advertise<json_transport::json_t>("json", 1);
publisher.publish(sent);

boost::shared_ptr<const json_transport::json_t> received = ros::topic::waitForMessage<json_transport::json_t>("json");

assert(*received == sent);
```

## Python

The provided adapters allow publishing and subscribing anything that can be serialized/deserialized natively via the stdlib `json` module.

```
import json_transport
import rospy

rospy.init_node('json_talker')
pub = json_transport.Publisher('json', queue_size=1, latch=True)
pub.publish(1)
pub.publish([1, 2, 3])
pub.publish({'a': 1, 'b': 2, 'c': 3})
pub.publish(a=1, b=2, c=3)


def callback(self, data):
  assert data == {'a': 1, 'b': 2, 'c': 3}

json_transport.Subscriber('json', callback=callback)
```

## Notes

- `rospy` doesn't allow type masquerading, but there should be away to deserialize without an intermediary representation using [`rospy.AnyMsg`](http://docs.ros.org/api/rospy/html/rospy.msg.AnyMsg-class.html). Documentation is sparse.
