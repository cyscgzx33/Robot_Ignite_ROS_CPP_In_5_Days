#include <ros/ros.h>
#include <ardrone_as/ArdroneAction.h> // note: "Action" is appended
#include <actionlib/client/simple_action_client.h>


/* For Reference */

// int PENDING = 0;
// int ACTIVE = 1;
// int DONE = 2;
// int WARN = 3;
// int ERROR = 4;

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
    ROS_INFO("[State Result] : %s", state.toString().c_str());
    ROS_INFO("The Action has been completed");
    ros::shutdown();
}

// Call this function when the goal becomes active
void activeCb() {
    ROS_INFO("Goal just went ative");
}

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback) {
    ROS_INFO("[Feedback] image n.%d received", nImage);
    ++nImage;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "cancel_goal");
    actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server");
    client.waitForServer();
    
    ardrone_as::ArdroneGoal goal;
    goal.nseconds = 10;
    
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    //client.waitForResult();
    
    ros::Rate loop_rate(2);
    
    actionlib::SimpleClientGoalState state_result = client.getState();
    ROS_INFO("[State Result] : %s", state_result.toString().c_str());
    
    
    int counter = 0;
    
    while (state_result == actionlib::SimpleClientGoalState::ACTIVE || state_result == actionlib::SimpleClientGoalState::PENDING)
    {
        ROS_INFO("Conducting some stuff while waiting for the Server to give a result ...");
        loop_rate.sleep();
        state_result = client.getState();
        ROS_INFO("[State Result]: %s", state_result.toString().c_str());
        counter++;
        
        if (counter == 2) {
            ROS_INFO("Cancelling the goal ......");
            client.cancelGoal();
            ROS_INFO("Cancelled the goal.");
            state_result = client.getState();
            ROS_INFO("[State Result] : %s", state_result.toString().c_str());
            ROS_INFO("counter = %d", counter);
        }
    }
    
    return 0;


}
