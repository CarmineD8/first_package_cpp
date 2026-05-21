/**
 * @file talker.cpp
 * @brief Example ROS 2 publisher node using rclcpp.
 *
 * @details
 * This file implements a simple ROS 2 node called `MinimalPublisher`.
 * The node periodically publishes text messages on a ROS 2 topic
 * using the standard string message type.
 *
 * The purpose of this example is to demonstrate:
 * - ROS 2 node creation
 * - Publisher initialization
 * - Periodic execution with timers
 * - Message publishing with logging
 *
 * ## Publishers
 * | Topic Name | Message Type              | Description                     |
 * |------------|---------------------------|---------------------------------|
 * | `/topic`   | std_msgs::msg::String     | Publishes "Hello, world!" text messages with an incrementing counter |
 *
 * ## Subscribers
 * This node does not subscribe to any topics.
 *
 * ## Timer
 * A wall timer triggers message publication every 500 ms.
 */

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <chrono>
#include <iostream>
#include <string>

/**
 * @class MinimalPublisher
 * @brief A simple ROS 2 publisher node.
 *
 * This node publishes a std_msgs::msg::String message
 * periodically on the "topic" topic every 500 milliseconds.
 */
class MinimalPublisher : public rclcpp::Node
{
public:
    /**
     * @brief Construct a new Minimal Publisher object.
     *
     * Initializes the ROS 2 node, creates the publisher,
     * configures the timer callback, and initializes the counter.
     */
    MinimalPublisher()
        : Node("minimal_publisher"), count_(0)
    {
        publisher_ =
            this->create_publisher<std_msgs::msg::String>("topic", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&MinimalPublisher::timer_callback, this));
    }

private:
    /**
     * @brief Timer callback function.
     *
     * Creates and publishes a string message containing
     * an incrementing counter value.
     */
    void timer_callback()
    {
        auto message = std_msgs::msg::String();

        message.data = "Hello, world! " + std::to_string(count_++);

        RCLCPP_INFO(
            this->get_logger(),
            "Publishing: '%s'",
            message.data.c_str());

        publisher_->publish(message);
    }

    /**
     * @brief ROS 2 publisher for string messages.
     */
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    /**
     * @brief Timer used to periodically trigger publishing.
     */
    rclcpp::TimerBase::SharedPtr timer_;


    size_t count_;  /**< @brief Counter used to differentiate published messages*/
};

/**
 * @brief Main entry point for the ROS 2 publisher node.
 *
 * Initializes ROS 2, creates the publisher node,
 * spins the node to process callbacks, and shuts down ROS 2.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status code.
 */
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<MinimalPublisher>());

    rclcpp::shutdown();

    return 0;
}