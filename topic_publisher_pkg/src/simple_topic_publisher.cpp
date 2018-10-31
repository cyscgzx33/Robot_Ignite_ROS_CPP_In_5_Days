#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char** argv) {
    // Initialize a node named 'topic_publisher'
    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh;
    
    // Create a Publisher object, that publishs on 
    // the '/counter' topic message of type Int32
    ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000); 
    
    // set a publishing rate of 2 Hz
    ros::Rate loop_rate(2);
    
    // create a variable of type Int32
    std_msgs::Int32 count;
    // initialize 'count' variable
    count.data = 0;
    
    // create a loop that will go until someone stops the program execution
    while (ros::ok()) {
        // publish the message within the 'count' message
        pub.publish(count);
        ros::spinOnce();
        
        // make sure the publish rate maintains at 2 Hz
        loop_rate.sleep();
        
        ++count.data;
    }
    
    return 0;
    
}