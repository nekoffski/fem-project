#pragma once

#include <stdexcept>

namespace fem {

struct Error : std::exception {
};

struct ConfigError : Error {
};
}