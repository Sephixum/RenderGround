#pragma once

#include <fmt/format.h>
#include <source_location>

#define constant static constexpr const auto
#define local_persist static
#define internal_function static
#define global_variable static

constexpr void
    _ensure_true_impl(bool predicate,
                      std::string_view msg,
                      std::source_location source_loc = std::source_location::current()) {
    if(not predicate) {
        throw std::runtime_error{fmt::format("\nfile: {}\nfunction: {}\nline: {}\nexpression: {}",
                                             source_loc.file_name(),
                                             source_loc.function_name(),
                                             source_loc.line(),
                                             msg)};
    }
}

#define ensure_true(expr) _ensure_true_impl(expr, #expr)
