import os
from ament_index_python.packages import get_package_share_directory #where does this package come from in Python? I mean I did not pip isntall or conda install anything
from launch import LaunchDescription #where does this package come from in Python? I mean I did not pip isntall or conda install anything
from launch.actions import DeclareLaunchArgument #https://docs.ros.org/en/rolling/p/launch/launch.actions.declare_launch_argument.html#launch.actions.declare_launch_argument.DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node #what the hell is the difference between launch and launch_ros?
from launch_ros.parameter_descriptions import ParameterValue

def generate_launch_description():
    # what does _install_ package "robot_arm_description" in /homeubuntu/dev_ws/install mean? how to do that? 
    pkg_description_dir = get_package_share_directory("robot_arm_description") #this returns just the path or return the whole directory object? what data type would it be? and what does "share" mean?
    # can I still call get_package_share_directory("robot_arm_description") from a different package/workspace? basically there are too many abstraction not explained anywhere
    # 2. Map the path straight to our newly verified .xacro file
    default_model_path = os.path.join(pkg_description_dir, "urdf", "robotarm.urdf.xacro")
    
    model_arg = DeclareLaunchArgument( #looking for command arguments from user
        name="model", 
        default_value=default_model_path,
        description="Absolute path to robot urdf file"
    )

    robot_description = ParameterValue( #what is the returned value of this?
        Command(["xacro ", LaunchConfiguration("model")]), #execute a command, and I have no idea what is LaunchConfiguration, please explain? 
        value_type=str
    )

    # 4. Define our standard industrial background worker nodes
    robot_state_publisher_node = Node( #the documentation page is even empty, how the hell do you and everyone know how to use this?
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}]
    )

    joint_state_publisher_gui_node = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui"
    )

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="screen"
    )

    # 5. Spits out the orchestration plan to the ROS 2 core engine
    return LaunchDescription([ # https://docs.ros.org/en/rolling/p/launch/launch.html#launch.LaunchDescription
        model_arg, #as long as everything here is of type LaunchDescriptionEntity, it can be put in the list
        joint_state_publisher_gui_node,
        robot_state_publisher_node,
        rviz_node
    ])

"""
take home message 9.June 2026:
- $PYTHONPATH will append /opt/ros/humble/local/lib/python3.10/dist-packages when we run source /opt/ros/humble/setup.bash
- colcon build does "installing", that means everythin in robot_arm_description/src will go into /home/ubuntu/dev_ws/install/robot_arm_description/




All these are convention for ros2 launch
ROS 2 actually officially supports three different file extensions for launching:

.launch.py (Python — Industry Standard for advanced logic and math)

.launch.xml (XML — Best for simple, clean, non-code configurations)

.launch.yaml (YAML — Lightweight, text-based alternative)


YOU RUN: `ros2 launch robot_arm_description display.launch.py`
                                     │
                                     ▼
 1. Look inside the environment variable path lookup index:
    `/home/ubuntu/dev_ws/install/robot_arm_description/share/robot_arm_description/`
                                     │
                                     ▼
 2. Does a `launch/` directory exist inside that share folder?
                                     │
                                     ▼
 3. Look for a file string matching exactly: `display.launch.py`
                                     │
                                     ▼
 4. Hand the file over to the Python Launch Service Engine to parse the nodes
"""