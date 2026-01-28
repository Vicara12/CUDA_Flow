#include <iostream>
#include "solver/solver_types.h"
#include "solver/solver.h"

int main (int argc, char **argv) {
  Mesh sample_mesh = {
    {CellType::wall, CellType::inlet, CellType::inlet, CellType::belt},
    {CellType::wall, CellType::fluid, CellType::fluid, CellType::inlet},
    {CellType::wall, CellType::fluid, CellType::fluid, CellType::belt},
    {CellType::wall, CellType::outlet, CellType::outlet, CellType::belt}
  };

  Solver(
    sample_mesh,
    1, // rho
    1, // mu
    1, // cell_size
    5, // inlet_speed
    2  // belt_speed
  );

  return 0;
}