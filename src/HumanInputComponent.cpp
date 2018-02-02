//
//  HumanInputComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HumanInputComponent.hpp"

void HumanInputComponent::update(GameObject& gameObject) {
    if (humanUp) {
        gameObject.impulse += gameObject.forwardDirection * 0.5f;
    } else if (humanDown) {
        gameObject.impulse += gameObject.forwardDirection * -0.5f;
    }
    if (jumping) {
        gameObject.impulse.y += 2.0f;
        jumping = false;
    }
}
