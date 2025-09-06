#pragma once

#include <fmt/format.h>
#include <source_location>

constexpr void ensure_true(bool predicate,
                           std::string_view msg,
                           std::source_location source_loc = std::source_location::current()) {
    if(not predicate) {
        // TODO: Do not use excpetions
        throw std::runtime_error{fmt::format("\nfile: {}\nfunction: {}\nline: {}\nmessage: {}",
                                             source_loc.file_name(),
                                             source_loc.function_name(),
                                             source_loc.line(),
                                             msg)};
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
