#pragma once
#include <set>
#include <unordered_map>
#include <vector>

class Graph {
 public:
  using Depth = int;
  using VertexId = int;
  using EdgeId = int;

  struct Vertex {
   public:
    explicit Vertex(VertexId id) : id_(id){};
    VertexId id() const { return id_; };

   private:
    VertexId id_ = 0;
  };

  struct Edge {
   public:
    enum class Color { Grey, Green, Yellow, Red };

    Edge(EdgeId id, VertexId from_vertex_id, VertexId to_vertex_id)
        : id_(id),
          from_vertex_id_(from_vertex_id),
          to_vertex_id_(to_vertex_id){};

    EdgeId id() const { return id_; };

    void set_edge_color(Edge::Color color) { color_ = color; }

    VertexId from_vertex_id() const { return from_vertex_id_; };

    VertexId to_vertex_id() const { return to_vertex_id_; };

    Edge::Color color() const { return color_; }

   private:
    EdgeId id_ = 0;
    VertexId from_vertex_id_ = 0;
    VertexId to_vertex_id_ = 0;
    Edge::Color color_ = Color::Grey;
  };

  VertexId add_vertex();

  EdgeId add_edge(VertexId first_vertex_id, VertexId second_vertex_id);

  const std::unordered_map<VertexId, Vertex>& vertices() const {
    return vertices_;
  };

  const std::unordered_map<EdgeId, Edge>& edges() const { return edges_; };

  const std::vector<EdgeId>& connected_edge_ids(VertexId vertex_id) const {
    return adjacency_list_.at(vertex_id);
  }

  Edge::Color get_edge_color(EdgeId from_vertex_id, EdgeId to_vertex_id) const;

  void set_edge_color(EdgeId edge_id, Edge::Color color) {
    edges_.at(edge_id).set_edge_color(color);
  }

  bool is_connected(VertexId from_vertex_id, VertexId to_vertex_id) const {
    const auto& children = children_of_vertex_.at(from_vertex_id);
    for (const auto child_id : children) {
      if (child_id == to_vertex_id) {
        return true;
      }
    }
    return false;
  }

  Depth get_vertex_depth(VertexId vertex_id) const {
    return depths_of_vertices_.at(vertex_id);
  }

  void set_vertex_depth(VertexId vertex_id, Depth new_depth) {
    depths_of_vertices_[vertex_id] = new_depth;
  }

  Depth depth() const { return vertices_with_depth_.size(); }

  const std::set<VertexId>& vertices_with_depth(Depth depth) const {
    return vertices_with_depth_.at(depth);
  }

  const std::set<VertexId>& children_of_vertex(VertexId vertex_id) const {
    return children_of_vertex_.at(vertex_id);
  }

 private:
  bool has_vertex(VertexId id) const {
    return vertices_.find(id) != vertices_.end();
  };

  VertexId get_new_vertex_id() { return last_vertex_id_++; };

  EdgeId get_new_edge_id() { return last_edge_id_++; };

  std::unordered_map<VertexId, std::set<VertexId>> children_of_vertex_;
  std::unordered_map<VertexId, Depth> depths_of_vertices_;
  std::unordered_map<Depth, std::set<VertexId>> vertices_with_depth_;
  std::unordered_map<VertexId, std::vector<EdgeId>> adjacency_list_;
  std::unordered_map<VertexId, Vertex> vertices_;
  std::unordered_map<EdgeId, Edge> edges_;
  VertexId last_vertex_id_ = 0;
  EdgeId last_edge_id_ = 0;
};
