#pragma once
#include "igraph.hpp"

class MatrixGraph : public IGraph {
 public:
    MatrixGraph(size_t vCount);
    MatrixGraph(const IGraph* graph);

    MatrixGraph(const IGraph& graph) = delete;

    void AddEdge(size_t from, size_t to);
    size_t VerticesCount() const noexcept;
    void GetNextVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept;
    void GetPrevVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept;
 private:
    size_t vCount;
    std::vector<std::vector<char> > matrix;
};