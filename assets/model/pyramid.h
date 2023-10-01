#pragma once
#include <vector>

const std::vector<float> pyramid = {
        // front
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // 0 (Red)
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 1 (Blue)
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 2 (Green)

        // right
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 1 (Red)
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 3 (Blue)
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 2 (Green)

        // back
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 3 (Red)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 4 (Blue)
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 2 (Green)

        // left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 4 (Blue)
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // 0 (Red)
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 2 (Green)

        // bottom
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // 0 (Red)
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // 1 (White)
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 3 (Green)

        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // 0 (Red)
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 3 (Green)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f // 4 (Blue)
};
