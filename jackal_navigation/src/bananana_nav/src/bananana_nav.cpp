//============================================================================
// Name        : bananana_nav.cpp
// Author      : Gabriel Earley and Justin Alabaster
// Version     : #2.2 with improved formating and commenting
// Copyright   : Your copyright notice
// Description : banana_nav library
//==============================================================================
#include "ros/ros.h"
#include <bananana_nav/bananana_nav.h>
#include "std_msgs/String.h"
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>

using namespace std;

typedef costmap_2d::Costmap2D int8;

int buffer = 200;//Determines what cost values are considered objects

//Finds the goal and returns if it found one or not
bool FindGoal(Goal &currentGoal,int8 map, int m_x,int m_y,double resolution){


	//Stores the bounds of the map
	int maxHeight = m_y; int maxWidth = m_x;

	//for loop variables
	int height = 0; int width = 0;

	//Triggers that are set if a tree is found
	bool RTtrigger = false; bool LTtrigger = false;

	//Holds the cost of the tree on the left and right
	int RTcost = 0; int LTcost = 0;

	//variable that holds half the width of the map
	int halfWidth =maxWidth/2;

	//variables that hold the location of the closet tree on the left and right
	float LTLocatedHeight = 0; float LTLocatedWidth = 0;
	float RTLocatedHeight = 0; float RTLocatedWidth = 0;

	//while left tree and right tree have not been found
	for(height = maxHeight/2; height<=maxHeight; height++){

		for(width = halfWidth; width>=0;width = width - 1) {//search for the closet tree/obstacle to the left of the base_link

				LTcost = map.getCost(width,height);
                                //ROS_INFO("width = %d",width);
				ROS_INFO("LTcost = %d",LTcost);//Used for Debug

				//add in check if index is outside of map//////////////////////////////////////////////////////////////////////
				if ((LTcost > buffer) && (LTtrigger == false)){//found a lethal cost and haven't found one before this.									//lethal points are trees and it WILL NOT see last layers trees
					LTtrigger = true;
                                        ROS_INFO("TRUE");
					LTLocatedHeight = height;
					LTLocatedWidth = width;
				}

		}
		for(width = halfWidth; width <= maxWidth;width++){//search for the closet tree/obstacle to the right of the base_link

			if(width>halfWidth){ //Find first tree on right side of base_link
				RTcost = map.getCost(width,height);

				//ROS_INFO("RTcost = %d",RTcost);//Used for Debug

				if ((RTcost > buffer) && (RTtrigger == false)){//found a lethal cost and haven't found one before this.									//lethal points are trees and it WILL NOT see last layers trees
					RTtrigger = true;
					RTLocatedHeight = height;
					RTLocatedWidth = width;
				}
			}
		}
	}

	//Return false if no trees and sets goal to 0,0
	if(RTtrigger == false || LTtrigger == false){//Check if there are no trees

		ROS_INFO("I messed UP");//Displays if we don't see both trees
		if(LTtrigger)ROS_INFO("LT trigger is true");//Displays if we see tree on left side
		if(RTtrigger)ROS_INFO("RT trigger is true");//Displays if we see tree on right side

		currentGoal.y = 0;
		currentGoal.x = 0;
		return false;
	}

	//Return true, we have found two trees and have a goal
	else if((RTtrigger == true && LTtrigger == true)){

		//Location from bot in meters
		float MRTLocatedWidth = -resolution*(RTLocatedWidth-maxWidth/2);
		float MLTLocatedWidth = -resolution*(LTLocatedWidth-maxWidth/2);
		float MRTLocatedHeight = resolution*(RTLocatedHeight-maxHeight/2);
		float MLTLocatedHeight = resolution*(LTLocatedHeight-maxHeight/2);

		//Displays if we see trees
		ROS_INFO("I did the right thing \n right trigger is at height %f and width %f and left trigger is at height %f and width %f",MRTLocatedHeight,MRTLocatedWidth,MLTLocatedHeight,MLTLocatedWidth);

		//Sets the goal points based how the center of the local map which is the location of the base_link
		currentGoal.y = resolution*(-1*((RTLocatedWidth + LTLocatedWidth)/2 - (maxWidth/2)));//negative because Y to the left is positive
		currentGoal.x = resolution*((RTLocatedHeight +LTLocatedHeight)/2 - (maxHeight/2));

		//ROS_INFO("goal is at x = %f and y = %f",currentGoal.x,currentGoal.y); //Used for Debug
		return true;

	}
}




////////////////////////////////////////////////////////Find ROW/////////////////////////////////////////////////////////////////////////



