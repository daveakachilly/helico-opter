//
//  DefaultPhysicsComponent.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "HumanPhysicsComponent.hpp"

using namespace std;
using namespace glm;

void HumanPhysicsComponent::update(GameObject& human, GameObject& heli, float dt) {
    integrate(human, heli, dt);
}

void HumanPhysicsComponent::integrate(GameObject& human, GameObject& heli, float dt) {
    
	float xH = heli.position.x;
	float yH = heli.position.y;

	human.position.x = xH;
	human.position.y = yH + human.impulse.y;
	if (human.position.y < yH - 10.0f) {
		human.velocity.y = 0.0f;
		human.position.y = yH - 10.0f;
	}
	else if (human.position.y > heli.position.y - 2.0f) {
		human.velocity.y = 0.0f;
		human.position.y = yH- 2.0f;
	}

	
	/*
    human.velocity += human.impulse;
    human.impulse = vec3(0.0f);
    
    vec3 acceleration = calculateAcceleration(human, dt);
    
    human.velocity += acceleration * dt;
    human.position += human.velocity * dt;
    

	//human.position += human.impulse;
	
    float groundHeight = calculateGroundHeight();
	float skyHeight = 17.0f;
	if (heli.notMoving == true && human.up == false && human.down == false) {
		human.position -= human.velocity * dt;
		human.velocity.y = 0.0f;
	}
    else if(human.position.y < heli.position.y - 10.0f ) {
        human.velocity.y = 0.0f;
        human.position.y = heli.position.y - 10.0f;
    }
	else if (human.position.y > heli.position.y - 2.0f) {
		human.velocity.y = 0.0f;
		human.position.y = heli.position.y - 2.0f;
	}
	*/
}

float HumanPhysicsComponent::calculateGroundHeight() {
    return -15.0f;
}

vec3 HumanPhysicsComponent::calculateAcceleration(GameObject& gameObject, float dt) {
    vec3 acceleration = vec3(0.0f); // meters per second per second
    acceleration.y = -9.8f;
    
    float frictionMultiplier = 0.95f;
    acceleration.x = -1.0f * frictionMultiplier * gameObject.velocity.x;
    
    return acceleration;
}
