/*
 * bananana_nav.h

 *
 *  Created on: 2/14/2016
 *      Version 3 with costmaps
 *      Author: Gabriel Earley
 */

#ifndef BANANANA_NAV_H_
#define BANANANA_NAV_H_

#include "costmap_2d/costmap_2d_ros.h"
#include <costmap_2d/costmap_2d.h>
typedef costmap_2d::Costmap2D int8;

//custom class to hold goal before sending it to move_base
//Members: x,y, orientation give location of goal relative to base_link
//done tells if path planning is over and if it needs to head back to home
class Goal{
public:
	//location of goal
	double x; double y;

	bool orientation;// true is face positive x; false is face negative x

	Goal(double a, double b, bool c)// Constructor
	{
	x = a;
	y = b;
	orientation =c;
	};

	~Goal(){}//Destructor
};



//Finds the goal and returns if it found one or not
//Param: currentGoal is object you store goal coordinates in. map is the costmap you are wanting information from.
//max_x, max_y are bounds of map.
bool FindGoal(Goal& currentGoal,int8 map,int m_x,int m_y,double resolution);


//determines and gives the location of the next spot to look for trees
//Param: x,y are location of point. map is the costmap you are wanting information from. max_x, max_y are bounds of map.
//direction is the direction the base_link is facing with respect to the world positive x is true and negative x is false
bool FindRow(Goal& currentGoal,int8 map, int m_x,int m_y, bool direction,double resolution);


//determines if we are done and need to return to base
//Param: x,y are location of point. map is the costmap you are wanting information from.
//max_x, max_y are bounds of map.
bool CheckifDone(int8 map, int m_x,int m_y);



#endif /* BANANANA_NAV_H_ */


