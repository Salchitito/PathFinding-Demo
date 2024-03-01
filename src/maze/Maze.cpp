//
// Created by Gino Daza on 20/02/2024.
//

#include "Maze.h"

Maze::Maze(int _rows, int _columns): rows(_rows), columns(_columns){
    matrix = vector<vector<int>>(rows,vector<int>(columns,1));
    matrix[entrance.first][entrance.second] = 3;
    matrix[exit.first][exit.second] = 4;
    save_maze();
}

template<typename T>
void Maze::print_matrix(vector<vector<T>> vec) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << matrix[i][j] << " ";
        }  cout << endl;
    } cout << endl;

    cout << rows << " " << columns << endl;
}

void Maze::setVelocity(int microseconds) {
    velocity = microseconds;
}

void Maze::addRows(int n) {
    for (int i = 0; i < n; ++i) {
        matrix.emplace_back(vector<int>(columns,0));
    }
}

void Maze::addColums(int n) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i].emplace_back(0);
        }
    }
}

void Maze::removeRows(int n) {
    for (int i = 0; i < n; ++i) {
        matrix.pop_back();
    }
}

void Maze::removeColumns(int n) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i].pop_back();
        }
    }
}

void Maze::save_maze() {
    saves.push(MementoMaze(matrix,rows,columns,entrance,exit));
    cout << "Tamaño de saves: " << saves.size() << endl;
}

void Maze::load_maze() {
    if(!saves.empty()){
        matrix = saves.top().matrix;
        rows = saves.top().rows;
        columns = saves.top().columns;
        entrance = saves.top().entrance;
        exit = saves.top().exit;
        if(saves.size() > 1) saves.pop();
        cout << "Cargando maze anterior" << endl;
        cout << "Tamaño de saves: " << saves.size() << endl;
    }
}


void Maze::createOnePathMaze() {
    recursive_backtracking(0,0,true);
    save_maze();
}

void Maze::createMulPathsMaze() {
    recursive_backtracking(0,0, false);

    int obstacles = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(matrix[i][j] == 1) obstacles++;
        }
    }

    int obstacles_removed = 0;
    while(obstacles_removed < obstacles / 4){
        int i = rand() % rows; int j = rand() % columns;
        this_thread::sleep_for(chrono::microseconds (velocity));
        if(matrix[i][j] == 1){ matrix[i][j] = 0; obstacles_removed++;}
    }
    matrix[entrance.first][entrance.second] = 3;
    matrix[exit.first][exit.second] = 4;
    save_maze();
}

void Maze::fill_matrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = 1;
        }
    }
}



void Maze::recursive_backtracking(int row, int col, bool delay) {
    fill_matrix();
    srand(time(NULL));

    cout << "Creando laberinto con recursive backtraking..." << endl;
    ismodifing = true;

    matrix[row][col] = 0;
    std::stack<std::pair<int, int>> arrow_position;
    std::vector<std::pair<int, int>> visited_position;

    arrow_position.emplace(row, col);
    visited_position.emplace_back(row, col);

    vector<std::pair<int, int>> directions = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    while (!arrow_position.empty()) {
        matrix[entrance.first][entrance.second] = 3;
        matrix[exit.first][exit.second] = 4;
        std::random_shuffle(directions.begin(), directions.end());
        bool moved = false;

        for (const auto& direction : directions) {
            int new_row = arrow_position.top().first + direction.first;
            int new_col = arrow_position.top().second + direction.second;

            int new_row_back = new_row;
            int new_col_back = new_col;
            if(direction.first == 0) new_col_back +=  (direction.second/ 2) * -1;
            else new_row_back += (direction.first / 2) * -1;

            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < columns) {
                if (std::find(visited_position.begin(), visited_position.end(), std::make_pair(new_row, new_col)) == visited_position.end()) {
                    matrix[new_row_back][new_col_back] = 0;
                    matrix[arrow_position.top().first][arrow_position.top().second] = 2;
                    this_thread::sleep_for(chrono::microseconds (velocity));
                    matrix[new_row][new_col] = 0;
                    matrix[arrow_position.top().first][arrow_position.top().second] = 2;
                    this_thread::sleep_for(chrono::microseconds (velocity));
                    visited_position.emplace_back(new_row, new_col);
                    arrow_position.emplace(new_row, new_col);
                    moved = true;
                    break;
                }
            }
        }

        if (!moved) {
            this_thread::sleep_for(chrono::microseconds (velocity));
            this_thread::sleep_for(chrono::microseconds (velocity));
            matrix[arrow_position.top().first][arrow_position.top().second] = 0;
            arrow_position.pop();
        }
    }
    matrix[entrance.first][entrance.second] = 3;
    matrix[exit.first][exit.second] = 4;
    if(delay)this_thread::sleep_for(chrono::milliseconds (850));
    ismodifing = false;
}


