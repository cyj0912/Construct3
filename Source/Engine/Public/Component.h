#pragma once
#include <Core.h>
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

C3_NAMESPACE_BEGIN
class CComponent : public EEntity
{
public:
    CComponent();
};

class CTransform : public CComponent
{
public:
    CTransform()
    {
        bTMDirty = true;
        Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    void SetPosition(float x, float y, float z)
    {
        Translate.x = x;
        Translate.y = y;
        Translate.z = z;
    }
    glm::vec3 GetPosition()
    {
        return Translate;
    }
    void* GetMatrixData()
    {
        if(!bTMDirty)
            return glm::value_ptr(TransformMatrix);
        TransformMatrix = glm::scale(glm::mat4(1), Scale);
        glm::mat4 rotateMatrix = glm::eulerAngleXYZ(Rotation[0], Rotation[1], Rotation[2]);
        TransformMatrix = rotateMatrix * TransformMatrix;
        TransformMatrix = glm::translate(TransformMatrix, Translate);
        bTMDirty = false;
        return glm::value_ptr(TransformMatrix);
    }
protected:
    glm::vec3 Translate;
    glm::vec3 Scale;
    glm::vec3 Rotation;

    bool bTMDirty;
    glm::mat4 TransformMatrix;
};
C3_NAMESPACE_END
