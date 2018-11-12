#include <ros/ros.h>
// import the service message used by the service /gazebo/delete_model
#include <gazebo_msgs/DeleteModel.h>

int main(int argc, char** argv) {
    
    // initialize a ROS node with the name "service_client"
    ros::init(argc, argv, "service_client");
    ros::NodeHandle nh;
    
    // create the connection to the service /gazebo/delete_model
    ros::ServiceClient delete_model_service = nh.serviceClient<gazebo_msgs::DeleteModel>("/gazebo/delete_model");
    
    // create an object of type DeleteModel
    gazebo_msgs::DeleteModel srv;
    
    // fill the variable model_name of this object with the desired value
    srv.request.model_name = "bowl_1";
    
    
    // send through the connection the name of the object to be deleted by the service
    if (delete_model_service.call(srv)) {
        // print the result given by the service called
        ROS_INFO("%s", srv.response.status_message.c_str());
    } else {
        ROS_ERROR("Failed to call service delete_model");
        return 1;
    }
    
    return 0;
    
    
}