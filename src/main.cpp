#include <iostream>
#include "solver/solver_types.h"
#include "solver/solver.h"

int main (int argc, char **argv) {
  Mesh sample_mesh = {
    {CellType::belt, CellType::belt, CellType::belt, CellType::belt, CellType::belt},
    {CellType::inlet, CellType::fluid, CellType::fluid, CellType::fluid, CellType::outlet},
    {CellType::inlet, CellType::fluid, CellType::fluid, CellType::fluid, CellType::outlet},
    {CellType::wall, CellType::wall, CellType::wall, CellType::wall, CellType::wall}
  };

  Solver(
    Solver::transposeMesh(sample_mesh),
    1, // rho
    1, // mu
    1, // cell_size
    5, // inlet_speed
    2  // belt_speed
  );

  return 0;
}