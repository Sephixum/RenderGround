#pragma once

#include <fmt/format.h>
#include <source_location>
#include <expected>

using EnsureResult = std::expected<void, std::string>;
using EnsureOk = EnsureResult;
using EnsureError = std::unexpected<std::string>;

template<typename... Ts>
[[nodiscard]]
constexpr auto
    ensure_true(bool predicate,
                fmt::format_string<Ts...> fmt_str,
                Ts &&...args,
                std::source_location source_loc = std::source_location::current()) noexcept
    -> EnsureResult {
    // TODO: Do not use excpetions
    // throw std::runtime_error{fmt::format("\nfile: {}\nfunction: {}\nline: {}\nmessage: {}",
    //                                      source_loc.file_name(),
    //                                      source_loc.function_name(),
    //                                      source_loc.line(),
    //                                      formatted_message)};
    // NOTE: done and changed to std::expected

    // NOTE: usage would be :
    // if (auto result = ensure_true(1>2)) {
    //		log("it aight !");
    // } else {
    // 		log_error(result.error());
    // 		std::exit(-1);
    // }
    //

    if(not predicate) {
        auto formatted_message = fmt::format(fmt_str, std::forward<Ts>(args)...);
        auto formatted_error = fmt::format("\nmessage: {}\nfile: {}\nfunction: {}\nline: {}\n",
                                           formatted_message,
                                           source_loc.file_name(),
                                           source_loc.function_name(),
                                           source_loc.line());
        return EnsureError{formatted_error};
    }

    return EnsureOk{};
}

[[nodiscard]]
constexpr auto
    ensure_true(bool predicate,
                std::source_location source_loc = std::source_location::current()) noexcept
    -> EnsureResult {
    // NOTE: Same as the above

    if(not predicate) {
        auto formatted_error = fmt::format("\nfile: {}\nfunction: {}\nline: {}",
                                           source_loc.file_name(),
                                           source_loc.function_name(),
                                           source_loc.line());
        return EnsureError{formatted_error};
    }

    return EnsureOk{};
}
