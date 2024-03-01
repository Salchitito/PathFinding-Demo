//
// Created by Gino Daza on 20/02/2024.
//

#ifndef PATHFINDING_DEMO_MAZE_H
#define PATHFINDING_DEMO_MAZE_H

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <queue>
#include "MementoMaze.h"

using namespace std;

class Maze {
    friend class Menu;
private:
    vector<vector<int>> matrix;
    int rows = 0;
    int columns  = 0;
    stack<MementoMaze> saves;

    pair<int,int> entrance = {0,0};
    pair<int,int> exit = {rows - 1, columns -1};

    bool ismodifing = false;
    int velocity = 30;
    double dijkstra_time = 0;
    double bfs_time = 0;
    double dfs_time = 0;

    Maze() = default;

    // Estas son funciones que podria usar para mas algoritmos

    void recursive_backtracking(int row, int col, bool delay);
    void exploreNeighbor(int row, int col, vector<vector<bool>>& visited, queue<pair<int, int>>& bfsQueue);
    void exploreNeighborDijkstra(int row, int col, int currentDistance, vector<vector<int>>& distance, priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>& pq);

    void fill_matrix();


public:

    Maze(int rows, int columns);

    template<typename  T>
    void print_matrix(vector<vector<T>> vec);

    void setVelocity(int microseconds);

    void addRows(int n);

    void addColums(int n);

    void removeRows(int n);

    void removeColumns(int n);

    void save_maze();

    void load_maze();

    void createOnePathMaze();

    void createMulPathsMaze();

    void apply_dijkstra();

    void apply_bfs();

    void apply_dfs();


};


#endif //PATHFINDING_DEMO_MAZE_H
