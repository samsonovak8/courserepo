#include "set_graph.hpp"

SetGraph::SetGraph(size_t vCount_) : vCount(vCount_), edges(std::vector<std::set<size_t> > (vCount)) {}

SetGraph::SetGraph(const IGraph* graph) : SetGraph(graph->VerticesCount()) {
    std::vector<size_t> vertices;
    for(size_t from = 0; from < vCount; ++from) {
        graph->GetNextVertices(from, vertices);
        for(auto to : vertices) {
            edges[from].insert(to);
        }
    }
}
void SetGraph::AddEdge(size_t from, size_t to) {
    if (from < vCount && to < vCount) {
        edges[from].insert(to);
    }
}

size_t SetGraph::VerticesCount() const noexcept {
    return vCount;
}

void SetGraph::GetNextVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(auto next : edges[vertix]) {
        vertices.push_back(next);
    }
}

void SetGraph::GetPrevVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(size_t prev = 0; prev < vCount; ++prev) {
        for(auto cur : edges[prev]) {
            if (cur == vertix) {
                vertices.push_back(prev);
            }
        }
    }
}