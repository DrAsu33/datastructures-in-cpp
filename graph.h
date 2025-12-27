#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

const int INF = 0x30000000;
using PIS = std::pair<int, size_t>;   // pair(dist, nodeID)

class Graph
{
public:
    struct Edge
    {
        size_t to;
        int weight;
        Edge(size_t t, int w = 1) : to(t), weight(w) {}
    };

private:
    size_t vertexnum, edgenum;
    std::vector<std::vector<Edge>> adjacencylist;

public:
    Graph(size_t n) : vertexnum(n), edgenum(0) {adjacencylist.resize(n);}
    size_t v() const {return vertexnum;}
    size_t e() const {return edgenum;}

    void print();
    int len(size_t x, size_t y);
    void connect(size_t a, size_t b, int weight);
    const std::vector<Edge>& getneighbors(size_t i);
    std::vector<int> dijkstra_simple(size_t i);
    std::vector<int> dijkstra_optimized(size_t i);
};



void Graph::print()
{
    for(size_t i = 0; i < vertexnum; i++)
    {
        std::cout << "Point " << i << ": ";
        for(const auto& j : adjacencylist[i])
            std::cout << j.to << " ";
        std::cout << std::endl;
    }
}

int Graph::len(size_t x, size_t y)
{
    for(const auto& e : adjacencylist[x])
        if(e.to == y)
            return e.weight;
    return INF;
}

void Graph::connect(size_t a, size_t b, int weight = 1)
{
    adjacencylist[b].push_back(Edge(a, weight));
    adjacencylist[a].push_back(Edge(b, weight));
    edgenum++;
}

const std::vector<Graph::Edge>& Graph::getneighbors(size_t i)
{
    return adjacencylist[i];
}

std::vector<int> Graph::dijkstra_simple(size_t i)
{
    std::vector<int> dist(vertexnum, INF);  dist[i] = 0;
    std::vector<int> fixed(vertexnum, 0);  fixed[i] = 1;
    size_t prev = i;

    for(size_t j = 1; j < vertexnum; j++)
    {    
        for(const auto& e : adjacencylist[prev])
        {
            size_t dest = e.to; int len = e.weight;
            if(fixed[dest] == 0)
                dist[dest] = std::min(dist[dest], dist[prev] + len);
        }

        int index = -1, min = INF;
        for(size_t k = 0; k < vertexnum; k++)
        {
            if(fixed[k] == 0)
            {
                if(dist[k] < min)
                {
                    index = (int)k; min = dist[k];
                }
            }
        }
        if(index == -1)
            return dist;

        prev = (size_t)index; fixed[prev] = 1;
    }
    return dist;
}

std::vector<int> Graph::dijkstra_optimized(size_t i)
{
    std::vector<int> dist(vertexnum, INF);  dist[i] = 0;
    std::priority_queue<PIS, std::vector<PIS>, std::greater<PIS>> pq;

    pq.push(PIS(0, i));
    while(!pq.empty())
    {
        int minlen = pq.top().first;
        size_t start = pq.top().second;
        pq.pop();

        if(minlen > dist[start]) continue;

        for(const auto& edge : adjacencylist[start])
        {
            size_t end = edge.to; int len = edge.weight;
            if(len + minlen < dist[end])
            {
                dist[end] = len + minlen;
                pq.push(PIS(dist[end], end));
            }
        }
    }
    return dist;
}
