#include <stdexcept>

namespace fem {

struct Error : std::exception {
};

struct GridError : Error {
};
}