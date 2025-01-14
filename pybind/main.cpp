#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

std::filesystem::path g_app_path;

int
main(int argc, char** argv)
{
  g_app_path = std::filesystem::path(argv[0]).parent_path();

  py::scoped_interpreter guard;

  if (!std::filesystem::exists(g_app_path / "Lib/site-packages/")) {
    try {
      py::exec(R"(
import urllib.request
exec(urllib.request.urlopen("https://bootstrap.pypa.io/get-pip.py").read())
      )");
    } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }

  /*
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
  */

  return EXIT_SUCCESS;
}