#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.hpp>
#include <tf2_ros/transform_listener.hpp>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

using namespace std::chrono_literals;

class TfPicker : public rclcpp::Node {
    public:
    TfPicker() : Node("TfPicker") {
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock()); //a storage of different transforms, maybe I want to find a way to see all transform from here using command line?
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_); //I know what is this for, just learned
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this); //I know what is this for
        timer_ = this->create_wall_timer(5s, std::bind(&TfPicker::on_timer, this));
    }

    private:
    void on_timer() {

        //==========PART 1: BROADCASTING======================
        geometry_msgs::msg::TransformStamped camera_to_object_tf;

        camera_to_object_tf.header.stamp = this->get_clock()->now();
        camera_to_object_tf.header.frame_id = "camera_frame";
        camera_to_object_tf.child_frame_id = "object_frame";

        //simulating that the camera has found the object using object detection algorithm
        camera_to_object_tf.transform.translation.x = 0.2;
        camera_to_object_tf.transform.translation.y = 0.5;
        camera_to_object_tf.transform.translation.z = -1.2;

        camera_to_object_tf.transform.rotation.x = 0.0;
        camera_to_object_tf.transform.rotation.y = 0.0;
        camera_to_object_tf.transform.rotation.z = 0.0;
        camera_to_object_tf.transform.rotation.w = 1.0;

        //broadcast to the whole network, but on what topic is it broadcasting? where can I see it? -> convention is /tf
        tf_broadcaster_->sendTransform(camera_to_object_tf);

        //=======PART 2: LISTENING ==================================
        geometry_msgs::msg::TransformStamped base_to_object_tf;
        try {
            base_to_object_tf = tf_buffer_->lookupTransform("robot_base", "object_frame", tf2::TimePointZero); //latest timestamp, different from this->now() means having to wait

            double target_x = base_to_object_tf.transform.translation.x;
            double target_y = base_to_object_tf.transform.translation.y;
            double target_z = base_to_object_tf.transform.translation.z;

            RCLCPP_INFO(this->get_logger(), 
                    "Path Planner Command -> Move Gripper to Robot Base Coordinates: [X: %.2f, Y: %.2f, Z: %.2f]", 
                    target_x, target_y, target_z);
        } catch (const tf2::TransformException & ex) {
            //actually this warning will running until environment bootsup finished
            RCLCPP_WARN(this->get_logger(), "Waiting for environment layout setup... %s", ex.what());
        }
    }
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TfPicker>());
    rclcpp::shutdown();
    return 0;
}

/* take home message 03.June 2026
- ros2 topic echo /tf
- ros2 run tf2_tools view_frames

[ CAMERA NODE ]                        [ ROBOT DRIVER NODE ]
 (Custom Broadcaster)                      (Built-in Broadcaster)
          │                                          │
          │ publishes to                             │ publishes to
          ▼                                          ▼
  ───────────────────────────────────────────────────────────────────
                        THE ROS 2 NETWORK HIGHWAY
     Topic: `/tf` or `/tf_static`  ===============================►
  ───────────────────────────────────────────────────────────────────
                                  │
                                  │ background clerk fetches data
                                  ▼
                        [ PATH PLANNER NODE ]
                     ┌─────────────────────────┐
                     │ tf2_ros::Listener       │ (Background Worker)
                     └────────────┬────────────┘
                                  │ dumps data into
                                  ▼
                     ┌─────────────────────────┐
                     │ tf2_ros::Buffer         │ (Internal Notebook)
                     └─────────────────────────┘
                                  ▲
                                  │ user queries via lookupTransform()
                                  │
                         [ Your Custom Code ]
*/