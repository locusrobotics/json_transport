# Software License Agreement (BSD)
#
# \file      transport_py_talker.launch.py
# \authors   Paul Bovbel <pbovbel@locusrobotics.com>
# \copyright Copyright (c) (2018,), Locus Robotics, All rights reserved.

import launch
import launch_ros.actions
import launch_testing
import launch_testing.actions
import launch_testing.asserts


TEST_DATA = '{"test": 12.1, "other_test:": "fsa", "this is a list": [12, 42, "asdf"]}'


def generate_test_description():
    talker = launch_ros.actions.Node(
        package='json_transport',
        executable='talker_py',
        name='talker',
        parameters=[{'test_data': TEST_DATA}],
        output='screen',
    )

    listener_cpp = launch_ros.actions.Node(
        package='json_transport',
        executable='test_listener_cpp',
        name='test_listener_cpp',
        parameters=[{'test_data': TEST_DATA}],
        output='screen',
    )

    listener_py = launch_ros.actions.Node(
        package='json_transport',
        executable='test_listener_py',
        name='test_listener_py',
        parameters=[{'test_data': TEST_DATA}],
        output='screen',
    )

    shutdown = launch.actions.TimerAction(
        period=8.0,
        actions=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
    )

    return (
        launch.LaunchDescription([
            talker,
            listener_cpp,
            listener_py,
            shutdown,
            launch_testing.actions.ReadyToTest(),
        ]),
        {
            'listener_cpp': listener_cpp,
            'listener_py': listener_py,
        },
    )


@launch_testing.post_shutdown_test()
class TestTransportAfterShutdown:

    def test_exit_codes(self, proc_info, listener_cpp, listener_py):
        launch_testing.asserts.assertExitCodes(proc_info, process=listener_cpp)
        launch_testing.asserts.assertExitCodes(proc_info, process=listener_py)
