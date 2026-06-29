from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
import os
import xacro

def generate_launch_description():

    pkg = get_package_share_directory("my_robot_arm")
    xacro_file = os.path.join(pkg, "urdf", "robot.xacro")
    robot_urdf = xacro.process_file(xacro_file).toxml()

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[{"robot_description": robot_urdf} ]
    )

    joint_state_publisher_gui_node = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
        output="screen"
    )

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        output="screen",
        name="rviz2"
    )
    

    return LaunchDescription(
        [robot_state_publisher_node, joint_state_publisher_gui_node, rviz_node]
    )