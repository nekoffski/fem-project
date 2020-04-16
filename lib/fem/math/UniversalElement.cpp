#include <fem/math/UniversalElement.h>

#include <functional>
#include <vector>

namespace fem::math {

inline float N1(float ksi, float eta) {
    return 0.25f * (1.0f - ksi) * (1.0f - eta);
}

inline float N2(float ksi, float eta) {
    return 0.25f * (1.0f + ksi) * (1.0f - eta);
}

inline float N3(float ksi, float eta) {
    return 0.25f * (1.0f + ksi) * (1.0f + eta);
}

inline float N4(float ksi, float eta) {
    return 0.25f * (1.0f - ksi) * (1.0f + eta);
}

inline float dN1_dksi(float eta) {
    return -0.25 * (1.0f - eta);
}

inline float dN2_dksi(float eta) {
    return 0.25 * (1.0f - eta);
}

inline float dN3_dksi(float eta) {
    return 0.25 * (1.0f + eta);
}

inline float dN4_dksi(float eta) {
    return -0.25 * (1.0f + eta);
}

inline float dN1_deta(float ksi) {
    return -0.25 * (1.0f - ksi);
}

inline float dN2_deta(float ksi) {
    return -0.25 * (1.0f + ksi);
}

inline float dN3_deta(float ksi) {
    return 0.25 * (1.0f + ksi);
}

inline float dN4_deta(float ksi) {
    return 0.25 * (1.0f - ksi);
}

inline std::vector<fem::math::Point> localPoints{
    { -1.0f / fem::math::SQRT3, -1.0f / fem::math::SQRT3 }, // p1
    { 1.0f / fem::math::SQRT3, -1.0f / fem::math::SQRT3 }, // p2
    { 1.0f / fem::math::SQRT3, 1.0f / fem::math::SQRT3 }, // p3
    { -1.0f / fem::math::SQRT3, 1.0f / fem::math::SQRT3 } // p4
};

inline std::vector<std::function<float(float)>> dksis{
    dN1_dksi, dN2_dksi, dN3_dksi, dN4_dksi
};

inline std::vector<std::function<float(float)>> detas{
    dN1_deta, dN2_deta, dN3_deta, dN4_deta
};

inline std::vector<std::function<float(float, float)>> shapes{
    N1, N2, N3, N4
};

UniversalElement::UniversalElement() {
    for (int i = 0; i < 4; ++i) {
        const auto& p = localPoints[i];
        for (int j = 0; j < 4; ++j)
            dksi[i][j] = dksis[j](p.y);
        for (int j = 0; j < 4; ++j)
            deta[i][j] = detas[j](p.x);
        for (int j = 0; j < 4; ++j)
            shapeFunctions[i][j] = shapes[j](p.x, p.y);
    }
}
}
