#include <cstdlib>
#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

std::filesystem::path g_app_path;

int
main(int argc, char** argv)
{
  g_app_path = std::filesystem::path(argv[0]).parent_path();

  if (!std::filesystem::exists(g_app_path / "Lib/site-packages/")) {
    {
      py::scoped_interpreter guard;
      try {
        py::exec(
          R"(
import urllib.request
exec(urllib.request.urlopen("https://bootstrap.pypa.io/get-pip.py").read())
          )");
      } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
      }
    }
    {
      py::scoped_interpreter guard;
      try {
        py::exec(std::format(
          R"(
import pip
pip.main(["install", "-r", "{}"])
          )",
          (g_app_path / "requirements.txt").generic_string()));
      } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
      }
    }
    std::filesystem::remove_all(g_app_path / "Scripts/");
  }

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
    std::cout << e.what() << '\n';
  }

  return EXIT_SUCCESS;
}