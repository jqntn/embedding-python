#include <corecrt.h>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

static errno_t e = 0;

std::filesystem::path g_app_path;

static void
start_python()
{
  Py_Initialize();
}

static void
stop_python()
{
  e = Py_FinalizeEx();
  if (e) {
    std::printf("ABORT | Py_FinalizeEx | errno: %d", e);
    std::abort();
  }
}

static void
run_python_script(const std::filesystem::path& script_path)
{
  std::string script_path_str = script_path.generic_string();
  std::string script_stem = script_path.stem().string();

  FILE* p_file;
  e = fopen_s(&p_file, script_path_str.c_str(), "r");
  if (e) {
    std::printf("ABORT | fopen_s | %s | errno: %d", script_path_str.c_str(), e);
    std::abort();
  }

  e = PyRun_SimpleFileExFlags(p_file, script_stem.c_str(), 1, nullptr);
  if (e) {
    std::printf("ABORT | PyRun_SimpleFileExFlags | %s | errno: %d",
                script_path_str.c_str(),
                e);
    std::abort();
  }
}

int
main(int argc, char** argv)
{
  std::string script_name = "hello.py";

  std::filesystem::path exe_path = argv[0];
  g_app_path = exe_path.parent_path();
  std::filesystem::path script_path = g_app_path / script_name;

  start_python();
  // run_python_script(script_path);
  // run_python_script(R"(C:\Users\jqntn\embedding-python\cpython\hello-bpy.py)");
  run_python_script(
    R"(C:\Users\jqntn\embedding-python\cpython\hello-numpy.py)");
  stop_python();

  return EXIT_SUCCESS;
}