#include <ros/ros.h>

/* --------------------------------------------------------------------------
    some steps to decide which file should be included:
    step 0: roslaunch <pkg-name> <launch-file-name>
    step 1: rosservice list | grep execute_trajectory (ontain a service name)
    step 2: rosservice info /execute_trajectry (result of step 1)
    step 3: rossrv show <Type> (result of step 2, 'Type')
   -------------------------------------------------------------------------- */
#include <iri_wam_reproduce_trajectory/ExecTraj.h>

/* must include ros/package.h to call ros::package::getPath */
#include <ros/package.h>

int main (int argc, char** argv) {
    
    // initialize a ROS node with the name "execute_trajectory_node"
    ros::init(argc, argv, "execute_trajectory_node");
    ros::NodeHandle nh;
    
    // create a connection to the service /execute_trajectory
    ros::ServiceClient exec_traj_service = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");

    // create an object of type ExecTraj
    iri_wam_reproduce_trajectory::ExecTraj srv;
    
    // This ros::package::getPath works in same way as $(find name_of_package) in the launch files
    // One can just easily try "roscd iri_wam_reproduce_trajectory" and check
    srv.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") + "/config/get_food.txt";
    
    // using for debugging
    ROS_INFO("%s", "Before call service /execute_trajectory");
    
    
    // send through the connection of the name of the path above to be executed
    if (exec_traj_service.call(srv)) {
        ROS_INFO("%s", "Service successfully called. Executing trajectory.");
    } else {
        ROS_ERROR("Failed to call service /execute_trajectry");
        return 1;
    }
    
    
    return 0;
    
}