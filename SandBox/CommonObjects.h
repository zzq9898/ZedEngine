#include <vector>

namespace CommonObj{
    // layout
    // float3: position
    // float2: uv
    // float3: normal

    // GL_TRIANGLES drawElement
    void getQuadObj(std::vector<float> &vertices, std::vector<unsigned int> &indices);

    // GL_TRIANGLES drawElement
    void getCubeObj(std::vector<float> &vertices, std::vector<unsigned int> &indices);

    // GL_TRIANGLE_STRIP drawElement
    void getSphereObj(std::vector<float> &vertices, std::vector<unsigned int> &indices);
}