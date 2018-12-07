#include <ros/ros.h>
#include <ardrone_as/ArdroneAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
    ROS_INFO("[State Result]: %s", state.toString().c_str());
    ROS_INFO("The Action has been completed");
    //ros::shutdown();
}

void activeCb() {
    ROS_INFO("Goal just went active");
}

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback) {
    ROS_INFO("[feedback] image n.%d received", nImage);
    ++nImage;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "drone_action_client");
    ros::NodeHandle nh;
    
    actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
    client.waitForServer();
    
    ros::Publisher move = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    geometry_msgs::Twist move_msg;
    
    ros::Publisher takeoff = nh.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
    std_msgs::Empty takeoff_msg;
    
    ros::Publisher land = nh.advertise<std_msgs::Empty>("/drone/land", 1000);
    std_msgs::Empty land_msg;
    
    ardrone_as::ArdroneGoal goal;
    goal.nseconds = 19;
    
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    //client.waitForResult();
    
    ros::Rate loop_rate(1);
    actionlib::SimpleClientGoalState state_result = client.getState();
    
    ROS_INFO("[State Result]: %s", state_result.toString().c_str());
    
    int i = 0;
    while (i < 4) {
        takeoff.publish(takeoff_msg);
        ROS_INFO("Taking Off Drone");
        loop_rate.sleep();
        i++;
    }
    
    while (state_result == actionlib::SimpleClientGoalState::ACTIVE || state_result == actionlib::SimpleClientGoalState::PENDING) {
        ROS_INFO("Moving drone around while waiting for the Server to give a result");
        move_msg.linear.x = 1;
        move_msg.angular.z = 1;
        move.publish(move_msg);
        loop_rate.sleep();
        state_result = client.getState();
        ROS_INFO("[State Result]: %s", state_result.toString().c_str());
    }
    
    i = 0;
    while (i < 4) {
        move_msg.linear.x = 0;
        move_msg.angular.z = 0;
        move.publish(move_msg);
        land.publish(land_msg);
        ROS_INFO("Landing Drone");
        
        loop_rate.sleep();
        i++;
    }
    
    return 0;
}