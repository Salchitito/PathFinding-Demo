//
// Created by Gino Daza on 24/02/2024.
//

#ifndef PATHFINDING_DEMO_MEMENTOMAZE_H
#define PATHFINDING_DEMO_MEMENTOMAZE_H

#include <vector>

using namespace std;

// Patron de diseño 2: Memento

class MementoMaze{
    friend class Maze;
private:
    vector<vector<int>> matrix;
    int rows;
    int columns;

    pair<int,int> entrance;
    pair<int,int> exit;
    MementoMaze() = default;
public:
    MementoMaze(const vector<vector<int>> &matrix, int rows, int columns, const pair<int, int> &entrance,
                const pair<int, int> &exit) : matrix(matrix), rows(rows), columns(columns), entrance(entrance),
                                              exit(exit) {}
};

#endif //PATHFINDING_DEMO_MEMENTOMAZE_H