//determines and gives the location of the next spot to look for trees
bool FindRow(Goal& currentGoal,int8 map, int m_x,int m_y, bool direction, double resolution)
{
	//Stores the bounds of the map
	int maxHeight = m_y; int maxWidth = m_x;

	//for loop variables
	int height = 0; int width = 0;

	//Triggers that are set if a tree is found
	bool RTtrigger = false; bool LTtrigger = false;

	//Holds the cost of the tree on the left and right
	int RTcost = 0; int LTcost = 0;

	//variable that holds half the width of the map
	int halfWidth =maxWidth/2;

	//variables that hold the location of the closet tree on the left and right
	int LTLocatedHeight = 0; int LTLocatedWidth = 0;
	int RTLocatedHeight = 0; int RTLocatedWidth = 0;

	double heightOffset = 1.2; //amount to move in the x direction away from next row

	double widthOffset = .5; //amount to move in the y direction past the first tree on the next row

	//depending on the direction the goal will be on a different side
	switch(direction)
	{

	//enact if base_link is facing positive x
	case true:
		for(height = maxHeight; height>0; height--){//Stop from top of
			//search for the closet tree/obstacle to the left of the base_link
			for(width = halfWidth; width<maxWidth;width++) {
				if(width<halfWidth){
					RTcost = map.getCost(height,width);
					if ((RTcost > buffer) && (RTtrigger != true)){//found a lethal cost and haven't found one before this. Assumes only 										//lethal points are trees and it WILL NOT see last layers trees
						RTtrigger = true;
						RTLocatedHeight = height;
						RTLocatedWidth = width;
					}
				}
			}
		}
		if(RTtrigger == false){
			//No tree found error
			currentGoal.x = 0;
			currentGoal.y = 0;
			return false;
		}
		else{
			//Set goal to be in front of the next row
			currentGoal.y = resolution*(-1*(RTLocatedWidth + LTLocatedWidth)/2 - maxWidth/2) - widthOffset;
			currentGoal.x = resolution*((RTLocatedHeight +LTLocatedHeight)/2 - maxHeight/2) + heightOffset;
			currentGoal.orientation = false;//Set goal so base_link is facing negative x
			return true;
		}
		break;
		//enact if base_link is facing negative x
	case false:
		for(height = maxHeight; height>0; height--){
			//search for the closet tree/obstacle to the left of the base_link
			for(width = halfWidth; width>=0;width--) {
				if(width<halfWidth){
					LTcost = map.getCost(height,width);
					if ((LTcost > buffer) && (LTtrigger != true)){//found a lethal cost and haven't found one before this. Assumes only 										//lethal points are trees and it WILL NOT see last layers trees
						LTtrigger = true;
						LTLocatedHeight = height;
						LTLocatedWidth = width;
					}
				}
			}
		}
		if(LTtrigger == false){
			//No tree found Error
			currentGoal.x = 0;
			currentGoal.y = 0;
			return false;
		}
		else{
			//Set goal to be in front of the next row
			currentGoal.y = -resolution*((RTLocatedWidth + LTLocatedWidth)/2 - maxWidth/2) + widthOffset;
			currentGoal.x = resolution*(RTLocatedHeight +LTLocatedHeight)/2 - maxHeight/2 + heightOffset;
			currentGoal.orientation = true; //Set goal so base_link is facing positive x
			return true;
		}
		break;
	default:
		//Should never get to default case
		ROS_INFO("ERROR ERROR ERROR in FindRow");
		return false;
		break;
	}
}



//////////////////////////////////////////////////Check if Done/////////////////////////////////////////////////////////////////////

//determines if we are done and need to return to base
bool CheckifDone(int8 map, int m_x,int m_y){


	//Stores the bounds of the map
	int maxHeight = m_y; int maxWidth = m_x;

	//for loop variables
	int height = 0; int width = 0;

	//Triggers that are set if a tree is found
	bool RTtrigger = false; bool LTtrigger = false;

	//Holds the cost of the tree on the left and right
	int RTcost = 0; int LTcost = 0;

	//variable that holds half the width of the map
	int halfWidth = maxWidth/2;


	for(height = ((maxHeight/2) + (0.1*maxHeight)); height<maxHeight; height++){

		for(width = halfWidth; width>=0;width--) { //search for the closet tree/obstacle to the left of the base_link

			if(width<halfWidth){ //Find first tree on left side of base_link

				LTcost = map.getCost(height,width);
				if ((LTcost > buffer) && (LTtrigger != true)){//found a lethal cost and haven't found one before this. Assumes only 										//lethal points are trees and it WILL NOT see last layers trees
					LTtrigger = true;
				}
			}
		}

		for(width = halfWidth; width < maxWidth;width++){ //search for the closet tree/obstacle to the right of the base_link

			if(width>halfWidth){ //Find first tree on right side of base_link

				RTcost = map.getCost(width,height);
				if ((RTcost > buffer) && (RTtrigger != true)){//found a lethal cost and haven't found one before this. Assumes only 										//lethal points are trees and it WILL NOT see last layers trees
					RTtrigger = true;
				}
			}
		}
	}

	if(RTtrigger == true && LTtrigger == true){//Check if there are trees on both sides
		return true;
	}
	else return false;//There are no trees on either side
}

