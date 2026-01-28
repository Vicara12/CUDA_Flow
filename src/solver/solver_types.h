#pragma once
#include <vector>


enum class CellType {
  fluid,  // Normal fluid cell
  wall,   // No fluid can cross this cell
  inlet,  // Fluid is injected at inlet_speed out of this cell
  outlet, // Fluid can cross this cell freely and exit the simulation
  belt    // Wall of constant speed perpendicular to the surface
};


using Mesh = std::vector<std::vector<CellType>>;

using RowData = std::vector<float>;
using MeshData = std::vector<RowData>;