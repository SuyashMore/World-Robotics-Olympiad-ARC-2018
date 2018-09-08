cmake_minimum_required(VERSION 2.8.3)
project(Jetson)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  std_msgs
  message_generation
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  Angles.msg
  Position.msg
  ControlSignal.msg
  CtrlSigResponse.msg
  Dyx.msg
  bot.msg
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
 # INCLUDE_DIRS include
 # LIBRARIES Jetson
 # CATKIN_DEPENDS roscpp rospy tf
 # DEPENDS system_lib
)



###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}

# add_library(${PROJECT_NAME} include/Jetson/LineFollowing.cpp )


# catkin_package(INCLUDE_DIRS include
#                LIBRARIES ${PROJECT_NAME})

# install(TARGETS ${PROJECT_NAME}
#         ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#         LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#         RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

# install(DIRECTORY include/${PROJECT_NAME}/
#         DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


#   src/${PROJECT_NAME}/Jetson.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/Jetson_node.cpp)


add_executable(AtmegaNode scripts/AtmegaNode/AtmegaNode.cpp)
target_link_libraries(AtmegaNode ${catkin_LIBRARIES} )


# Motor Unit Tests
add_executable(unit_Motor_Fwd scripts/AtmegaNode/unit_botForward.cpp)
add_executable(unit_Motor_Bck scripts/AtmegaNode/unit_botBackward.cpp)
add_executable(unit_Motor_SLeft scripts/AtmegaNode/unit_botSpot_Left.cpp)
add_executable(unit_Motor_SRight scripts/AtmegaNode/unit_botSpot_Right.cpp)
add_executable(unit_Motor_SfLeft scripts/AtmegaNode/unit_botStrafe_Left.cpp)
add_executable(unit_Motor_SfRight scripts/AtmegaNode/unit_botStrafe_Right.cpp)

target_link_libraries(unit_Motor_Fwd ${catkin_LIBRARIES} )
target_link_libraries(unit_Motor_Bck ${catkin_LIBRARIES} )
target_link_libraries(unit_Motor_SLeft ${catkin_LIBRARIES} )
target_link_libraries(unit_Motor_SRight ${catkin_LIBRARIES} )
target_link_libraries(unit_Motor_SfLeft ${catkin_LIBRARIES} )
target_link_libraries(unit_Motor_SfRight ${catkin_LIBRARIES} )

# Arm Unit Tests on ROS

add_executable(unit_Arm_Cord_disable scripts/AtmegaNode/unit_arm_cordinator_disable.cpp)
add_executable(unit_Arm_Cord_enable scripts/AtmegaNode/unit_arm_cordinator_enable.cpp)
add_executable(unit_Arm_pickup scripts/AtmegaNode/unit_arm_pickup.cpp)
add_executable(unit_Arm_stack scripts/AtmegaNode/unit_arm_stack.cpp)
add_executable(unit_Arm_std scripts/AtmegaNode/unit_arm_standard.cpp)
add_executable(unit_Arm_std_w_cord scripts/AtmegaNode/unit_arm_standard_with_cordinator.cpp)

target_link_libraries(unit_Arm_Cord_enable ${catkin_LIBRARIES} )
target_link_libraries(unit_Arm_Cord_disable ${catkin_LIBRARIES} )
target_link_libraries(unit_Arm_pickup ${catkin_LIBRARIES} )
target_link_libraries(unit_Arm_stack ${catkin_LIBRARIES} )
target_link_libraries(unit_Arm_std ${catkin_LIBRARIES} )
target_link_libraries(unit_Arm_std_w_cord ${catkin_LIBRARIES} )


# Atmega-Node Unit Tests
add_executable(unit_Atmega_Linefollow scripts/AtmegaNode/unit_LineFollowing.cpp)
add_executable(unit_Atmega_Stack scripts/AtmegaNode/unit_Atmega_Stack.cpp)
add_executable(unit_Atmega_WhiteSpace scripts/AtmegaNode/unit_Atmega_WhiteSpace.cpp)
add_executable(unit_Atmega_DeliveryChute scripts/AtmegaNode/unit_Atmega_DeliveryChute.cpp)

target_link_libraries(unit_Atmega_Linefollow ${catkin_LIBRARIES} )
target_link_libraries(unit_Atmega_Stack ${catkin_LIBRARIES} )
target_link_libraries(unit_Atmega_DeliveryChute ${catkin_LIBRARIES} )


## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )


# target_link_libraries(AtmegaNode
#   ${catkin_LIBRARIES} 
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_Jetson.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
