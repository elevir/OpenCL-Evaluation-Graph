#pragma once

#include <tuple>

inline constexpr std::pair<const char *, const char *> ADD = {
#include "open_cl_kernels/add.cl"
, "add"
};

inline constexpr std::pair<const char *, const char *> ELEM_WISE_MULT = {
#include "open_cl_kernels/multiply_element_wise.cl"
, "multiply_element_wise"
};

inline constexpr std::pair<const char *, const char *> ELEM_WISE_DIV = {
#include "open_cl_kernels/div_element_wise.cl"
    , "div_element_wise"
};

inline constexpr std::pair<const char *, const char *> ABS = {
#include "open_cl_kernels/abs.cl"
    , "abs_func"
};

inline constexpr std::pair<const char *, const char *> SQRT = {
#include "open_cl_kernels/sqrt.cl"
    , "sqrt_func"
};

inline constexpr std::pair<const char *, const char *> UNARY_MINUS = {
#include "open_cl_kernels/unary_minus.cl"
    , "unary_minus"
};