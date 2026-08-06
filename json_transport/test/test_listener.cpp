/**
Software License Agreement (BSD)

\file      test_listener.cpp
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
#include "json_transport/json_transport.hpp"

#include <chrono>
#include <mutex>
#include <optional>
#include <thread>

#include <rclcpp/rclcpp.hpp>

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("json_listener_cpp");
  node->declare_parameter<std::string>("test_data", "null");
  const auto expected = json_transport::json_t::parse(node->get_parameter("test_data").as_string());

  std::mutex mutex;
  std::optional<json_transport::json_t> received;

  auto subscription = node->create_subscription<json_transport::json_t>(
    "json",
    rclcpp::QoS(10).transient_local().reliable(),
    [&](const json_transport::json_t & message) {
      {
        std::lock_guard<std::mutex> lock(mutex);
        received = message;
      }
      RCLCPP_INFO_STREAM(node->get_logger(), "Received " << message);
    });

  (void)subscription;

  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(node);

  auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (rclcpp::ok()) {
    {
      std::unique_lock<std::mutex> lock(mutex);
      if (received.has_value()) {
        break;
      }
    }

    executor.spin_some();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    if (std::chrono::steady_clock::now() > deadline) {
      RCLCPP_ERROR(node->get_logger(), "Timed out waiting for message on 'json'");
      rclcpp::shutdown();
      return 1;
    }
  }

  int exit_code = 0;
  {
    std::lock_guard<std::mutex> lock(mutex);
    if (!received.has_value() || received.value() != expected) {
      RCLCPP_ERROR_STREAM(node->get_logger(), "Received payload does not match expected payload");
      exit_code = 1;
    }
  }

  rclcpp::shutdown();
  return exit_code;
}
