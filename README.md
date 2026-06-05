# Journey of learning to communicate with Computer Architecture

Practice here:
https://www.ewskills.com/
https://changkun.de/modern-cpp/en-us/07-thread/

To start docker 
```
docker run -it --rm \
  -v "$(pwd):/home/dev_ws/src" \
  -w /home/dev_ws \
  ros:humble-ros-base
```

source ROS:

```source /opt/ros/humble/setup.bash```

To create package:
```
ros2 pkg create --build-type ament_cmake tf2 --dependencies rclcpp std_msgs geometry_msgs sensor_msgs tf2_ros
```
To build code:

```
# Move to the workspace root
cd /home/dev_ws

# Build only your learning package
colcon build --packages-select changkun03

# Update your terminal's path to see the new build
source install/setup.bash

# Run the lesson!
ros2 run changkun03 execute_example
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

