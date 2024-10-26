/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

using namespace std::literals;

namespace py = pybind11;

// === CONSTANTS ===

namespace {
auto const MODULE_DOC = R"pbdoc(
Pybind11 example plugin
-----------------------

.. currentmodule:: playground

.. autosummary::
:toctree: _generate

add
subtract
)pbdoc";

}  // namespace

// === HELPERS ===

namespace {
int add(int i, int j) {
  return i + j;
}

auto const ADD_DOC = R"pbdoc(
Add two numbers

Some other explanation about the add function.
                          )pbdoc";
}  // namespace

// === IMPLEMENTATION ===

PYBIND11_MODULE(playground, m) {
  m.doc() = MODULE_DOC;

  m.def("add", &add, ADD_DOC);

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
