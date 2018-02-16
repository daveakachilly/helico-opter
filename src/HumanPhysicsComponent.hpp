//
//  DefaultPhysicsComponent.hpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#ifndef HumanPhysicsComponent_hpp
#define HumanPhysicsComponent_hpp

#include <stdio.h>

#include "Component.hpp"
#include "glm/glm.hpp"

class HumanPhysicsComponent : public PhysicsComponent
{
public:
    virtual void update(GameObject& heli, GameObject& human, float dt);
    void integrate(GameObject& heli, GameObject& human, float dt);
    
    float calculateGroundHeight();
    
    glm::vec3 calculateAcceleration(GameObject& gameObject, float dt);
};

#endif /* HumanPhysicsComponent_hpp */
