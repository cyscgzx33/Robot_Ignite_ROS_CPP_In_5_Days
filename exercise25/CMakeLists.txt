cmake_minimum_required(VERSION 2.8.3)
project(exercise25)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Age.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)

# be very careful that is related to system include files
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(publish_age src/publish_age.cpp)

add_dependencies(publish_age ${publish_age_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(publish_age
   ${catkin_LIBRARIES}
 )
 
add_dependencies(publish_age exercise25_generate_messages_cpp)