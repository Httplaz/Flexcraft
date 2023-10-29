#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class sveCamera {
public:
    sveCamera();
    void translateRelative(const glm::vec3& translation);
    void translateRaw(const glm::vec3& translation);

    void rotateRelative(const glm::vec3& axis, float angle);
    void rotate(const glm::vec3& axis, float angle);

    const glm::mat4& getViewMatrix() const;

private:
    glm::mat4 rotationMatrix;
    glm::vec3 position;
};