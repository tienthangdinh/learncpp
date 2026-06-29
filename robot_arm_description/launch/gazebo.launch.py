import os
from pathlib import Path
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription  # Fixed typo
from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable, IncludeLaunchDescription
from launch.substitutions import Command, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue

def generate_launch_description():
    pkg_description_dir = get_package_share_directory("robot_arm_description")

    # 1. Declare the argument slot
    model_args = DeclareLaunchArgument(
        name="model", 
        default_value=os.path.join(pkg_description_dir, "urdf", "robotarm.urdf.xacro"), 
        description="Absolute path to robot URDF file"
    )
    
    # 2. Tell Gazebo where your meshes are hiding
    gazebo_resource_path = SetEnvironmentVariable(
        name="GZ_SIM_RESOURCE_PATH", 
        value=[str(Path(pkg_description_dir).parent.resolve())]
    )
    
    # 3. Use the safe, lazy evaluation Command pointer to parse Xacro at boot time
    robot_description = ParameterValue(
        Command(["xacro ", LaunchConfiguration("model")]), 
        value_type=str
    )

    # 4. State Publisher Node
    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[{"robot_description": robot_description, "use_sim_time": True}] # Crucial for synchronization!
    )

    # 5. Include Gazebo World Simulator Engine
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory("ros_gz_sim"), "launch", "gz_sim.launch.py")
        ]),
        launch_arguments=[("gz_args", " -v 4 -r empty.sdf ")]
    )
    
    # 6. Spawner Node - Takes URDF data from ROS topic and drops it into Gazebo physics
    gz_spawn_entity = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=["-topic", "robot_description", "-name", "robot_arm"], # Renamed cleanly
    )

    # 7. Bridge Node - Passes simulation clock cycles back to ROS 2
    gz_ros2_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        arguments=["/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock"]
    )

    # 8. Return EVERYTHING to the Launch Service Engine (Including arguments and environment configs!)
    return LaunchDescription([
        model_args,
        gazebo_resource_path,
        robot_state_publisher_node,
        gazebo,
        gz_spawn_entity,
        gz_ros2_bridge
    ])