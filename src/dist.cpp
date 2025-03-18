#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "std_msgs/msg/float32.hpp"
#include <cmath>

class DistSubPub : public rclcpp::Node {
public:
    DistSubPub(): Node("dist_sub_pub")
    {
        subscriber = this->create_subscription<geometry_msgs::msg::Point>(
            "/points", 10, std::bind(&DistSubPub::callback, this, std::placeholders::_1));
        publisher = this->create_publisher<std_msgs::msg::Float32>("/distances", 10);
    }

private:
    void callback(const geometry_msgs::msg::Point::SharedPtr msg)
    {
        const float base_x = 0.0;
        const float base_y = 0.0;
        const float base_z = 0.0;
        float distance = sqrt(pow(msg->x - base_x, 2) + pow(msg->y - base_y, 2) + pow(msg->z - base_z, 2));
        auto message = std_msgs::msg::Float32();
        message.data = distance;
        publisher->publish(message);
        RCLCPP_INFO(this->get_logger(), "Distance from (0,0,0) to (%.2f, %.2f,%.2f): %.2f", msg->x, msg->y, msg->z, message.data);
    }
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscriber;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DistSubPub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}