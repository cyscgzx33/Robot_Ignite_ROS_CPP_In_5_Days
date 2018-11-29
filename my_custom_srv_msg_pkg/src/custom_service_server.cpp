#include <ros/ros.h>
#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"

bool myCbFunction(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request  &req,
                  my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res) 
{
    ROS_INFO("Request Data: radius = %f, repetitions = %d", req.radius, res.repetitions);        
    if (req.radius > 5.0) {
        res.success = true;
        ROS_INFO("sending back response : true");
    } else {
        res.success = false;
        ROS_INFO("sending back response : false");
    }
    
    return true;
}

int main