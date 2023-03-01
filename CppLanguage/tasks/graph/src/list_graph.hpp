#pragma once
#include "igraph.hpp"

class ListGraph : public IGraph {
 public:
    ListGraph(size_t vCount_);
    ListGraph(const IGraph* graph);
    ListGraph(const IGraph& graph) = delete;

    void AddEdge(size_t from, size_t to);
    size_t VerticesCount() const noexcept;
    void GetNextVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept;
    void GetPrevVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept;

 private:
    size_t vCount;
    std::vector<std::vector<size_t> > edges;
};