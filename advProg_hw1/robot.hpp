//
//  robot.hpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#ifndef robot_hpp
#define robot_hpp

#include "maze.hpp"
#include <climits>

class Robot {
private:
    // coordinates of the robot
    int coordX;
    int coordY;
    char dir; //the direction which the robots is facing
    // try to move robot in exactly one loop with starting point at current position and return the pathHistory and steps within n steps
    // if no loops found then robot will just move n steps and update path history and return 0;
    long long moveRobot1LoopGetHistory(long long n, const Maze maze, vector<char> pathHistory);
    
public:
    void setRobot(int coordX, int coordY, char dir);
    int getCoordX() const;
    int getCoordY() const;
    int getDir() const;
    void moveRobot(const Maze maze);
    void moveRobotNSteps(const long long n, const Maze maze);
    // robot willl try to find a loop within timeout number of steps and move 1 loop if cannot find robot will remain at the original coordinates
    bool isSamePathHistory(vector<char> pathHistoryA, vector<char> pathHistoryB) const;
    long long findLoop(long long &n, const Maze maze, vector<char> pathHistory, int timeout);
};


#endif /* robot_hpp */
