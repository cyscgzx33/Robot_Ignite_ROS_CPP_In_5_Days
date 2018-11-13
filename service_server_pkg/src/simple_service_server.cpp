#include <ros/ros.h>
// include the service message header from the Empty.srv message
#include <std_srvs/Empty.h>

// We define the callback function of the service
bool my_callback(std_srvs::Empty::Request &req,
                 std_srvs::Empty::Response &res) 
{
    // res.some_variable = req.some_variable + req.another_variable;
    ROS_INFO("my_callback has been called");
    return true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "service_server");
    ros::NodeHandle nh;
    
    ros::ServiceServer my_service = nh.advertiseService("/my_service", my_callback);
    // maintain the service once
    ros::spin(); 
    
    return 0;
}