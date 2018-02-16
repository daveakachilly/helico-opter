//
//  HumanInputComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HumanInputComponent.hpp"

void HumanInputComponent::update(GameObject& gameObject) {
    if (humanUp) {
        gameObject.impulse += gameObject.forwardDirection * 10.0f;
		if (gameObject.impulse.y > 0.f)
			gameObject.impulse.y = 0.f;
    } else if (humanDown) {
        gameObject.impulse += gameObject.forwardDirection * -10.0f;
		if (gameObject.impulse.y < -10.f)
			gameObject.impulse.y = -10.f;
    }
    if (jumping) {
        gameObject.impulse.y += 2.0f;
        jumping = false;
    }
}
