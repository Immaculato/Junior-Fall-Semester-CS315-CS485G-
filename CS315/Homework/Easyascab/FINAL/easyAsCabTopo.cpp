//THIS SOLUTION IS NOT MY ORIGINAL WORK --------------
//All credit is given to the ACM Mid-Central Regionals 2016 judges for this implementation.

#include <iostream>
using namespace std;

bool edge[26][26];

void dump(int N, bool ready[], int indeg[]) {
    cout << "----------------" << endl;
    for (int j=0; j < N; j++)
        cout << char('a'+j) << " " << indeg[j] << " " << (ready[j] ? "ready" : "no") << endl;
}

int main() {
    for (int j=0; j < 26; j++)
        for (int k=0; k < 26; k++)
            edge[j][k] = false;

    char L;
    int M;
    int N;
    bool possible(true), unique(true);
    cin >> L >> M;
    N = 1 + L - 'a';

    bool ready[N];
    int indeg[N];
    for (int j=0; j<N; j++) {
        ready[j] = true;
        indeg[j] = 0;
    }

    string prev,next;
    cin >> prev;
    for (int j=1; j < M; j++) {
        cin >> next;
        if (prev != next) {
            int k;
            for (k=0; k < prev.size() && k < next.size(); k++) {
                if (prev[k] != next[k]) {
                    int u = prev[k] - 'a';
                    int v = next[k] - 'a';
                    if (!edge[u][v]) {
                        edge[u][v] = true;
                        indeg[v]++;
                        ready[v]=false;
                    }
                    break;
                }
            }
            if (k == next.size())
                possible = false;   // prev is substring of next
                
        }
        prev = next;
    }


    string topo;
    if (possible) {
        //dump(N,ready,indeg);
        while (topo.size() != N) {
            int u = -1;
            for (int j=0; j < N; j++) {
                if (ready[j]) {
                    if (u != -1)
                        unique = false;
                    else
                        u = j;
                }
            }
            if (u == -1) {
                possible = false;
                break;
            } else if (!unique)
                break;
            else {
                topo += ('a'+u);
                ready[u] = false;
                for (int v=0; v < N; v++)
                    if (edge[u][v]) {
                        indeg[v]--;
                        if (indeg[v] == 0)
                            ready[v] = true;
                    }
            }
        }
    }

    if (!possible)
        cout << "IMPOSSIBLE" << endl;
    if (!unique)
        cout << "AMBIGUOUS" << endl;
    else
        cout << topo << endl;

}

