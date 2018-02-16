//
//  HelicopterInputComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HelicopterInputComponent.hpp"

void HelicopterInputComponent::update(GameObject& gameObject) {
	printf("%d",helicopterUp);
    if (helicopterUp) {
		printf("%s", "here");
        gameObject.impulse += gameObject.forwardDirection * 2.0f;
		printf("cheese nuggets: %f\n", gameObject.impulse.y);
    } else if (helicopterDown) {
        gameObject.impulse += gameObject.forwardDirection * -2.0f;
    }
    if (jumping) {
        gameObject.impulse.y += 2.0f;
        jumping = false;
    }
}
