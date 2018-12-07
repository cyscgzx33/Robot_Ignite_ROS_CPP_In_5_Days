#include <ros/ros.h>
#include <ardrone_as/ArdroneAction.h>
#include <actionlib/client/simple_action_client.h>

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
    ROS_INFO("[State result]: %s", state.toString().c_str());
    ROS_INFO("The Action has been completed");
    ros::shutdown();
}

void activeCb() {
    ROS_INFO("Goal just went active");
}

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback) {
    ROS_INFO("[Feedback] image n.%d received", nImage);
    nImage++;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "no_wait_for_result");
    actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
    client.waitForServer();
    
    ardrone_as::ArdroneGoal goal;
    goal.nseconds = 19;
    
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    //client.waitForResult();
    
    ros::Rate loop_rate(2);
    actionlib::SimpleClientGoalState state_result = client.getState();
    ROS_INFO("[State Result]: %s", state_result.toString().c_str());
    
    
    // As comparison, it allows other tasks to perform in parallel
    // i.e., printing the log message while also printing the feedback from Action
    while (state_result == actionlib::SimpleClientGoalState::ACTIVE || state_result == actionlib::SimpleClientGoalState::PENDING) {
        ROS_INFO("Doing stuff while waiting for the Server to give a result ... ");
        loop_rate.sleep();
        state_result = client.getState();
        ROS_INFO("[State Result] : %s", state_result.toString().c_str());
        
    }
    
    return 0;
}