void Maze::apply_dfs() {
    auto start = chrono::high_resolution_clock::now();
    srand(time(NULL));
    ismodifing = true;

    int row = entrance.first, col = entrance.second;

    vector<vector<bool>> visited(rows, vector<bool>(columns, false));

    bool foundExit = false;

    stack<pair<int, int>> dfs_stack;
    dfs_stack.push({row, col});

    while (!dfs_stack.empty() && !foundExit) {
        pair<int, int> current = dfs_stack.top();
        dfs_stack.pop();

        row = current.first;
        col = current.second;


        // Verifica que el movimiento actual sea posible, si no volvera a empezar el bucle
        if (row < 0 || row >= rows || col < 0 || col >= columns || visited[row][col] || matrix[row][col] == 1) {
            continue;
        }

        // Marca la celda como visitada
        visited[row][col] = true;
        this_thread::sleep_for(chrono::microseconds (velocity));
        matrix[row][col] = 2;

        // esto lo use para verificar cuando funcionaba mal
        cout << "Visitando celda (" << row << ", " << col << ")" << endl;

        // Si encontramos la salida, actualizamos el indicador y finalizamos
        if (row == exit.first && col == exit.second) {
            matrix[entrance.first][entrance.second] = 3;
            matrix[exit.first][exit.second] = 4;
            cout << "Salida encontrada" << endl;

            break;
        }

        // Obtener direcciones aleatorias
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        random_shuffle(directions.begin(), directions.end());

        // Agregar vecinos no visitados al stack
        for (const auto& direction : directions) {
            int newRow = row + direction.first;
            int newCol = col + direction.second;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && !visited[newRow][newCol]) {
                dfs_stack.push({newRow, newCol});
            }
        }
    }

    matrix[entrance.first][entrance.second] = 3;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double,milli> total_time = end - start;
    dfs_time = total_time.count();
    this_thread::sleep_for(chrono::milliseconds (850));
    ismodifing = false;
}

// Esto lo hice junto a GPT, por eso los comentarios y la impresion en consola

void Maze::apply_bfs(){
    ismodifing = true;
    auto start = chrono::high_resolution_clock::now();

    int startRow = entrance.first, startCol = entrance.second;

    // Inicializa la matriz de visitados
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));

    // Cola para BFS
    queue<pair<int, int>> bfsQueue;

    // Inicia el bfs desde el punto de partida
    bfsQueue.push({startRow, startCol});
    visited[startRow][startCol] = true;

    while (!bfsQueue.empty()) {
        // Obtiene las coordenadas actuales en la cola
        int currentRow = bfsQueue.front().first;
        int currentCol = bfsQueue.front().second;
        bfsQueue.pop();

        // Console test
        cout << "Visitando celda (" << currentRow << ", " << currentCol << ")" << endl;

        // Si llego a la salida
        if (currentRow == exit.first && currentCol == exit.second) {
            matrix[exit.first][exit.second] = 4;
            cout << "Salida encontrada" << endl;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double,milli> total_time = end - start;
            bfs_time = total_time.count();
            this_thread::sleep_for(chrono::milliseconds (850));
            ismodifing = false;
            return;
        }

        // Explora los vecinos no visitados
        exploreNeighbor(currentRow - 1, currentCol, visited, bfsQueue);
        exploreNeighbor(currentRow + 1, currentCol, visited, bfsQueue);
        exploreNeighbor(currentRow, currentCol - 1, visited, bfsQueue);
        exploreNeighbor(currentRow, currentCol + 1, visited, bfsQueue);

    }
    matrix[entrance.first][entrance.second] = 3;
    cout << "No se encontro la salida" << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double,milli> total_time = end - start;
    bfs_time = total_time.count();
    this_thread::sleep_for(chrono::milliseconds (850));
    ismodifing = false;
}

