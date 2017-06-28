#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


int main() {
    
    /*
     * Daca vreti sa folositi iostream(cin si cout) in loc de stdio(scanf si printf), decomentati linia urmatoare
     * cin este mult mai lent decat scanf in general, dar decomentand linia nu se va simti diferenta de timp
     * Nu folositi stdio daca decomentati linia => posibile probleme de sincronizare
     **/
    //std::ios::sync_with_stdio(false);  
  
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int N, M;
    
    cin >> N >> M;
    
    int m[N][M];
    int d[N][M];
    int viz[N][M] = {0};
    
    std::queue<std::pair<int, int> > q;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> m[i][j];
            
            if (m[i][j] == 'X') {
                d[i][j] = -1;
            } else if (m[i][j] == 'G') {
                d[i][j] = 0;
                viz[i][j] = 1;
                q.push(std::pair<int, int>(i, j));
            } else {
                d[i][j] = -1;
            }
        }
    }
    
    while (!q.empty()) {
        std::pair<int, int> curr = q.front();
        q.pop();
        
        std::pair<int, int> v[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < 4; ++i) {
            int ii = curr.first + v[i].first;
            int jj = curr.second+ v[i].second;
            if (ii >= 0 && ii < N && jj >=0 && jj < M && m[i][jj] != 'X' && viz[ii][jj] == 0) {
                viz[ii][jj] = 1;
                d[ii][jj] = d[curr.first][curr.second] + 1;
            }
        }
        
        if (curr.second == 0) {
            int ii = curr.first;
             int jj = M - 1;
            
            if (m[ii][jj] != 'X' && viz[ii][jj] == 0) {
                viz[ii][jj] = 1;
                d[ii][jj] = d[curr.first][curr.second];
            }
        }
        
        if (curr.second == M - 1) {
            int ii = curr.first;
           int jj = 0;
            
            if (m[ii][jj] != 'X' && viz[ii][jj] == 0) {
                viz[ii][jj] = 1;
                d[ii][jj] = d[curr.first][curr.second];
            }
        }
        
        if (curr.first == 0) {
            int ii = N - 1;
            int jj = curr.second;
            
            if (m[ii][jj] != 'X' && viz[ii][jj] == 0) {
                viz[ii][jj] = 1;
                d[ii][jj] = d[curr.first][curr.second];
            }
        }
        
        if (curr.first == N - 1) {
            int ii = 0;
            int jj = curr.second;
            
            if (m[ii][jj] != 'X' && viz[ii][jj] == 0) {
                viz[ii][jj] = 1;
                d[ii][jj] = d[curr.first][curr.second];
            }
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << d[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
