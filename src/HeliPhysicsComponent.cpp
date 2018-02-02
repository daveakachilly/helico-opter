//
//  DefaultPhysicsComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HelicopterInputComponent.hpp"
#include "HeliPhysicsComponent.hpp"

using namespace std;
using namespace glm;

void HeliPhysicsComponent::update(GameObject& heli, GameObject& human, float dt) {
    integrate(heli, human, dt);
}

void HeliPhysicsComponent::integrate(GameObject& heli, GameObject& human, float dt){
    
    heli.velocity += heli.impulse;
    heli.impulse = vec3(0.0f);
    
    vec3 acceleration = calculateAcceleration(heli, dt);
    
    heli.velocity += acceleration * dt;
    heli.position += heli.velocity * dt;
    
    float groundHeight = calculateGroundHeight();
	float skyHeight = 17.0f;
	heli.notMoving = false;
    if(heli.position.y < groundHeight ) {
        heli.velocity.y = 0.0f;
        heli.position.y = groundHeight;
		heli.notMoving = true;
    }
	else if (heli.position.y > skyHeight) {
		if (heli.up == true) {
			heli.velocity.y = 0.0f;
			heli.notMoving = true;
		}
		heli.position.y = skyHeight;
	}
}

float HeliPhysicsComponent::calculateGroundHeight() {
    return -5.0f;
}

vec3 HeliPhysicsComponent::calculateAcceleration(GameObject& gameObject, float dt) {
    vec3 acceleration = vec3(0.0f); // meters per second per second
    acceleration.y = -9.8f;
    
    float frictionMultiplier = 0.95f;
    acceleration.x = -1.0f * frictionMultiplier * gameObject.velocity.x;
    
    return acceleration;
}
