#include <ardrone_as/ArdroneAction.h>
#include <actionlib/client/simple_action_client.h>

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
    ROS_INFO("The action has been completed");
    ros::shutdown();
}

void activeCb() {
    ROS_INFO("Goal just went active");
}

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback)
{
    ROS_INFO("[Feedback] image n.%d received", nImage);
    nImage++;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "wait_for_result");
    actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
    client.waitForServer();
    
    ardrone_as::ArdroneGoal goal;
    goal.nseconds = 19;
    
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    //client.waitForResult();
    
    ros::Rate loop_rate(2);
    
    // In this example, if the Action has not finished, it will never be activated
    while(!client.waitForResult()) {
        ROS_INFO("Doing stuff while waiting for server to give a result ...");
        loop_rate.sleep();
    }
    
    return 0;
}