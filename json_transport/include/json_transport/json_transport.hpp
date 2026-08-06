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

#ifndef JSON_TRANSPORT_JSON_TRANSPORT_HPP
#define JSON_TRANSPORT_JSON_TRANSPORT_HPP

#include "json_msgs/msg/json.hpp"

#include <nlohmann/json.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/type_adapter.hpp>

namespace json_transport
{
  typedef nlohmann::json json_t;
  typedef json_msgs::msg::Json json_msg_t;

  inline json_t unpack(json_msg_t message)
  {
    return json_t::parse(message.json.empty() ? "null" : message.json);
  }

  inline json_msg_t pack(json_t data)
  {
    json_msg_t message{};
    message.json = data.dump();
    return message;
  }
}

namespace rclcpp
{
template<>
struct TypeAdapter<json_transport::json_t, json_transport::json_msg_t>
{
  using is_specialized = std::true_type;
  using custom_type = json_transport::json_t;
  using ros_message_type = json_transport::json_msg_t;

  static void convert_to_ros_message(const custom_type& source, ros_message_type& destination)
  {
    destination = json_transport::pack(source);
  }

  static void convert_to_custom(const ros_message_type& source, custom_type& destination)
  {
    destination = json_transport::unpack(source);
  }
};
} // namespace rclcpp

RCLCPP_USING_CUSTOM_TYPE_AS_ROS_MESSAGE_TYPE(json_transport::json_t, json_transport::json_msg_t)

#endif  // JSON_TRANSPORT_JSON_TRANSPORT_HPP
