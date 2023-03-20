//
//  maze.hpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#ifndef maze_hpp
#define maze_hpp

#include <iostream>
#include <string>

using namespace std;

class Maze {
public:
    // function to set the map, length and width
    void setMap(int length, int width, string map[]);
    
    string *getmap();
    
    // function to set map from standard I/O
    void setMapFromStdIO();
    
    // update one character in the array
    void updateOneElementinMap(int x, int y, char newSymbol);
    
private:
    int length;
    int width;
    // maze map would be an array of strings
    string *mazeMap;
};


#endif /* maze_hpp */
