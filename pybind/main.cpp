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
    py::module_ numpy = py::module_::import("numpy");
  } catch (const std::exception& e) {
    std::cout << e.what();
    throw;
  }

  return EXIT_SUCCESS;
}