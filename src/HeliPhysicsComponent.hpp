//
//  DefaultPhysicsComponent.hpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#ifndef HeliPhysicsComponent_hpp
#define HeliPhysicsComponent_hpp

#include <stdio.h>

#include "Component.hpp"
#include "glm/glm.hpp"

class HeliPhysicsComponent : public PhysicsComponent
{
public:
    virtual void update(GameObject& gameObject1, GameObject& gameObject2, float dt);
    void integrate(GameObject& gameObject1, GameObject& gameObject2, float dt);
    
    float calculateGroundHeight();
    
    glm::vec3 calculateAcceleration(GameObject& gameObject, float dt);
};

#endif /* DefaultPhysicsComponent_hpp */
