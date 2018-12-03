#include <ros/ros.h>

// Note: one must include this file to call action server
// Convention:
// if your message file was called Arfrone.action
// then the type of action message is ArdroneAction
#include <ardrone_as/ArdroneAction.h>
#include <actionlib/client/simple_action_client.h>

/* do all the initialization and function definition here */

// initialization of a global variable
int nImage = 0;

// done callback function, which is called once the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
             const ardrone_as::ArdroneResultConstPtr& result) 
{
    ROS_INFO("The action has been completed");
    ros::shutdown();
}

// active callback funtion, which is called when the goal becomes active
void activeCb() {
    ROS_INFO("The goal becomes active");
}

// feedback callback function, which is called when the feedback is received
// from the action server, and it just prints a message indicating a new
// message has been received
void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback) {
    ROS_INFO("[Feedback] image n.%d received", nImage);
    nImage++;
}



int main(int argc, char** argv) {
    
    // initialize a node?
    ros::init(argc, argv, "drone_action_client");
    
    // create connection to the action server
    actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
    
    // wait until the action server is ON and running
    client.waitForServer();

    // create a goal object to send to the action server
    // Convention:
    // If your action message file was called Ardrone.action
    // then the type of goal message is ArdroneGoal
    ardrone_as::ArdroneGoal goal;
    
    // assign it that it will take pictures along 12 seconds
    // It turns out at the screen it will only counts to (n-2) seconds
    goal.nseconds = 19;
    
    // send the goal to the action server, specified which functions to call: 0), when the goal completes
    // 1) when the goal becomes active, and when the feedback is received
    // Convention:
    // it contains 4 items:
    // 1. the goal parameters
    // 2. a done function to be called when the action finishes
    // 3. an active function to be called when the action starts
    // 4. a feedback function to be called from time to time to know the status of the action
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    
    
    // finally, wait for the result
    client.waitForResult();
    
    return 0;
}