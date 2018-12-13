#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actions_quiz/CustomActionMsgAction.h>

class CustomActionMsgAction
{
    protected:
        ros::NodeHandle nh_;
        
        actionlib::SimpleActionServer<actions_quiz::CustomActionMsgAction> as_;
        
        std::string action_name_;
        
        actions_quiz::CustomActionMsgFeedback feedback_;
        
        actions_quiz::CustomActionMsgResult result_;
        
    public:
        CustomActionMsgAction(std::string name);
        ~CustomActionMsgAction();
        
        void executeCB(const actions_quiz::CustomActionMsgGoalConstPtr& goal);
}