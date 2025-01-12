#include <cstdlib>
#include <exception>
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

int
main()
{
  py::scoped_interpreter guard;

  try {
    py::exec(R"(
      import numpy as np
      print(np.arange(15).reshape(3, 5))
    )");
    py::exec(R"(
      import bpy
      bpy.ops.object.select_all(action="DESELECT")
    )");
  } catch (const std::exception& e) {
    std::cout << e.what();
    throw;
  }

  return EXIT_SUCCESS;
}