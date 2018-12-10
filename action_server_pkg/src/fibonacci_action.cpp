#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/FibonacciAction.h>
#include <action_server_pkg/fibonacci_action.h>

FibonacciAction::FibonacciAction(std::string name):
    // please pay attention to "_1", it is a special place holder of the bind() function
    // this is a boost shared pointer, given by appending "ConstPtr" to the end of the goal message type
    as_(nh_, name, boost::bind(&FibonacciAction::executeCB, this, _1), false),
    action_name_(name)
{
    as_.start();
}

FibonacciAction::~FibonacciAction() {}

void FibonacciAction::executeCB(const actionlib_tutorials::FibonacciGoalConstPtr& goal)
{
    // helper variables
    ros::Rate rt_(1);
    bool success = true;
    
    // push_back the seeds for the fibonacci sequence
    feedback_.sequence.clear();
    feedback_.sequence.push_back(0);
    feedback_.sequence.push_back(1);
    
    // publish info to the console for the user
    ROS_INFO("%s: Executing, creating fibonacci sequence of oder %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);
    
    // start executing the action
    // an important component of an action server is the ability to allow an action client to request,
    // that the current goal execution be cancelled
    // i.e., when a client requests that the current goal to be preempted, 
    // the action server should cancel the goal, perform necessary clean-up and call the function setPreempted(),
    // which indicates that the action has been preempted by user's request
    for (int i = 1; i <= goal->order; i++) {
        
        // check the preempt has not been requested by the client
        if (as_.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s: Preempted", action_name_.c_str());
            
            // set the action state to preempted
            as_.setPreempted();
            success = false;
            break;
        }
        
        feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
        
        
        // here the Fibonacci sequence is put into the feedback variable and then published on the feedback channel provided by action server
        // then the action continues on looping and publishing feedback
        // publish the feedback
        as_.publishFeedback(feedback_);
        
        // setting the rate at which the action server checks for preemption requests is left to the implementor of the server
        // the sleep is not necessary, the sequence is computed at 1 Hz for demonstration purpose
        rt_.sleep();
        
    }
    
    
    // once the action has finished computing the Fibonacci sequence the action notifies the action client,
    // that the action completed by setting succeeded
    if (success) {
        result_.sequence = feedback_.sequence;
        ROS_INFO("%s: Succeeded", action_name_.c_str());
        
        // set the action state to succeeded
        as_.setSucceeded();
    }
}