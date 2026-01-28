#pragma once

#include <string>
#include "solver_types.h"


class Solver {
  int mesh_w_, mesh_h_;
  Mesh mesh_;

  float rho_, mu_, cell_size_, inlet_speed_, belt_speed_;
  MeshData u_, u_p_, R_u_; // Horizontal fluid speeds
  MeshData v_, v_p_, R_v_; // Vertical fluid speeds
  MeshData P_;             // Fluid pressure

  void initializeVelocityFields();

  void checkMeshOk();

  float velocityThroughCellBorder(CellType type_a, CellType type_b);

  std::string formatMeshData(const MeshData& data);

public:

  Solver(
    Mesh mesh,
    /* Fluid parameters */
    float rho,
    float mu,
    float cell_size,

    /* Parameters for special cells (change only if that cell type is used) */
    float inlet_speed = 0,
    float belt_speed = 0
  );

  static Mesh transposeMesh(const Mesh &mesh);
};