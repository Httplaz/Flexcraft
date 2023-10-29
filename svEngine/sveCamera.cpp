#include "pch.h"

sveCamera::sveCamera() : rotationMatrix(1.0f) {}

void sveCamera::translateRelative(const glm::vec3& translation) {
    glm::vec4 f = glm::vec4(translation * 0.000004f, 1.f) * rotationMatrix;
    position += glm::vec3{ f.x, f.y, f.z };
}

void sveCamera::translateRaw(const glm::vec3& translation) {
    position += translation * 0.000001f;
}

void sveCamera::rotateRelative(const glm::vec3& axis, float angle)
{
    rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
}

void sveCamera::rotate(const glm::vec3& axis, float angle)
{
    glm::mat4 worldSpaceRotation = glm::rotate(glm::mat4(1.0f), angle, axis);
    rotationMatrix = worldSpaceRotation * rotationMatrix;
}


const glm::mat4& sveCamera::getViewMatrix() const {
    return glm::translate(rotationMatrix, position);
}
