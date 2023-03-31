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
    void setMap(int width, int height, vector<string> map);
    
    char getXYofMap(int x, int y) const;
    
    int getWidth() const;
    
    int getHeight() const;
    
    // update one character in the array
    void updateOneElementinMap(int x, int y, char newSymbol);
    
private:
    int width;
    int height;
    // maze map would be a vector of strings
    vector<string> mazeMap;
};

void Maze::setMap(int width, int height, vector<string> map) {
    this->width = width;
    this->height = height;
    this->mazeMap = map;
}

char Maze::getXYofMap(int x, int y) const {
    return mazeMap[x][y];
}

int Maze::getWidth() const {
    return width;
}

int Maze::getHeight() const {
    return height;
}

void Maze::updateOneElementinMap(int x, int y, char newSymbol) {
    mazeMap[x][y] = newSymbol;
}

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

int main()
{
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
}
