#include <ros/ros.h>
#include "services_quiz/BB8CustomServiceMessage.h"

int main(int argc, char** argv) {
    
    // initialize a ROS node
    ros::init(argc, argv, "MoveBB8Client"); 
    
    ros::NodeHandle nh;
    
    // create connection to the Service /move_bb8_in_square_custom
    ros::ServiceClient perform_square_service_client = nh.serviceClient<services_quiz::BB8CustomServiceMessage>("/move_bb8_in_square_custom");
    
    // create an object of type BB8CustomServiceMessage
    services_quiz::BB8CustomServiceMessage srv;
    
    srv.request.side = 3.0;
    srv.request.repetitions = 2;
    
    if (perform_square_service_client.call(srv)) {
        ROS_INFO("Service /move_bb8_in_square_custom successfully called. Moving BB8 in a square now.");
    } else {
        ROS_ERROR("Failed to call service /move_bb8_in_square_custom");
        return 1;
    }
    
    return 0;
}
