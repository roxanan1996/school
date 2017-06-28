#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /*
     * Daca vreti sa folositi iostream(cin si cout) in loc de stdio(scanf si printf), decomentati linia urmatoare
     * cin este mult mai lent decat scanf in general, dar decomentand linia nu se va simti diferenta de timp
     * Nu folositi stdio daca decomentati linia => posibile probleme de sincronizare
     **/
    //std::ios::sync_with_stdio(false);  
  
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int N, K;
    
    cin >> N >> K;
    
    int d[N][N];
    int s[K];
    int S = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
        cin >> d[i][j];
            if (j > i) {
                S += d[i][j];
            }
        }
    }
    
    for (int drumulete = 0; drumulete < K; ++drumulete) {
        int nod1, nod2, drum;
        cin >> nod1 >> nod2 >> drum;
        if (d[nod1 - 1][nod2 - 1] > drum) {
            S -= d[nod1 - 1][nod2 - 1];
            S += drum;
            d[nod1 - 1][nod2 - 1] = drum;
            d[nod2 - 1][nod1 - 1] = drum;
            
            for (int k = 0; k < N; ++k) {
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        int vechiDrum = d[i][j];
                        d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                        if (j > i && vechiDrum != d[i][j]) {
                            S -= vechiDrum;
                            S += d[i][j];
                        }
                    }
                }
            }
        
            cout << S << " ";
        }
    }
    
    return 0;
}
