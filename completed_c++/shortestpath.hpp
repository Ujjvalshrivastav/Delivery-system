#include<vector>
#include<queue>
#include<limits>

struct Waypoint{
    std::string name;
    double latitude;
    double longitude;
};

struct Edge{
    int to;
    double distance;
};

std::vector<int>dijkstra(int start, int end, const std::vector<std::vector<Edge>>& graph){
    int n = graph.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());

    std::vector<int> prev(n, -1);
    dist[start] = 0;

    using PII = std::pair<double, int>;
    std::priority_queue<PII, std::vector<std::pair<double, int>>, std::greater<PII>> pq;

    pq.push({0, start});

    while(!pq.empty()){
        double currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(u == end)    break;

        if(currentDist > dist[u])   continue;

        for(const Edge& edge: graph[u]){
            int v = edge.to;
            double weight = edge.distance;

            if(dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> path;
    for(int at = end; at != -1; at = prev[at])
        path.push_back(at);

    std::reverse(path.begin(), path.end());

    return path;
}
