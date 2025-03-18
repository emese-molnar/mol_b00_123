#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <cstdlib>

class PointGenerator : public rclcpp::Node {
public:
    PointGenerator(): Node("point_generator")
    {
        publisher = this->create_publisher<geometry_msgs::msg::Point>("/points", 10);
        timer = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&PointGenerator::timer_callback, this));
    }

private:
    void timer_callback()
        {
            auto message = geometry_msgs::msg::Point();
            message.x = (rand() % 100) / 10.0;
            message.y = (rand() % 100) / 10.0;
            message.z = (rand() % 100) / 10.0;
            RCLCPP_INFO(this->get_logger(), "Publishing: x=%f, y=%f, z=%f", message.x, message.y, message.z);
            publisher->publish(message);
        }
        
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PointGenerator>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
