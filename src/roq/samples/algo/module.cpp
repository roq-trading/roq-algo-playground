/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include <pybind11/pybind11.h>

#include "roq/algo/reporter.hpp"

#include "roq/utils/common.hpp"

#include "roq/python/utils/convert.hpp"

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

std::unique_ptr<roq::algo::Reporter> create_my_reporter() {
  return {};
};
}  // namespace

// === IMPLEMENTATION ===

PYBIND11_MODULE(ROQ_PACKAGE_NAME, m) {
  m.doc() = MODULE_DOC;

  m.def("add", &add, ADD_DOC);

  m.def("create_my_reporter", &create_my_reporter);

  m.def("foo", [](roq::Side side) { return roq::utils::invert(side); });

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif

  auto m2 = py::module::import("roq");
}
