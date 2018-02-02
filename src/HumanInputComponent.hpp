//
//  HumanInputComponent.hpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#ifndef HumanInputComponent_hpp
#define HumanInputComponent_hpp

#include <stdio.h>

#include "Component.hpp"
#include "glm/glm.hpp"

class HumanInputComponent : public InputComponent
{
public:
    //Variables
    bool humanUp = false;
    bool humanDown = false;
    bool jumping = false;
    
    //Functions
    virtual void update(GameObject& gameObject);
};

#endif /* PlayerInputComponent_hpp */
