#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/static_transform_broadcaster.hpp>
#include <tf2_ros/transform_broadcaster.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

using namespace std::chrono_literals;

class WorkflowDemo : public rclcpp::Node {
    public:
    WorkflowDemo() : Node("workflowdemo_node") {
        //but why bother using pointer? -> just for manual control
        tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this); // why pointer and why did you design this to be a shared pointer? -> idk but the API seems to use some components internally relying on shared lifecycle ownership  https://docs.ros.org/en/humble/p/tf2_ros/generated/classtf2__ros_1_1StaticTransformBroadcaster.html
        tf_dynamic_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this); // why pointer and why did you design this to be a unique pointer? -> unique is always preffered. https://docs.ros.org/en/humble/p/tf2_ros/generated/classtf2__ros_1_1TransformBroadcaster.html

        joint_state_pub_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10); // why not design this to be any pointer like above? -> just construct it this way because Node has this method. https://docs.ros.org/en/kilted/p/rclcpp/generated/classrclcpp_1_1Node.html#_CPPv4I000EN6rclcpp4Node17create_wall_timerEN6rclcpp9WallTimerI9CallbackTE9SharedPtrENSt6chrono8durationI12DurationRepT9DurationTEE9CallbackTN6rclcpp13CallbackGroup9SharedPtrEb

        publish_static_environment();

        timer_ = this->create_wall_timer(10ms, std::bind(&WorkflowDemo::robot_motor_loop, this)); // why not design this to be any pointer like above? -> just construct it this way. https://docs.ros.org/en/kilted/p/rclcpp/generated/classrclcpp_1_1Node.html#_CPPv4I000EN6rclcpp4Node17create_wall_timerEN6rclcpp9WallTimerI9CallbackTE9SharedPtrENSt6chrono8durationI12DurationRepT9DurationTEE9CallbackTN6rclcpp13CallbackGroup9SharedPtrEb

        RCLCPP_INFO(this->get_logger(), "Complete Robot Simulation Node Active.");
    }

    private:
    void publish_static_environment() {
        geometry_msgs::msg::TransformStamped static_tf;
        static_tf.header.stamp = this->get_clock()->now();
        static_tf.header.frame_id = "world";
        static_tf.child_frame_id = "robot_base";

        static_tf.transform.translation.x = 1.5;
        static_tf.transform.translation.y = 0.0;
        static_tf.transform.translation.z = 0.0;
        static_tf.transform.rotation.w = 1.0;

        tf_static_broadcaster_->sendTransform(static_tf);
        RCLCPP_INFO(this->get_logger(), "Published fixed environment map to /tf_static"); //does StaticTransformBroadcaster auto publish on /tf_static? i haven read that in documentation
    }

    void robot_motor_loop() {
        joint_angle_ += 0.02;
        if (joint_angle_ > 2 * M_PI) joint_angle_ = 0.0;

        sensor_msgs::msg::JointState joint_msg;
        joint_msg.header.stamp = this->get_clock()->now();
        joint_msg.name.push_back("shoulder_joint"); //btw why push_back instead of = ? because we are pushing to a vector
        joint_msg.position.push_back(joint_angle_);
        joint_state_pub_->publish(joint_msg);


        //simulating the received ff from robot_state_publisher
        geometry_msgs::msg::TransformStamped dynamic_tf;
        dynamic_tf.header.stamp = this->get_clock()->now();
        dynamic_tf.header.frame_id = "robot_base";
        dynamic_tf.child_frame_id = "arm_link_1";

        dynamic_tf.transform.translation.x = 0.5 * std::cos(joint_angle_);
        dynamic_tf.transform.translation.y = 0.5 * std::sin(joint_angle_);
        dynamic_tf.transform.translation.z = 0.2; // Fixed height of the arm segment
        dynamic_tf.transform.rotation.w = 1.0;

        tf_dynamic_broadcaster_->sendTransform(dynamic_tf);
    }

    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_dynamic_broadcaster_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_; //what the hell is this syntax, is it a shared pointer or not? why dows it not look like above?
    // std::shared_ptr<rclcpp::Publisher<sensor_msgs::msg::JointState>> joint_state_pub_; this is actually also correct, but the above is just a more concise way to write it, because we are using the convention that all publisher in ROS2 is shared pointer, so we can just directly use the SharedPtr alias provided by rclcpp::Publisher class. https://docs.ros.org/en/kilted/p/rclcpp/generated/classrclcpp_1_1Publisher.html#_CPPv4I000EN6rclcpp9PublisherIN12sensor_msgs3msg10JointStateEE9SharedPtr
    rclcpp::TimerBase::SharedPtr timer_;
    double joint_angle_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WorkflowDemo>());
    rclcpp::shutdown();
    return 0;
}


/*take home message 04.June 2026
YOUR NODE
         ┌────────────────────────┐
         │ Part B:                │
         │ Publishes raw angle to │
         │ `/joint_states`        │
         └───────────┬────────────┘
                     │
                     ▼ `/joint_states` topic highway
   ══════════════════════════════════════════════════════════
                     │
                     ▼ (ROS catches this data automatically)
         ┌────────────────────────┐
         │ robot_state_publisher  │ ◄── Reads `.urdf` (Robot dimensions)
         └───────────┬────────────┘
                     │
                     ▼ Computes Forward Kinematics behind the scenes
   ══════════════════════════════════════════════════════════
                     │
                     ▼ `/tf` topic highway
         [ Finished 3D Coordinate Tree Frames ]
*/