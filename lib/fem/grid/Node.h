#pragma once

namespace fem::grid {

struct Node {
    int x;
    int y;
    int temp;
    bool boundaryCase;
};
}