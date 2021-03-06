//
//  GameObject.cpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/28/18.
//

#include "GameObject.hpp"

using namespace std;

shared_ptr<GameObject> GameObject::interpolate(shared_ptr<GameObject> previous, shared_ptr<GameObject> current, float alpha)
{
    shared_ptr<GameObject> gameObject;
    
    /* Why are we constructing this gameObject using 'current'?
     * Won't this copy the component pointers?
     * Yes, gameObject needs a copy of GraphicsComponent for rendering purposes
     * It should not modify any of the variables of any components.
     */
    gameObject = make_shared<GameObject>( *current.get() );
    
    gameObject->position = current->position*alpha + previous->position*(1-alpha);
    gameObject->velocity = current->velocity*alpha + previous->velocity*(1-alpha);
    
    
    return gameObject;
}

GameObject::GameObject(const GameObject& gameObject) { //Copy Constructor
	this->position = gameObject.position;
	this->velocity = gameObject.velocity;
	
	this->input = gameObject.input;
    this->physics = gameObject.physics;
    this->graphics = gameObject.graphics;
}

GameObject::GameObject(std::shared_ptr<InputComponent> inputComponent, std::shared_ptr<PhysicsComponent> physicsComponent, std::shared_ptr<GraphicsComponent> graphicsComponent) {
    this->input = inputComponent;
    this->physics = physicsComponent;
    this->graphics = graphicsComponent;
}

void GameObject::simulate(float dt)
{
    velocity.z = 0.0f; //don't want them moving zed
    //position.z = 0.0f; //don't want them not being 0
    
    
    if(collisionCooldown > 0.0f) {
        collisionCooldown -= dt;
    } else if (collisionCooldown < 0.0f) {
        collisionCooldown = 0.0f;
    }
    
	if (body != nullptr) {
		b2Vec2 position2D = body->GetPosition(); //Box2D vec2
		glm::vec3 position3D = glm::vec3(position2D.x, position2D.y, 0.0f); //glm::vec3
		position = position3D;
        
        rotation = glm::vec3(0.0f, 0.0f, body->GetAngle());
	}
    
    input->update(*this, dt);
    physics->update(*this, dt);
}

void GameObject::render(float t, std::shared_ptr<Program> prog) {
    graphics->update(*this, t, prog);
}
