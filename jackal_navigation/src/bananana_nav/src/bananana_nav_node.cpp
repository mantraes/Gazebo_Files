//============================================================================
// Name        : banana_nav_node.cpp
// Author      : Gabriel Earley
// Version     : #2.1 with improved formating and commenting
// Copyright   : Your copyright notice
// Description : banana_nav_node(banana_nav executable)
//==============================================================================
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <bananana_nav/bananana_nav.h>
#include <stdlib.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base/move_base.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>


#include <math.h>
#include <sstream>
#include <iostream>
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
using namespace std;


//typedefs to simplify long object titles

//Allows us to connect with the move_base action server
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;



//typedef geometry_msgs::Pose pose; //Not needed right now but maybe in the future
typedef costmap_2d::Costmap2DROS costmapROS;
typedef costmap_2d::Costmap2D costmap;




//////////////////////////////////////////////////////////////Main Function/////////////////////////////////////////

int main(int argc, char** argv) {


	ros::init(argc,argv,"bananana_nav");//initializes node
	ros::NodeHandle banana_nav;	//Used as a constructor and destructor of ROS nodes

	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base",true);


	
	


	while(!ac.waitForServer(ros::Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}
costmap bubble_costmap;

tf::TransformListener tf(ros::Duration(10));
	costmapROS costmap1("bubble_costmap", tf);
	bubble_costmap = *costmap1.getCostmap();
ros::spinOnce();

	//Object that allow banana_nav to publish to topic if necessary
	//ros::Publisher goal_pub = banana_nav.advertise<std_msgs::String>("goal", 1000);

	

	Goal currentGoal(0,0,true); //custom message type to get goal from function

	move_base_msgs::MoveBaseGoal goal; //message type to send goal to move_base

char *p; //checks if there is an error in converting string to long needed if node takes in inputs

	bool endofRow = false; //Set to true if we are at the end of the row and need to find new row

	bool done = false; //Set to true if we have reached the end of the banana fiel
	//Holds the length and width of the local cost map
	int field_length = 0; int field_width = 0;

	//direction gives the direction base_link is facing.
	bool direction = true; //True means it is facing positive x and False means it is facing negative x


	////////////////////////////////Take in inputs or go to defaults///////////////////////////////////////////////
	//if-else statements are there if no inputs are given and implements default values
	//These might be used later if we want to give the node inputs for testing or otherwise
	/*if(argc == 1)
	{
		//use base_local param file if no inputs are given/////////////////////////////////////////////
		//banana_nav.getParam("field_length",field_length);
		//banana_nav.getParam("field_width",field_width);
		//obtain size of map from costmap
		field_length = global_map.info.height;
		field_width = global_map.info.width;
	}
	else if(argc == 2){
		field_length = strtol(argv[1],&p,10);
		//banana_nav.getParam("field_width",field_width);
		field_width = global_map.info.width;
	}
	else if(argc == 3)
	{
		field_length = strtol(argv[1],&p,10);
		field_width = strtol(argv[2],&p,10);
	}	*/

	//Set the max length and width of the map based on info from the occupancy grid
	field_length = bubble_costmap.getSizeInCellsY();
	field_width = bubble_costmap.getSizeInCellsX();
	double field_resolution = bubble_costmap.getResolution();

	//Wait for Map to be Created
	while(field_length == 0 || field_width == 0){

	//Set the max length and width of the map based on info from the occupancy grid
	field_length = bubble_costmap.getSizeInCellsY();
	field_width = bubble_costmap.getSizeInCellsX();
	


	ROS_INFO("Error Error NO Map Received"); //No map received error message
	}
	//Print out the size of the occupancy grid to see if it makes sense
	ROS_INFO("The field length is %d",field_length);
	ROS_INFO("The field width is %d",field_width);
	ROS_INFO("The field resolution is %f",field_resolution);
	
	while(~done){ //We run a switch until mission is completed. Thus it acts as a state machine

		ros::spinOnce();//Get new map before next planing decision

		switch(endofRow){//We are either going down a row or going to next row

		///////////////////////////////////On Row////////////////////////////////////////////////////////////////////

		//Base_link is currently on a row
		case false:
			endofRow = ~FindGoal(currentGoal, bubble_costmap,field_length,field_width,field_resolution); //obtain goal to send to move_base

			// check that base_link is the right frame
			goal.target_pose.header.frame_id = "base_link";
			goal.target_pose.header.stamp = ros::Time::now();

			//set the goals position
			goal.target_pose.pose.position.x = currentGoal.x;
			goal.target_pose.pose.position.y = currentGoal.y;

			ROS_INFO("Sending goal x = %f and y = %f",currentGoal.x,currentGoal.y); //Print current goal to terminal


			while(!ac.waitForServer(ros::Duration(5.0)))
			{
				ROS_INFO("Waiting for the move_base action server to come up");
			}


			ac.sendGoal(goal); //send goal to move_base
			ac.waitForResult();//Wait for goal to be completed

			//Check if goal was successful. Break if it was not.
			if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
				ROS_INFO("Hooray, J5 moved to goal.");
			else
			{
				//goal failed -> end node
				ROS_INFO("The J5 didn't move to goal. Error...Error...Error");
				done = true;
				return 0; // ends node
			}

			//Get updated costmap before determining if it is an end of a row
			ros::spinOnce();

			//Check if we are at an end of a row
			endofRow = ~FindGoal(currentGoal,bubble_costmap,field_length,field_width,field_resolution);
			break;

			//////////////////////////////Find Next Row////////////////////////////////////////////////////////////////////////////////

			//Need to find next row
		case true:
			//Add error check to FindRow
			FindRow(currentGoal,bubble_costmap,field_length,field_width,direction,field_resolution); //Find goal that lines us up with next row

			// check that base_link is the right frame
			goal.target_pose.header.frame_id = "base_link";
			goal.target_pose.header.stamp = ros::Time::now();

			//set the goals position
			goal.target_pose.pose.position.x = currentGoal.x;
			goal.target_pose.pose.position.y = currentGoal.y;

			if(currentGoal.orientation){//Turns base_link around to look for trees depending on direction

				goal.target_pose.pose.orientation.x = tf::createQuaternionFromYaw(M_PI).getX();
				goal.target_pose.pose.orientation.y = tf::createQuaternionFromYaw(M_PI).getY();
				goal.target_pose.pose.orientation.z = tf::createQuaternionFromYaw(M_PI).getZ();
				goal.target_pose.pose.orientation.w = tf::createQuaternionFromYaw(M_PI).getW();
				direction = false;//base_link is now facing negative x
			}
			else {
				goal.target_pose.pose.orientation.x = tf::createQuaternionFromYaw(0).getX();
				goal.target_pose.pose.orientation.y = tf::createQuaternionFromYaw(0).getY();
				goal.target_pose.pose.orientation.z = tf::createQuaternionFromYaw(0).getZ();
				goal.target_pose.pose.orientation.w = tf::createQuaternionFromYaw(0).getW();
				direction = true;//base link is now facing positive x
			}

			//Print current goal to terminal
			switch(currentGoal.orientation){
			case true:
			ROS_INFO("Sending goal x = %f and y = %f and orientation is positive x",currentGoal.x,currentGoal.y);
			case false:
			ROS_INFO("Sending goal x = %f and y = %f and orientation is negative x",currentGoal.x,currentGoal.y);
			default:
			ROS_INFO("ERROR ERROR ERROR in nextROW/node");
			}

			while(!ac.waitForServer(ros::Duration(5.0)))
			{
			ROS_INFO("Waiting for the move_base action server to come up");
			}


			ac.sendGoal(goal); //send goal to move_base
			ac.waitForResult(); //Wait for goal to be completed

			//Check if goal was successful.
			if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
				ROS_INFO("Hooray, J5 moved to next row.");
				endofRow = false;
			}
			else{  //goal failed -> end node
				ROS_INFO("The J5 didn't turn to next row. Error...Error...Error");
				done = true;
				return 0; //ends node
			}

			//Get new map to check if done
			ros::spinOnce();

			//check if there are no more rows of trees
			done = CheckifDone( bubble_costmap, field_length, field_width);
			break;

		default:
			//Should never get to default case
			ROS_INFO("ERROR ERROR ERROR in banana_nav_node");
			break;
		}
	}

	///////////////////////////////////Return Home/////////////////////////////////////////////////

	//Use map frame so you can return to home
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	//set the goals position to go to 0,0 on the world map
	goal.target_pose.pose.position.x = 0;
	goal.target_pose.pose.position.y = 0;

	//Change the orientation to face positive x
	goal.target_pose.pose.orientation.x = tf::createQuaternionFromYaw(0).getX();
	goal.target_pose.pose.orientation.y = tf::createQuaternionFromYaw(0).getY();
	goal.target_pose.pose.orientation.z = tf::createQuaternionFromYaw(0).getZ();
	goal.target_pose.pose.orientation.w = tf::createQuaternionFromYaw(0).getW();
	ROS_INFO("Sending goal x = %d and y = %d and orientation is front",0,0);

	ac.sendGoal(goal);//send goal to move_base
	ac.waitForResult();//Wait for goal to be completed

	//Check if goal was successful.
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		ROS_INFO("Hooray, J5 Phoned Home and got there");
	}
	else{
		//goal failed -> end node
		ROS_INFO("The J5 didn't go home. Error...Error...Error");
	}
        
	return 0;
   ros::spin();
}

