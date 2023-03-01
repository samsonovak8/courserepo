#include "list_graph.hpp"

ListGraph::ListGraph(size_t vCount_) : vCount(vCount_), edges(std::vector<std::vector<size_t> > (vCount)) {}

ListGraph::ListGraph(const IGraph* graph) : ListGraph(graph->VerticesCount()) {
    std::vector<size_t> vertices;
    for(size_t from = 0; from < vCount; ++from) {
        graph->GetNextVertices(from, vertices);
        for(size_t to : vertices) {
            edges[from].push_back(to);
        }
    }
}

void ListGraph::AddEdge(size_t from, size_t to) {
    if (from < vCount && to < vCount) {
        edges[from].push_back(to);
    }
}

size_t ListGraph::VerticesCount() const noexcept {
    return vCount;
}

void ListGraph::GetNextVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(auto next : edges[vertix]) {
        vertices.push_back(next);
    }
}

void ListGraph::GetPrevVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(size_t prev = 0; prev < vCount; ++prev) {
        for(size_t cur : edges[prev]) {
            if (cur == vertix) {
                vertices.push_back(prev);
                break;
            }
        }
    }
}
