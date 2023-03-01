#pragma once
#include "igraph.hpp"
#include <set>

class SetGraph : public IGraph {
 public:
    SetGraph(size_t vCount_);
    SetGraph(const IGraph* graph);
    SetGraph(const IGraph& graph) = delete;

    void AddEdge(size_t from, size_t to);
    size_t VerticesCount() const noexcept;
    void GetNextVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept;
    void GetPrevVertices(size_t vertix, std::vector<size_t>& vertices) const noexcept;
 private:
    size_t vCount;
    std::vector<std::set<size_t> > edges;
};
