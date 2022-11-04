#include <fstream>
#include <iostream>

#include "config.hpp"
#include "graph.hpp"
#include "graph_generator.hpp"
#include "graph_json_printing.hpp"
#include "graph_printing.hpp"
#include "logger.hpp"

namespace {
void write_to_file(const std::string& graph_json,
                   const std::string& file_name) {
  std::ofstream json_file(file_name);

  json_file << graph_json;
}

int handle_depth_input() {
  const std::string init_message = "Type graph depth: ";
  const std::string err_format_message =
      "The depth must be a non-negative integer. Try again";

  int depth;
  int correct_input = false;

  std::cout << init_message << std::endl;

  while (correct_input == false) {
    if (std::cin >> depth && depth >= 0) {
      correct_input = true;
    } else if (std::cin.fail() || depth < 0) {
      std::cout << err_format_message << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      throw std::runtime_error("Failed to get depth from user");
    }
  }

  return depth;
}

int handle_new_vertices_count_input() {
  const std::string init_message = "Type new vertices count: ";
  const std::string err_format_message =
      "Vertices count must be a non-negative integer. Try again";
  int new_vertices_count;
  int correct_input = false;

  std::cout << init_message << std::endl;

  while (correct_input == false) {
    if (std::cin >> new_vertices_count && new_vertices_count >= 0) {
      correct_input = true;
    } else if (std::cin.fail() || new_vertices_count < 0) {
      std::cout << err_format_message << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      throw std::runtime_error("Failed to get new vertices count from user");
    }
  }

  return new_vertices_count;
}

int handle_graphs_count_input() {
  const std::string init_message = "Type new grpahs count: ";
  const std::string err_format_message =
      "Graphs count must be a non-negative integer. Try again";
  int graphs_count;
  int correct_input = false;

  std::cout << init_message << std::endl;

  while (correct_input == false) {
    if (std::cin >> graphs_count && graphs_count >= 0) {
      correct_input = true;
    } else if (std::cin.fail() || graphs_count < 0) {
      std::cout << err_format_message << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      throw std::runtime_error("Failed to get new graphs count from user");
    }
  }

  return graphs_count;
}

std::string generation_started_string(int graph_number) {
  return "Graph " + std::to_string(graph_number) + ", Generation Started";
}

std::string generation_finished_string(int graph_number,
                                       const std::string& graph_description) {
  return "Graph " + std::to_string(graph_number) + ", Generation Finished " +
         graph_description;
}
}  // namespace

int main() {
  using namespace uni_course_cpp;

  const int depth = handle_depth_input();
  const int new_vertices_count = handle_new_vertices_count_input();
  const int graphs_count = handle_graphs_count_input();

  auto params = GraphGenerator::Params(depth, new_vertices_count);

  const auto generator = GraphGenerator(std::move(params));
  auto& logger = Logger::get_logger();

  for (int i = 0; i < graphs_count; i++) {
    logger.log(generation_started_string(i));
    const auto graph = generator.generate();

    logger.log(generation_finished_string(i, "Empty graph description"));

    const auto graph_json = printing::json::print_graph(graph);

    const std::string graph_json_file_name =
        "graph_" + std::to_string(i) + ".json";
    const std::string graph_json_file_path =
        config::kTempDirectoryPath + graph_json_file_name;
    write_to_file(graph_json, graph_json_file_path);
  }

  return 0;
}
