//
//  HumanInputComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HumanInputComponent.hpp"

void HumanInputComponent::update(GameObject& gameObject) {
    if (humanUp || humanDown) {
		if (count == 0)
		{
			gameObject.impulse += gameObject.forwardDirection * 0.5f;
		}
		else {
			gameObject.impulse += gameObject.forwardDirection * 0.5f * float(count);
		}
    }
	printf("Count: %d\n", count);
    if (jumping) {
        gameObject.impulse.y += 2.0f;
        jumping = false;
    }
}