void Maze::exploreNeighbor(int row, int col, vector<vector<bool>>& visited, queue<pair<int, int>>& bfsQueue) {
    // Verificar limites y si la celda ya ha sido visitada
    if (row >= 0 && row < rows && col >= 0 && col < columns && matrix[row][col] != 1 && !visited[row][col]) {
        // Marcar la celda como visitada
        this_thread::sleep_for(chrono::microseconds (velocity));
        matrix[row][col] = 2;
        visited[row][col] = true;
        // Agregar la celda a la cola para explorar sus vecinos
        bfsQueue.push({row, col});
    }
}

// Dijkstra

void Maze::apply_dijkstra() {
    ismodifing = true;
    auto start = chrono::high_resolution_clock::now();

    // Obtiene las coordenas de la entrada

    int startRow = entrance.first, startCol = entrance.second;

    // Inicializa la matriz de distancias
    vector<vector<int>> distance(rows, vector<int>(columns, INT_MAX));

    // Prioridad maxima en la cola de prioridad
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // Inicia Dijkstra desde el punto de entrada
    pq.push({0, {startRow, startCol}});
    distance[startRow][startCol] = 0;

    while (!pq.empty()) {
        // Obtiene las coordenadas actuales de la cola
        int currentRow = pq.top().second.first;
        int currentCol = pq.top().second.second;
        int currentDistance = pq.top().first;
        pq.pop();

        this_thread::sleep_for(chrono::microseconds (velocity));
        matrix[currentRow][currentCol] = 2;

        // Console test
        cout << "Visitando celda (" << currentRow << ", " << currentCol << ") con distancia " << currentDistance << endl;

        // Comprueba si hemos llegado a la salida
        if (currentRow == exit.first && currentCol == exit.second) {
            matrix[entrance.first][entrance.second] = 3;
            matrix[exit.first][exit.second] = 4;
            cout << "Salida encontrada" << endl;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double,milli> total_time = end - start;
            dijkstra_time = total_time.count();
            this_thread::sleep_for(chrono::milliseconds (850));
            ismodifing = false;
            return;
        }

        // Explora vecinos
        exploreNeighborDijkstra(currentRow - 1, currentCol, currentDistance + 1, distance, pq);
        exploreNeighborDijkstra(currentRow + 1, currentCol, currentDistance + 1, distance, pq);
        exploreNeighborDijkstra(currentRow, currentCol - 1, currentDistance + 1, distance, pq);
        exploreNeighborDijkstra(currentRow, currentCol + 1, currentDistance + 1, distance, pq);
    }

    matrix[entrance.first][entrance.second] = 3;

    cout << "No se encontro la salida" << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double,milli> total_time = end - start;
    dijkstra_time = total_time.count();
    this_thread::sleep_for(chrono::milliseconds (850));
    ismodifing = false;
}

void Maze::exploreNeighborDijkstra(int row, int col, int currentDistance, vector<vector<int>>& distance, priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>& pq) {
    // Verificar límites y si la celda es accesible
    if (row >= 0 && row < rows && col >= 0 && col < columns && matrix[row][col] != 1) {
        // Actualizar la distancia si es menor que la distancia almacenada actualmente
        if (currentDistance < distance[row][col]) {
            distance[row][col] = currentDistance;
            // Agregar la celda a la cola de prioridad con la nueva distancia
            pq.push({currentDistance, {row, col}});
        }
    }
}

