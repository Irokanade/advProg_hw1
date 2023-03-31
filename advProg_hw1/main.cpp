//
//  main.cpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include "maze.hpp"
#include "robot.hpp"

using namespace std;

int main() {
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    long long n;
    size_t found = string::npos;
    vector<string> inputmaze;
    int coordY = 0;
    int coordX = 0;
    int oriY = 0;
    int oriX = 0;
    long long stepsInLoop = 0;
    long long stepsRemaining = 0;
    char dir = 'N'; //N up S down E right W left
    vector<vector<char>> pathHistories;
    cin >> n; cin.ignore();
    
    const int timeout = 10000;
    
    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, line);
        inputmaze.push_back(line);
        if (found == string::npos) {
            found = line.find("O");
            if(found != string::npos) {
                coordY = i;
                coordX = (int)found;
                oriY = coordY;
                oriX = coordX;
            }
        }
    }
    
    Robot myRobot;
    myRobot.setRobot(oriX, oriY, dir);
    
    Maze myMaze;
    myMaze.setMap((int)inputmaze[0].size(), h, inputmaze);
    
    
    if(n > 10000) {
        for(int i = 0; i < n; i++) {
            vector<char> temp;
            stepsInLoop = myRobot.findLoop(n, myMaze, temp, timeout);
            n -= stepsInLoop;
            pathHistories.push_back(temp);
            
            cerr << "X: " << coordX << " Y: " << coordY << " dir: " << dir << endl;
            
            if(i > 0 && myRobot.isSamePathHistory(pathHistories[i-1], pathHistories[i])) {
                //run at least twice
                break;
            }
        }
        
        stepsRemaining = n % stepsInLoop;
        myRobot.moveRobotNSteps(stepsRemaining, myMaze);
        
    } else {
        cerr << myRobot.getCoordX() << " " << myRobot.getCoordY() << endl;
        // n less than 10000 we can just use brute force :D
        myRobot.moveRobotNSteps(n, myMaze);
    }
    
    string answer = to_string(myRobot.getCoordX()) + " " + to_string(myRobot.getCoordY());


    cout << answer << endl;
    
    return 0;
}
