#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Point {
    int row;
    int col;

    bool operator<(const Point& other) const {
        if (row == other.row) {
            return col < other.col;
        }
        return row < other.row;
    }
};

const int ROWS = 20;
const int COLS = 40;
const int INF = numeric_limits<int>::max();

bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

bool isWall(const vector<vector<int>>& playground, int row, int col) {
    return playground[row][col] == 1;
}

void drawPlayground(const vector<vector<int>>& playground, const vector<Point>& path, Point start, Point end) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (isWall(playground, i, j)) {
                cout << "#";
            }
            else if (i == start.row && j == start.col) {
                cout << "A";
            }
            else if (i == end.row && j == end.col) {
                cout << "B";
            }
            else {
                bool isPath = false;
                for (const Point& p : path) {
                    if (p.row == i && p.col == j) {
                        isPath = true;
                        break;
                    }
                }
                if (isPath) {
                    cout << "*";
                }
                else {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}

vector<Point> dijkstra(const vector<vector<int>>& playground, Point start, Point end) {
    vector<vector<int>> distance(ROWS, vector<int>(COLS, INF));
    vector<vector<Point>> prev(ROWS, vector<Point>(COLS, { -1, -1 }));

    distance[start.row][start.col] = 0;

    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        Point current = pq.top().second;
        pq.pop();

        int currRow = current.row;
        int currCol = current.col;

        static const int dr[] = { -1, 1, 0, 0 };
        static const int dc[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int newRow = currRow + dr[i];
            int newCol = currCol + dc[i];

            if (isValid(newRow, newCol) && !isWall(playground, newRow, newCol)) {
                int weight = 1; // Udaljenost izmeðu susjednih æelija je 1

                if (distance[currRow][currCol] + weight < distance[newRow][newCol]) {
                    distance[newRow][newCol] = distance[currRow][currCol] + weight;
                    prev[newRow][newCol] = current;
                    pq.push({ distance[newRow][newCol], { newRow, newCol } });
                }
            }
        }
    }

    vector<Point> path;
    if (distance[end.row][end.col] != INF) {
        Point current = end;
        while (!(current.row == start.row && current.col == start.col)) {
            path.push_back(current);
            current = prev[current.row][current.col];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    return path;
}

int main() {
    vector<vector<int>> playground(ROWS, vector<int>(COLS, 0));
    Point start, end;

    cout << "Unesite redak i stupac tocke A (A se nalazi na igralistu): ";
    cin >> start.row >> start.col;

    cout << "Unesite redak i stupac tocke B (B se nalazi na igralistu): ";
    cin >> end.row >> end.col;

    int numWalls;
    cout << "Unesite broj zidova: ";
    cin >> numWalls;

    for (int i = 0; i < numWalls; i++) {
        int wallRow, wallCol;
        cout << "Unesite redak i stupac " << i + 1 << ". zida: ";
        cin >> wallRow >> wallCol;
        playground[wallRow][wallCol] = 1;
    }


    vector<Point> path = dijkstra(playground, start, end);

    drawPlayground(playground, path, start, end);

    return 0;
}
