#pragma once 
#include "igraph.hpp"

class ArcGraph : public IGraph {
 public:
    ArcGraph(size_t vCount_);
    ArcGraph(const IGraph* graph);
    ArcGraph(const IGraph& graph) = delete;

    void AddEdge(size_t from, size_t to);

    size_t VerticesCount() const noexcept;

    void GetNextVertices(size_t vertex, std::vector<size_t>& vertices) const noexcept;
    void GetPrevVertices(size_t vertex, std::vector<size_t>& vertices) const noexcept;

 private:
    const size_t vCount;
    std::vector<std::pair<size_t, size_t> > edges;
};