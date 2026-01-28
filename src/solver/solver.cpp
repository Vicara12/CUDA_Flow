#include  "solver.h"
#include <iostream>
#include <stdexcept>
#include <format>
#include <sstream>


Solver::Solver(
  Mesh mesh,
  float rho,
  float mu,
  float cell_size,
  float inlet_speed,
  float belt_speed
)
// Mesh borders are boundary conditions and thus do not count as width or height
: mesh_w_(mesh.size() - 2)
, mesh_h_(mesh[0].size() - 2)
, mesh_(std::move(mesh))
, rho_(rho)
, mu_(mu_)
, cell_size_(cell_size)
, inlet_speed_(inlet_speed)
, belt_speed_(belt_speed)
, u_  (MeshData(mesh_w_ + 1, RowData(mesh_h_)))
, u_p_(MeshData(mesh_w_ + 1, RowData(mesh_h_)))
, R_u_(MeshData(mesh_w_ + 1, RowData(mesh_h_)))
, v_  (MeshData(mesh_w_,     RowData(mesh_h_ + 1)))
, v_p_(MeshData(mesh_w_,     RowData(mesh_h_ + 1)))
, R_v_(MeshData(mesh_w_,     RowData(mesh_h_ + 1)))
, P_(MeshData(mesh_w_, RowData(mesh_h_, 0)))
{
  checkMeshOk();
  initializeVelocityFields();

  std::cout << "u:" << std::endl << formatMeshData(u_) << std::endl;
  std::cout << "v:" << std::endl << formatMeshData(v_) << std::endl;
  std::cout << "P:" << std::endl << formatMeshData(P_) << std::endl;
}


std::string Solver::formatMeshData(const MeshData& data) {
  std::stringstream ss;
  for (int y = data[0].size() - 1; y >= 0; y--) {
    for (int x = 0; x < data.size(); x++) ss << std::format("{:.2f} ", data[x][y]);
    ss << std::endl;
  }
  return ss.str();
}


void Solver::checkMeshOk() {
  auto boundaryError = [](size_t i, size_t j) {
    throw std::runtime_error(std::format("Border cell at position ({},{}) is fluid.", i, j));
  };

  if (mesh_w_ == 0) throw std::runtime_error("Mesh has width 0");
  if (mesh_h_ == 0) throw std::runtime_error("Mesh has height 0");

  size_t x_max = mesh_.size() - 1;
  size_t y_max = mesh_[0].size() -1;
  // Check there are no mesh borders of type fluid (borders fix the boundary conditions)
  for (size_t y = 0; y <= y_max; y++) {
    if (mesh_[0][y] == CellType::fluid) boundaryError(0, y);
    else if (mesh_[x_max][y] == CellType::fluid) boundaryError(x_max, y);
  }
  for (size_t x = 0; x <= x_max; x++) {
    if (mesh_[x][0] == CellType::fluid) boundaryError(x, 0);
    else if (mesh_[x][y_max] == CellType::fluid) boundaryError(x, y_max);
  }
}


float Solver::velocityThroughCellBorder(CellType type_a, CellType type_b) {
  // Belts and walls don't let fluid flow through
  if (type_a == CellType::belt or type_a == CellType::wall or
      type_b == CellType::belt or type_b == CellType::wall)
    return 0;
  if (type_a == CellType::inlet)
    return inlet_speed_;
  if (type_b == CellType::inlet)
    return -inlet_speed_;
  return 0;
}


void Solver::initializeVelocityFields() {
  for (size_t i = 0; i < u_.size(); i++)
    for (size_t j = 0; j < u_[0].size(); j++)
      u_[i][j] = velocityThroughCellBorder(mesh_[i][j + 1], mesh_[i + 1][j + 1]);

  for (size_t i = 0; i < v_.size(); i++)
    for (size_t j = 0; j < v_[0].size(); j++)
      v_[i][j] = velocityThroughCellBorder(mesh_[i + 1][j], mesh_[i + 1][j + 1]);
}