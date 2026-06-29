# Journey of learning to communicate with Computer Architecture

Practice here:
https://www.ewskills.com/
https://changkun.de/modern-cpp/en-us/07-thread/

To start minimal docker 
```
docker run -it --rm \
  -v "$(pwd):/home/dev_ws/src" \
  -w /home/dev_ws \
  ros:humble-ros-base
```
To start VNC docker
```
docker run -it --rm \
  -p 6080:80 \
  -v "$(pwd):/home/ubuntu/dev_ws/src" \
  -w /home/ubuntu/dev_ws \
  --name ros2_desktop_container \
  --security-opt seccomp=unconfined \
  tiryoh/ros2-desktop-vnc:humble
```

To get into another terminal of the same docker container:
```
docker exec -it 099a4b8a510a /bin/bash 
```


source ROS:

```
sudo apt update && sudo apt install -y ros-humble-xacro
sudo apt install -y ros-humble-joint-state-publisher-gui
sudo apt install -y wget lsb-release gnupg
sudo wget https://packages.osrfoundation.org/gazebo.gpg -O /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null
sudo apt update #very important!!!
sudo apt install -y ros-humble-ros-gz-sim ros-humble-ros-gz-bridge
sudo apt install -y ros-humble-moveit
sudo apt install -y ros-humble-ros2-control ros-humble-ros2-controllers
source /opt/ros/humble/setup.bash
```

To create package:
```
ros2 pkg create --build-type ament_cmake tf2 --dependencies rclcpp std_msgs geometry_msgs sensor_msgs tf2_ros
```
To build code:

```
# Move to the workspace root
cd /home/dev_ws
colcon build --packages-select stupid_moveit_config
source install/setup.bash
ros2 launch stupid_moveit_config demo.launch.py
```

## Plan for blog
- Blog will be from perspective of Robotic Engineer & Embeded Engineer with all related examples
- how to read C++ docs:
  - structure of packages
  - how to read member type, member function, non-member function, iterator 
  invalidation (e.g. std::vector)
  - structore of ROS packages too
- language usability concept:
  - types of constants (e.g. when to pass and make it const inside a function scope?)
  - types of variables (e.g. uint8_t is massively more data-efficient than int - 75%)
  - how to get types of a variable
  - control flow related to constexpr
  - templates hell: folding, variadic,...
  - OOP: different ways to construct/initialize
- values:
  - passing arguments
  - playing around with lvalues, rvalues, xvalues,...
  - move semantics & perfect forwarding 
- containers in C++ (ultimately important)
  - different types of list, array (linear)
  - different types of set, map
  - tuples
  - i need more contents here (going into robotics)
- memory management:
  - process virtual memory
  - let's work alot with pointer & *
  - RAII and reference counting
  - and a lot more of that

