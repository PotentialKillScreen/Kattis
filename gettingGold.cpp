#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Position {
    int x, y;
};

vector<vector<char> > grid;
int W, H;
Position playerStart;
vector<Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

bool isNearTrap(int x, int y) {
    for (const auto& dir : directions) {
        int nx = x + dir.x;
        int ny = y + dir.y;
        if (grid[nx][ny] == 'T') {
            return true;
        }
    }
    return false;
}

int getMaxSafeGold() {
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    queue<Position> q;
    q.push(playerStart);
    visited[playerStart.x][playerStart.y] = true;

    int goldCount = 0;

    while (!q.empty()) {
        Position pos = q.front();
        q.pop();

        if (grid[pos.x][pos.y] == 'G') {
            goldCount++;
        }
        if (isNearTrap(pos.x, pos.y)){
            continue;
        }
        for (const auto& dir : directions) {
            int nx = pos.x + dir.x;
            int ny = pos.y + dir.y;

            if (!visited[nx][ny] && grid[nx][ny] != '#') {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return goldCount;
}

int main() {
    cin >> W >> H;
    grid.resize(H, vector<char>(W));

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'P') {
                playerStart = {i, j};
            }
        }
    }

    int maxGold = getMaxSafeGold();
    cout << maxGold << endl;

    return 0;
}