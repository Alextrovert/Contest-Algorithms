/*

1.5.3 - Maximum Flow (Push-Relabel Algorithm)

Description: Given a flow network, find a flow from a single
source node to a single sink node that is maximized. The push-
relabel algorithm is considered one of the most efficient
maximum flow algorithms. However, unlike the Ford-Fulkerson or
Edmonds-Karp algorithms, it cannot take advantage of the fact
if max flow itself has a small magnitude.

Complexity: O(V^3) on the number of vertices.

=~=~=~=~= Sample Input =~=~=~=~=
6 8
0 1 3
0 2 3
1 2 2
1 3 3
2 4 2
3 4 1
3 5 2
4 5 3
0 5

=~=~=~=~= Sample Output =~=~=~=~=
5

*/

#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 100, INF = 0x3F3F3F3F;
int nodes, edges, source, sink;
int cap[MAXN][MAXN], f[MAXN][MAXN];
int h[MAXN], maxh[MAXN], e[MAXN];

int push_relabel() {
  h[source] = nodes - 1;
  for (int i = 0; i < nodes; i++) {
    f[source][i] = cap[source][i];
    f[i][source] = -f[source][i];
    e[i] = cap[source][i];
  }
  int sz = 0;
  for (;;) {
    if (sz == 0) {
      for (int i = 0; i < nodes; i++)
        if (i != source && i != sink && e[i] > 0) {
          if (sz != 0 && h[i] > h[maxh[0]]) sz = 0;
          maxh[sz++] = i;
        }
    }
    if (sz == 0) break;
    while (sz != 0) {
      int i = maxh[sz - 1];
      bool pushed = false;
      for (int j = 0; j < nodes && e[i] != 0; j++) {
        if (h[i] == h[j] + 1 && cap[i][j] - f[i][j] > 0) {
          int df = min(cap[i][j] - f[i][j], e[i]);
          f[i][j] += df;
          f[j][i] -= df;
          e[i] -= df;
          e[j] += df;
          if (e[i] == 0) sz--;
          pushed = true;
        }
      }
      if (!pushed) {
        h[i] = INF;
        for (int j = 0; j < nodes; j++)
          if (h[i] > h[j] + 1 && cap[i][j] - f[i][j] > 0)
            h[i] = h[j] + 1;
        if (h[i] > h[maxh[0]]) {
          sz = 0;
          break;
        }
      }
    }
  }
  int flow = 0;
  for (int i = 0; i < nodes; i++) flow += f[source][i];
  return flow;
}
 
int main() {
  int edges, a, b, capacity;
  cin >> nodes >> edges;
  for (int i = 0; i < edges; i++) {
    cin >> a >> b >> capacity;
    cap[a][b] = capacity;
  }
  cin >> source >> sink;
  cout << push_relabel() << "\n";
  return 0;
}
