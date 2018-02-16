//
//  HelicopterInputComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HelicopterInputComponent.hpp"

void HelicopterInputComponent::update(GameObject& gameObject) {
    if (helicopterUp) {
        gameObject.impulse += gameObject.forwardDirection * 0.5f;
    } else if (helicopterDown) {
        gameObject.impulse += gameObject.forwardDirection * -0.5f;
    }
    if (jumping) {
        gameObject.impulse.y += 2.0f;
        jumping = false;
    }
}
