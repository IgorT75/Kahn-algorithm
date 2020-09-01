#include <stdio.h>
#include <queue>
#include <vector>
#include <map>

using namespace std;

void printVec(const vector<int>& v) {
  printf("%zu: ", v.size());
  for (int i : v)
    printf("%d, ", i);
  printf("\n");
}

vector<int> topologicalSort(const vector<vector<int>>& graph) {
  // find initial vertices with outgoings only (i.e. no incomings)
  map<int, int> insMap; // vertex to # of incomings map
  for(size_t i = 0, n = graph.size(); i < n; ++i)
    insMap[i] = 0;

  for (size_t vi = 0, gSz = graph.size(); vi < gSz; ++vi) {
    const auto& v = graph[vi];
    for(size_t i = 0, n = v.size(); i < n; ++i) {
      ++insMap[v[i]];
    }
  }
  
  // push to the queue
  queue<int> q;
  for (size_t i = 0, n = insMap.size(); i < n; ++i)
    if (insMap[i] == 0) q.push(i);

  vector<int> res;
  while (!q.empty()) {
    int currVert = q.front();
    q.pop();
    res.push_back(currVert);
    for (int adjVert : graph[currVert]) {
      if (--insMap[adjVert] == 0) {
        q.push(adjVert);
        insMap.erase(adjVert);
      }
    }
  }

  return res;
}

int main() {
/* 0→→→→1←←←←←←←←←←←3
   ↑    ↓ ⬉      ⬈ ↓ ⬊ 
   ↑    ↓   ⬉  ⬈   ↓   ⬊
   ↑    ↓     2     ↓    4
   ↑    ↓  ⬋        ↓  ⬈
   ↑    ↓⬋          ↓⬈
   7→→→→6→→→→→→→→→→→5 */
  vector<vector<int>> graph {
    { 1 },
    { 6 },
    { 1, 3, 6 },
    { 1, 4, 5 },
    {  },
    { 4 },
    { 5 },
    { 0, 6 },
  };

  auto topoSort = topologicalSort(graph);
  printVec(topoSort);

  return 0;
}
