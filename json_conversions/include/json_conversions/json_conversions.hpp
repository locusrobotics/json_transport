#include "nlohmann/json.hpp"
#include "json_msgs/Json.h"

#include <ros/message_traits.h>
#include <ros/serialization.h>

ROS_STATIC_ASSERT(sizeof(nlohmann::json) == 16);

namespace json_msgs
{

void to_json(nlohmann::json& json, const Json& msg) {
  json = nlohmann::json::from_ubjson(msg.data);
}

void from_json(const nlohmann::json& json, Json& msg) {
  msg.data = nlohmann::json::to_ubjson(json);
}

}

namespace ros
{
namespace message_traits
{
// template<> struct IsFixedSize<nlohmann::json> : public TrueType {};

template<>
struct MD5Sum<nlohmann::json>
{
  static const char* value()
  {
    // Ensure that if the definition of json_msgs::Json changes we have a compile error here.
    // ROS_STATIC_ASSERT(MD5Sum<json_msgs::Json>::static_value1 == 0x4a842b65f413084dULL);
    // ROS_STATIC_ASSERT(MD5Sum<json_msgs::Json>::static_value2 == 0xc2b10fb484ea7f17ULL);
    return MD5Sum<json_msgs::Json>::value();
  }

  static const char* value(const nlohmann::json& m)
  {
    return MD5Sum<json_msgs::Json>::value(m);
  }
};

template<>
struct DataType<nlohmann::json>
{
  static const char* value()
  {
    return DataType<json_msgs::Json>::value();
  }

  static const char* value(const nlohmann::json& m)
  {
    return DataType<json_msgs::Json>::value(m);
  }
};

template<>
struct Definition<nlohmann::json>
{
  static const char* value()
  {
    return Definition<json_msgs::Json>::value();
  }

  static const char* value(const nlohmann::json&)
  {
    return value();
  }
};
} // namespace message_traits

namespace serialization
{

template<>
struct Serializer<nlohmann::json>
{
  template<typename Stream>
  inline static void write(Stream& stream, const nlohmann::json& json)
  {
    stream.next(nlohmann::json::to_ubjson(json));
  }

  template<typename Stream>
  inline static void read(Stream& stream, nlohmann::json& json)
  {
    std::vector<std::uint8_t> data;
    stream.next(data);
    json = nlohmann::json::from_ubjson(data);
  }

  inline static uint32_t serializedLength(const nlohmann::json& json)
  {
    return nlohmann::json::to_ubjson(json).size();
  }
};

} // namespace serialization
} // namespace ros
