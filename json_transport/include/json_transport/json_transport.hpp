/**
Software License Agreement (BSD)

\file      json_transport.hpp
\authors   Paul Bovbel <pbovbel@locusrobotics.com>
\copyright Copyright (c) (2018,), Locus Robotics, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided with
the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#include "nlohmann/json.hpp"
#include "json_msgs/Json.h"

#include <ros/message_traits.h>
#include <ros/serialization.h>

ROS_STATIC_ASSERT(sizeof(nlohmann::json) == 16);

namespace ros
{
namespace message_traits
{

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

  static const char* value(const nlohmann::json&)
  {
    return value();
  }
};

template<>
struct DataType<nlohmann::json>
{
  static const char* value()
  {
    return DataType<json_msgs::Json>::value();
  }

  static const char* value(const nlohmann::json&)
  {
    return value();
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
    stream.next(json.dump());
  }

  template<typename Stream>
  inline static void read(Stream& stream, nlohmann::json& json)
  {
    std::string data;
    stream.next(data);
    json = nlohmann::json::parse(data);
  }

  inline static uint32_t serializedLength(const nlohmann::json& json)
  {
    return json.dump().size() + 4;
  }
};

} // namespace serialization
} // namespace ros
