# Journey of learning to communicate to Operating System

To start docker 
```
docker run -it --rm \
  -v "$(pwd):/home/dev_ws/src" \
  -w /home/dev_ws \
  ros:humble-ros-base
```

source ROS:

```source /opt/ros/humble/setup.bash```

To build code:

```
# Move to the workspace root
cd /home/dev_ws

# Build only your learning package
colcon build --packages-select changkun03

# Update your terminal's path to see the new build
source install/setup.bash

# Run the lesson!
ros2 run changkun03 lesson01_exe
```