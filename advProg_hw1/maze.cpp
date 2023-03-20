//
//  maze.cpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#include "maze.hpp"

void Maze::setMap(int length, int width, string map[]) {
    this->length = length;
    this->width = width;
    this->mazeMap = map;
}

string *Maze::getmap() {
    return this->mazeMap;
}

void Maze::setMapFromStdIO() {
    
}

void Maze::updateOneElementinMap(int x, int y, char newSymbol) {
    this->mazeMap[x][y] = newSymbol;
}
