#include "CommonObjects.h"
#include <vector>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

void CommonObj::getQuadObj(std::vector<float> &vertices, std::vector<unsigned int> &indices){
    vertices = {
        // pos            //tex      //normal
        -1.0f, -1.0, 0.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0, 0.0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    indices = {
        0, 1, 2,
        1, 3, 2
    };
}

void CommonObj::getCubeObj(std::vector<float> &vertices, std::vector<unsigned int> &indices){
    vertices = {
        // pos              //tex      //normal
        -0.5, -0.5, -0.5,    0.0, 0.0,     -1.0, 0.0, 0.0, 
        -0.5, -0.5,  0.5,    0.0, 1.0,     -1.0, 0.0, 0.0,
        -0.5,  0.5,  0.5,    1.0, 1.0,     -1.0, 0.0, 0.0,
        -0.5,  0.5, -0.5,    1.0, 0.0,     -1.0, 0.0, 0.0,

        0.5, -0.5, -0.5,     0.0, 0.0,      1.0, 0.0, 0.0,
        0.5, -0.5,  0.5,     0.0, 1.0,      1.0, 0.0, 0.0,
        0.5,  0.5,  0.5,     1.0, 1.0,      1.0, 0.0, 0.0,
        0.5,  0.5, -0.5,     1.0, 0.0,      1.0, 0.0, 0.0,

        -0.5, -0.5, -0.5,    0.0, 0.0,      0.0,-1.0, 0.0,
        0.5, -0.5, -0.5,     1.0, 0.0,      0.0,-1.0, 0.0,
        0.5, -0.5,  0.5,     1.0, 1.0,      0.0,-1.0, 0.0,
        -0.5, -0.5,  0.5,    0.0, 1.0,      0.0,-1.0, 0.0,

        -0.5,  0.5, -0.5,    0.0, 0.0,      0.0, 1.0, 0.0,
        0.5,  0.5, -0.5,     1.0, 0.0,      0.0, 1.0, 0.0,
        0.5,  0.5,  0.5,     1.0, 1.0,      0.0, 1.0, 0.0,
        -0.5,  0.5,  0.5,    0.0, 1.0,      0.0, 1.0, 0.0,

        -0.5, -0.5, -0.5,    0.0, 1.0,      0.0, 0.0,-1.0,
        0.5, -0.5, -0.5,     1.0, 1.0,      0.0, 0.0,-1.0,
        0.5,  0.5, -0.5,     1.0, 0.0,      0.0, 0.0,-1.0,
        -0.5,  0.5, -0.5,    0.0, 0.0,      0.0, 0.0,-1.0,

        -0.5, -0.5,  0.5,    0.0, 1.0,      0.0, 0.0, 1.0,
        0.5, -0.5,  0.5,     1.0, 1.0,      0.0, 0.0, 1.0,
        0.5,  0.5,  0.5,     1.0, 0.0,      0.0, 0.0, 1.0,
        -0.5,  0.5,  0.5,    0.0, 0.0,      0.0, 0.0, 1.0
    };

    indices = {
        0, 1, 2,    2, 3, 0,
        4, 5, 6,    6, 7, 4,
        8, 9,10,   10,11, 8, 
        12,13,14,  14,15,12,
        16,17,18,  18,19,16,
        20,21,22,  22,23,20
    };
}


void CommonObj::getSphereObj(std::vector<float> &vertices, std::vector<unsigned int> &indices){
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        //std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359f;
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }

        std::vector<float> &data = vertices;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }
}