#pragma once

#include <fmt/format.h>
#include <source_location>

constexpr void ensure_true(bool predicate,
                           std::string_view message,
                           std::source_location source_loc = std::source_location::current()) {
    if(not predicate) {
        throw std::runtime_error{fmt::format("\nfile: {}\nfunction: {}\nline: {}\nmessage: {}",
                                             source_loc.file_name(),
                                             source_loc.function_name(),
                                             source_loc.line(),
                                             message)};
    }
}

constexpr void ensure_true(bool predicate,
                           std::source_location source_loc = std::source_location::current()) {
    if(not predicate) {
        throw std::runtime_error{fmt::format("\nfile: {}\nfunction: {}\nline: {}",
                                             source_loc.file_name(),
                                             source_loc.function_name(),
                                             source_loc.line())};
    }
}
