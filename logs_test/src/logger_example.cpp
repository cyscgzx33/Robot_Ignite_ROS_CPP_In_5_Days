#include <ros/ros.h>
#include <ros/console.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    
    /* -----------------------------------------------------------------------------------------------
        Note 0: To change the logger levels from C++, use ros::console::set_logger_level()
        Note 1: If one changed one of the logger's verbosity levels after any logging statements
                using that logger, you MUST call "console::notifyLoggerLevelChanged()". If you don't,
                logging statements that have already been hit once (and therefore initialized) may
                continue to print when they should not, and vice-versa
       ----------------------------------------------------------------------------------------------- */ 
    if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug))
    {
        ros::console::notifyLoggerLevelsChanged();
    }
    
    ros::init(argc, argv, "log_demo");
    
    ros::NodeHandle nh;
    
    // create a Rate object of 2Hz
    ros::Rate loop_rate(0.5);
    
    // endless loop until Ctrl + C
    while (ros::ok()) {
        
        
        ROS_DEBUG("There is a missing droid");
        
        
        ROS_INFO("The Emperors Capuchino is done");
        
        
        ROS_WARN("Help me Obi-wan Kenobi, you're my only hope");
        
        
        int exhaust_number = rand() % 100 + 1;
        int port_number = rand() % 100 + 1;
        ROS_ERROR("The thermal exhaust port %d, right below the main port %d", exhaust_number, port_number);
        
        
        ROS_FATAL("The DeathStar is EXPLODING");
        
        loop_rate.sleep();
        ros::spinOnce();
        
    }
    
    return 0;
    
}