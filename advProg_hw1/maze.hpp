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
#include <vector>

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


#endif /* maze_hpp */
