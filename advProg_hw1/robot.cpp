//
//  robot.cpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#include "robot.hpp"

void Robot::setRobot(int coordX, int coordY, char dir) {
    this->coordX = coordX;
    this->coordY = coordY;
    this->dir = dir;
}

int Robot::getCoordX() const {
    return coordX;
}

int Robot::getCoordY() const {
    return coordY;
}

int Robot::getDir() const {
    return dir;
}

void Robot::moveRobot(const Maze maze) {
    while(1) {
        if(dir == 'N') {
            if(coordY == 0 || maze.getXYofMap(coordY-1, coordX) == '#') {
                dir = 'E';
            } else {
                //move forward
                coordY--;
                return;
            }
        } else if(dir == 'E') {
            if(coordX == maze.getWidth() -1 || maze.getXYofMap(coordY, coordX+1) == '#') {
                dir = 'S';
            } else {
                //move forward
                coordX++;
                return;
            }
        } else if(dir == 'S') {
            if(coordY == maze.getHeight()-1 || maze.getXYofMap(coordY+1, coordX) == '#') {
                dir = 'W';
            } else {
                //move forward
                coordY++;
                return;
            }
        } else if(dir == 'W') {
            if(coordX == 0 || maze.getXYofMap(coordY, coordX-1) == '#') {
                dir = 'N';
            } else {
                //move forward
                coordX--;
                return;
            }
        }
    }
}

void Robot::moveRobotNSteps(const long long n, const Maze maze) {
    for(long long i = 0; i < n; i++) {
        moveRobot(maze);
        // cerr << this->getCoordX() << " " << this->getCoordY() << endl;
    }
}

bool Robot::isSamePathHistory(const vector<char> pathHistoryA, const vector<char> pathHistoryB) const{
    if(pathHistoryA.size() != pathHistoryB.size()) {
        return false;
    } else {
        for(size_t i = 0; i < pathHistoryA.size(); i++) {
            if(pathHistoryA[i] != pathHistoryB[i]) {
                return false;
            }
        }
        return true;
    }
}

long long Robot::moveRobot1LoopGetHistory(long long n, const Maze maze, vector<char> pathHistory) {
    int oriX = coordX;
    int oriY = coordY;
    
    for(long long i = 0; i < n; i++) {
        moveRobot(maze);
        pathHistory.push_back(coordX);
        pathHistory.push_back(coordY);
        if(coordX == oriX && coordY == oriY && i > 0) {
            return i+1;
        }
    }
    
    return 0;
}

long long Robot::findLoop(long long &n, const Maze maze, vector<char> pathHistory, int timeout) {
    // try 10000 steps
    int oldX = coordX;
    int oldY = coordY;
    char oldDir = dir;
    long long currSteps = 0;
    int loopTimeout = INT_MAX; // i feel uncomfortable using endless loop so i'll add a loop timout
    
    while(loopTimeout > 0) {
        pathHistory.clear();
        
        currSteps = moveRobot1LoopGetHistory(timeout, maze, pathHistory);
        if(currSteps != 0) {
            cerr << "found loop" << endl;
            return currSteps;
        }
        
        coordX = oldX;
        coordY = oldY;
        dir = oldDir;
        moveRobot(maze);
        oldX = coordX;
        oldY = coordY;
        oldDir = dir;
        
        n--;
        
        loopTimeout--;
    }
    
    return 0;
}
