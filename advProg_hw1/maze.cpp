//
//  maze.cpp
//  advProg_hw1
//
//  Created by Michael Leong on 10/03/2023.
//

#include "maze.hpp"

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
