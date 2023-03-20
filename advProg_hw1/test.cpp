#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

class Maze {
public:
    // function to set the map, length and width
    void setMap(int width, int height, string map[]);
    
    // function to set map from standard I/O
    void setMapFromStdIO();
    
    char getXYofMap(int x, int y) const {
        return mazeMap[x][y];
    }
    
    int getWidth() const {
        return width;
    }
    
    int getHeight() const {
        return height;
    }
    
    // update one character in the array
    void updateOneElementinMap(int x, int y, char newSymbol);
    
private:
    int width;
    int height;
    // maze map would be a vector of strings
    vector<string> mazeMap;
};

class Robot {
private:
    // coordinates of the robot
    int coordX;
    int coordY;
    char dir; //the direction which the robots is facing
    bool isSamePathHistory(vector<char> pathHistoryA, vector<char> pathHistoryB);
    // try to move robot in exactly one loop with starting point at current position and return the pathHistory and steps within n steps
    // if no loops found then robot will just move n steps and update path history and return 0;
    long long moveRobot1LoopGetHistory(long long n, Maze maze, vector<char> pathHistory);
    
public:
    void moveRobot(Maze maze);
    void moveRobotNSteps(long long n, Maze maze);
    // robot willl try to find a loop within timeout number of steps and move 1 loop if cannot find robot will remain at the original coordinates
    long long findLoop(long long &n, Maze maze, vector<char> pathHistory, int timeout);
};

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
            if(coordY == maze.getHeight()-1 || maze.getXYofMap(coordY, coordX) == '#') {
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

void Robot::moveRobotNSteps(long long n, Maze maze) {
    for(long long i = 0; i < n; i++) {
        moveRobot(maze);
    }
}

bool Robot::isSamePathHistory(vector<char> pathHistoryA, vector<char> pathHistoryB) {
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

long long Robot::moveRobot1LoopGetHistory(long long n, Maze maze, vector<char> pathHistory) {
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

long long Robot::findLoop(long long &n, Maze maze, vector<char> pathHistory, int timeout) {
    // try 10000 steps
    int oldX = coordX;
    int oldY = coordY;
    char oldDir = dir;
    long long currSteps = 0;
    int loopTimeout = INT_MAX; // i feel uncomfortable using endless loop so i'll add a loop timout
    
    while(loopTimeout > 0) {
        currSteps = moveRobot1LoopGetHistory(n, maze, pathHistory);
        if(currSteps != 0) {
            cerr << "found loop" << endl;
            return currSteps;
        }
        
        moveRobot(maze);
        n--;
        coordX = oldX;
        coordY = oldY;
        dir = oldDir;
        
        loopTimeout--;
    }
    
    return 0;
}

void moveRobot(int &coordX, int &coordY, char &dir, string maze[], int h) {
    while(1) {
        if(dir == 'N') {
            if(coordY == 0 || maze[coordY-1][coordX] == '#') {
                dir = 'E';
            } else {
                //move forward
                coordY--;
                return;
            }
        } else if(dir == 'E') {
            if(coordX == maze[0].length() -1 || maze[coordY][coordX+1] == '#') {
                dir = 'S';
            } else {
                //move forward
                coordX++;
                return;
            }
        } else if(dir == 'S') {
            if(coordY == h-1 || maze[coordY+1][coordX] == '#') {
                dir = 'W';
            } else {
                //move forward
                coordY++;
                return;
            }
        } else if(dir == 'W') {
            if(coordX == 0 || maze[coordY][coordX-1] == '#') {
                dir = 'N';
            } else {
                //move forward
                coordX--;
                return;
            }
        }
    }
}

void moveRobotNSteps(int &coordX, int &coordY, long long n, char &dir, string maze[], int h) {
    for(long long i = 0; i < n; i++) {
        moveRobot(coordX, coordY, dir, maze, h);
    }
    
    return;
}

bool isSamePathHistory(vector<int> pathHistoryA, vector<int> pathHistoryB) {
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

long long getStepsInLoop(int &coordX, int &coordY, int oriX, int oriY, long long n, char &dir, string maze[], int h, vector<int> pathHistory) {
    
    for(long long i = 0; i < n; i++) {
        moveRobot(coordX, coordY, dir, maze, h);
        pathHistory.push_back(coordX);
        pathHistory.push_back(coordY);
        if(coordX == oriX && coordY == oriY && i > 0) {
            return i+1;
        }
    }
    
    return 0;
}

long long findLoop(int &coordX, int &coordY, long long &n, char &dir, string maze[], int h, vector<int> pathHistory) {
    // try 10000 steps
    int oldX = coordX;
    int oldY = coordY;
    char oldDir = dir;
    long long currSteps = 0;
    int timeout = 1000; //try 1000 times
    int loopTimeout = INT_MAX; // i feel uncomfortable using endless loop so i'll add a loop timout
    
    while(loopTimeout > 0) {
        currSteps = getStepsInLoop(coordX, coordY, coordX, coordY, timeout, dir, maze, h, pathHistory);
        if(currSteps != 0) {
            cerr << "found loop" << endl;
            return currSteps;
        }
        
        moveRobot(oldX, oldY, oldDir, maze, h);
        n--;
        coordX = oldX;
        coordY = oldY;
        dir = oldDir;
        
        loopTimeout--;
    }
    
    return 0;
}

int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    long long n;
    size_t found = string::npos;
    string maze[h];
    int coordY = 0;
    int coordX = 0;
    int oriY = 0;
    int oriX = 0;
    long long stepsInLoop = 0;
    long long stepsRemaining = 0;
    char dir = 'N'; //N up S down E right W left
    vector<vector<int>> pathHistories;
    cin >> n; cin.ignore();
    
    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, line);
        maze[i] = line;
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
    
    if(n > 10000) {
        for(int i = 0; i < n; i++) {
            vector<int> temp;
            stepsInLoop = findLoop(coordX, coordY, n, dir, maze, h, temp);
            cerr << "X: " << coordX << " Y: " << coordY << " dir: " << dir << endl;
            n -= stepsInLoop;
            
            pathHistories.push_back(temp);
            
            if(i > 0 && isSamePathHistory(pathHistories[i-1], pathHistories[i])) {
                //run at least twice
                cerr << "same" << endl;
                break;
            }
        }
        
        stepsRemaining = n % stepsInLoop;
        
        moveRobotNSteps(coordX, coordY, stepsRemaining, dir, maze, h);
        
    } else {
        // n less than 10000 we can just use brute force :D
        moveRobotNSteps(coordX, coordY, n, dir, maze, h);
    }
    
    string answer = to_string(coordX) + " " + to_string(coordY);


    cout << answer << endl;
}
