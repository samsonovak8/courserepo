#include "matrix_graph.hpp" 

MatrixGraph::MatrixGraph(size_t vCount_) : vCount(vCount_), matrix(std::vector<std::vector<char> > (vCount, std::vector<char> (vCount, 0))) {}

MatrixGraph::MatrixGraph(const IGraph* graph) : MatrixGraph(graph->VerticesCount()){
    std::vector<size_t> vertices;
    for(size_t from = 0; from < vCount; ++from) {
        graph->GetNextVertices(from, vertices);
        for(size_t to : vertices) {
            matrix[from][to] = 1;
        }
    }
}

void MatrixGraph::AddEdge(size_t from, size_t to) {
    if (from < vCount && to < vCount) {
        matrix[from][to] = 1;
    }
}

size_t MatrixGraph::VerticesCount() const noexcept {
    return vCount;
}

void MatrixGraph::GetNextVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(size_t next = 0; next < vCount; ++next) {
        if (matrix[vertix][next]) {
            vertices.push_back(next);
        }
    }
}
void MatrixGraph::GetPrevVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept {
    vertices.clear();
    for(size_t prev = 0; prev < vCount; ++prev) {
        if (matrix[prev][vertix]) {
            vertices.push_back(prev);
        }
    }
}