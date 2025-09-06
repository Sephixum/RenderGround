#pragma once

#include <fmt/format.h>
#include <source_location>

template<typename... Ts>
constexpr void ensure_true(bool predicate,
                           fmt::format_string<Ts...> fmt_str,
                           Ts &&...args,
                           std::source_location source_loc = std::source_location::current()) {
    if(not predicate) {
        // TODO: Do not use excpetions
        auto formatted_message = fmt::format(fmt_str, std::forward<Ts>(args)...);
        throw std::runtime_error{fmt::format("\nfile: {}\nfunction: {}\nline: {}\nmessage: {}",
                                             source_loc.file_name(),
                                             source_loc.function_name(),
                                             source_loc.line(),
                                             formatted_message)};
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
