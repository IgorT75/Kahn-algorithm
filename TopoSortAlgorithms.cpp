#include <stdio.h>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <exception>

using namespace std;

void printVec(const vector<size_t>& v) {
  printf("%zu: ", v.size());
  for (size_t i : v)
    printf("%zu, ", i);
  printf("\n");
}

vector<size_t> topologicalSortKahn(const vector<vector<size_t>>& graph) {
  // find initial vertices with outgoings only (i.e. no incomings)
  map<size_t, size_t> insMap; // vertex to # of incomings map
  for(size_t i = 0, n = graph.size(); i < n; ++i)
    insMap[i] = 0;

  for (size_t vi = 0, gSz = graph.size(); vi < gSz; ++vi) {
    const auto& v = graph[vi];
    for(size_t i = 0, n = v.size(); i < n; ++i) {
      ++insMap[v[i]];
    }
  }
  
  // push to the queue
  queue<size_t> q;
  for (size_t i = 0, n = insMap.size(); i < n; ++i)
    if (insMap[i] == 0) q.push(i);

  vector<size_t> res;
  while (!q.empty()) {
    size_t currVert = q.front();
    q.pop();
    res.push_back(currVert);
    for (size_t adjVert : graph[currVert]) {
      if (--insMap[adjVert] == 0) {
        q.push(adjVert);
        insMap.erase(adjVert);
      }
    }
  }

  return res;
}

class TopoSortDfs {
  vector<vector<size_t>> _graph;
  mutable vector<bool> _visited;
  mutable stack<size_t> _stack;
  public:
    TopoSortDfs(const vector<vector<size_t>>& graph) : 
      _graph(graph), _stack(stack<size_t>()), _visited(graph.size(), false) { }

    void dfs(size_t vertex) const {
      if (vertex >= _graph.size())
        throw bad_exception();
      
      _visited[vertex] = true;
      for (size_t i = 0, n = _graph[vertex].size(); i < n; ++i) {
        size_t adjVert = _graph[vertex][i];
        if (!_visited[adjVert])
          dfs(adjVert);
      }
      //printf("Pushing: %zu\n", vertex);
      _stack.push(vertex);
    }

    vector<size_t> topologicalSortDfs() {
      
      for (size_t i = 0, n = _graph.size(); i < n; ++i) {
        if (!_visited[i])
          dfs(i);
      }

      vector<size_t> v;
      while (!_stack.empty()) {
        v.push_back(_stack.top());
        _stack.pop();
      }
      return v;
    }
};

int main() {
/* 0→→→→1←←←←←←←←←←←3
   ↑    ↓ ⬉      ⬈ ↓ ⬊
   ↑    ↓   ⬉  ⬈   ↓   ⬊
   ↑    ↓     2     ↓    4
   ↑    ↓  ⬋        ↓  ⬈
   ↑    ↓⬋          ↓⬈
   7→→→→6→→→→→→→→→→→5*/
  vector<vector<size_t>> graph {
    { 1 },
    { 6 },
    { 1, 3, 6 },
    { 1, 4, 5 },
    {  },
    { 4 },
    { 5 },
    { 6 },
  };

  auto topoSort1 = topologicalSortKahn(graph);
  printf("Kahn's algorithm:\n");
  printVec(topoSort1);
  printf("\n");

  TopoSortDfs ts(graph);
  auto topoSort2 = ts.topologicalSortDfs();
  printf("DFS-based algorithm:\n");
  printVec(topoSort2);

  return 0;
}
