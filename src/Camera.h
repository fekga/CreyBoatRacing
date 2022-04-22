#pragma once

// from LearnOpenGL tutorial

#include <glm/glm.hpp>

// An abstract camera class that processes input and calculates 
// the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 1000.0f;
    const float FOV = 45.0f;
    const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Target;
    // camera options
    float AspectRatio = 1.0f;

    // constructor with vectors
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
        :
        Position(position)
    {}

    glm::mat4 GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(FOV), AspectRatio, NEAR_PLANE, FAR_PLANE);
    }

    glm::mat4 GetViewMatrix(bool useTarget = false) const
    {
        return glm::lookAt(Position, Target, WORLD_UP);
    }
};