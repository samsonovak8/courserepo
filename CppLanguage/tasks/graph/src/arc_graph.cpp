#include "arc_graph.hpp"

ArcGraph::ArcGraph(size_t vCount_) : vCount(vCount_) {}

ArcGraph::ArcGraph(const IGraph* graph) : ArcGraph(graph->VerticesCount()) {
    std::vector<size_t> currEdges;
    for(size_t u = 0; u < vCount; ++u) {
        graph->GetNextVertices(u, currEdges);
        for(size_t v : currEdges) {
            edges.push_back({u, v});
        }
    }
}

void ArcGraph::AddEdge(size_t u, size_t v) {
    if (u < vCount && v < vCount) {
        edges.push_back({u, v});
    }
}

size_t ArcGraph::VerticesCount() const noexcept {
    return vCount;
}

void ArcGraph::GetNextVertices(size_t vertex, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(auto i : edges) {
        if (i.first == vertex) {
            vertices.push_back(i.second);
        }
    }
}

void ArcGraph::GetPrevVertices(size_t vertex, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(auto i : edges) {
        if (i.second == vertex) {
            vertices.push_back(i.first);
        }
    }
}