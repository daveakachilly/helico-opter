//
//  HelicopterInputComponent.hpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#ifndef HelicopterInputComponent_hpp
#define HelicopterInputComponent_hpp

#include <stdio.h>

#include "Component.hpp"
#include "glm/glm.hpp"

class HelicopterInputComponent : public InputComponent
{
public:
    //Variables
    bool helicopterUp = false;
    bool helicopterDown = false;
    bool jumping = false;

    //Functions
    virtual void update(GameObject& gameObject);
};

#endif /* HelicopterInputComponent_hpp */
