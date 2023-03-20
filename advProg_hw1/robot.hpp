//
//  robot.hpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#ifndef robot_hpp
#define robot_hpp

#include "maze.hpp"
#include <iostream>

class Robot {
public:
    //move the robot
    void move(string maze[], int h);
    
    void moveNSteps(long long n, string maze[], int h);
    
private:
    // coordinates of the robot
    int coordX;
    int coordY;
    char dir; //the direction which the robots is facing
};

#endif /* robot_hpp */
