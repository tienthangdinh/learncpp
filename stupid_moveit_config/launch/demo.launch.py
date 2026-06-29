from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch

def generate_launch_description():
    # Force the builder to use your native XACRO and bypass the hardware drivers
    moveit_config = (
        MoveItConfigsBuilder("my_robot_arm", package_name="stupid_moveit_config")
        .robot_description(file_path="src/my_robot_arm/urdf/robot.xacro")
        .trajectory_execution(moveit_manage_controllers=True)
        .to_moveit_configs()
    )
    return generate_demo_launch(moveit_config)