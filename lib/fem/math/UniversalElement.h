#pragma once

#include <fem/math/Utils.hpp>

namespace fem::math {

struct UniversalElement {
    UniversalElement();

    Mat4 dksi;
    Mat4 deta;
    Mat4 shapeFunctions;
    Mat8x4 boundaryShapeFunctions;
};
}
