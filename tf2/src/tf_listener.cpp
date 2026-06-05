#include <chrono>
#include <functional>
#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp> //how do we know how to include? what is the general guide? like I saw the documentation and it doesnt say anything
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h> //how do we know how to include?
#include <geometry_msgs/msg/transform_stamped.hpp>

using namespace std::chrono_literals;

class TFListener : public rclcpp::Node {
    public:
    TFListener() : Node("TFListener") {
        //buffer stores coordinates frame over time,
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock()); //https://docs.ros.org/en/humble/p/tf2_ros/generated/classtf2__ros_1_1Buffer.html
        //listener listen to the buffer?
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_); //https://docs.ros.org/en/humble/p/tf2_ros/generated/classtf2__ros_1_1TransformListener.html

        timer_ = this->create_wall_timer(1s, std::bind(&TFListener::on_timer, this)); //https://docs.ros.org/en/kilted/p/rclcpp/generated/classrclcpp_1_1Node.html#_CPPv4I000EN6rclcpp4Node17create_wall_timerEN6rclcpp9WallTimerI9CallbackTE9SharedPtrENSt6chrono8durationI12DurationRepT9DurationTEE9CallbackTN6rclcpp13CallbackGroup9SharedPtrEb

        RCLCPP_INFO(this->get_logger(), "TF2 Listener Node has been started.");
    }

    private:
    void on_timer() {
        std::string target_frame = "gripper_link";
        std::string source_frame = "workpiece";

        geometry_msgs::msg::TransformStamped transformStamped; //https://docs.ros2.org/foxy/api/geometry_msgs/msg/TransformStamped.html

        try {
            transformStamped = tf_buffer_->lookupTransform(target_frame, source_frame, tf2::TimePointZero); //https://docs.ros.org/en/humble/p/tf2_ros/generated/classtf2__ros_1_1Buffer.html

            double x = transformStamped.transform.translation.x;
            double y = transformStamped.transform.translation.y;
            double z = transformStamped.transform.translation.z;

            RCLCPP_INFO(this->get_logger(), "Success! Workpiece relative to Gripper: X: %.2f, Y: %.2f, Z: %.2f", x, y, z);
        } catch (const tf2::TransformException& ex) {
            RCLCPP_WARN(this->get_logger(), "Could not transform %s to %s: %s", target_frame.c_str(), source_frame.c_str(), ex.what());
        }
    }

    std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr}; //brace initialization, VERY IMPORTANT!!! create a pointer but not the object
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TFListener>());
  rclcpp::shutdown();
  return 0;
}