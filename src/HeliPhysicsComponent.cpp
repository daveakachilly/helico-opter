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
	printf("In physics: %f\n", heli.impulse.y);
    heli.impulse = vec3(0.0f);
    vec3 acceleration = calculateAcceleration(heli, dt);
	//vec3 acceleration = vec3(0.0f);
	printf("acceleration: %f", acceleration.y);
    heli.velocity += acceleration * dt;
    heli.position += heli.velocity * dt;
	printf("position: %f", heli.position.y);
	//printf("%f", heli.velocity);
    float groundHeight = calculateGroundHeight();
	float skyHeight = 7.0f;
	//heli.notMoving = false;
    if(heli.position.y < groundHeight ) {
		printf("%s\n", "too low");
        heli.velocity.y = 0.0f;
        heli.position.y = groundHeight;
		//heli.notMoving = true;
    }
	else if (heli.position.y > skyHeight) {
		printf("%s\n", "too high");
		if (heli.up == true) {
			heli.velocity.y = 0.0f;
			//heli.notMoving = true;
		}
		heli.position.y = skyHeight;
	}
}

float HeliPhysicsComponent::calculateGroundHeight() {
    return -7.0f;
}

vec3 HeliPhysicsComponent::calculateAcceleration(GameObject& gameObject, float dt) {
    vec3 acceleration = vec3(0.0f); // meters per second per second
    acceleration.y = -0.5f;
    
    float frictionMultiplier = 0.95f;
    acceleration.x = -1.0f * frictionMultiplier * gameObject.velocity.x;
    
    return acceleration;
}
