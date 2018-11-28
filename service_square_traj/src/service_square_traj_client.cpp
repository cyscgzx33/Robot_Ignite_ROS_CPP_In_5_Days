#include <ros/ros.h>
#include <std_srvs/Empty.h>

int main(int argc, char** argv) 
{
    // initialize a ROS node of service client
    ros::init(argc, argv, "service_square_traj_client");
    
    ros::NodeHandle nh;
    
    // create connection to the service /perform_square
    ros::ServiceClient perform_square_service_client = nh.serviceClient<std_srvs::Empty>("/perform_square");
    
    // create an object of type Empty
    std_srvs::Empty srv;
    
    if (perform_square_service_client.call(srv)) {
        ROS_INFO("Service successfully called. Moving BB8 in a square");
    } 
    else {
        ROS_ERROR("Failed to call service /perform_square");
        return 1;
    }
    
    return 0;
    
}