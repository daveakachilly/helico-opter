//
//  Player.cpp
//  final471project
//
//  Created by Alex Saalberg on 11/27/17.
//

#include "Player.h"

using namespace glm;
using namespace std;

void Player::step(double dt) {
    double framerate = 60.0f;
    dt *= framerate;
    //forward/back movement
    float movX = cos(radians(cameraTheta)) * velocity.x;
    float movZ = sin(radians(cameraTheta)) * velocity.x;
    
    //strafing
    movX += cos(radians(cameraTheta + 90)) * velocity.z;
    movZ += sin(radians(cameraTheta + 90)) * velocity.z;
    
    if(position.y < height) {
        velocity.y = 0.0f;
        position.y = height;
    } else if (position.y > height) {
        velocity.y -= gravityAcceleration * dt;
    }
    velocity *= frictionMultiplier * dt;
    
    position.y += velocity.y * dt;
    
    //Minus equals because camera is opposite
    position.x += movX * dt;
    position.z += movZ * dt;
    
    //If velocity is very low (<~0.01f), consider the player to be stopped;
    velocity.x = clampVelocity(velocity.x, minHorizontalVelocity);
    velocity.z = clampVelocity(velocity.z, minHorizontalVelocity);
    
    this->avatar->position = this->position;
}

void Player::setModelIdentityMatrix(const std::shared_ptr<Program> prog) const {
    auto M = make_shared<MatrixStack>();
    M->pushMatrix();
        M->loadIdentity();
        CHECKED_GL_CALL( glUniformMatrix4fv(
            prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix())) );
    M->popMatrix();
}

void Player::setHelicopterViewMatrix(const std::shared_ptr<Program> prog) const {
    float x = cos(radians(cameraPhi))*cos(radians(cameraTheta));
    float y = sin(radians(cameraPhi));
    float z = cos(radians(cameraPhi))*sin(radians(cameraTheta));
    
    x = -cameraDistance;
    z = 0.0f;
    y = 0.0f;
    
    vec3 cameraIdentityVector = vec3(x, y, z);
    
    auto V = make_shared<MatrixStack>();
    V->pushMatrix();
    V->loadIdentity();
    V->lookAt(vec3(0, 0, 0), cameraIdentityVector, vec3(0, 1, 0));
    V->translate((-position)); //Negative
    V->translate(vec3(-cameraDistance, 0.0f, 0.0f));
    CHECKED_GL_CALL( glUniformMatrix4fv(
                                        prog->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix())) );
    V->popMatrix();
}

void Player::setViewMatrix(const std::shared_ptr<Program> prog) const {
    float x = cos(radians(cameraPhi))*cos(radians(cameraTheta));
    float y = sin(radians(cameraPhi));
    float z = cos(radians(cameraPhi))*sin(radians(cameraTheta));
    vec3 cameraIdentityVector = vec3(x, y, z);
    
    auto V = make_shared<MatrixStack>();
    V->pushMatrix();
        V->loadIdentity();
        V->lookAt(vec3(0, 0, 0), cameraIdentityVector, vec3(0, 1, 0));
        V->translate(-position); //Negative 
        CHECKED_GL_CALL( glUniformMatrix4fv(
            prog->getUniform("V"), 1, GL_FALSE, value_ptr(V->topMatrix())) );
    V->popMatrix();
}

void Player::setProjectionMatrix(const std::shared_ptr<Program> prog, float aspect) const {
    auto P = make_shared<MatrixStack>();
    P->pushMatrix();
        P->perspective(45.0f, aspect, 0.01f, 100.0f);
        //P->perspective(45.0f, aspect, 0.05f, 100.0f);
        CHECKED_GL_CALL( glUniformMatrix4fv(
            prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix())) );
    P->popMatrix();
}

void Player::setEyePosition(const std::shared_ptr<Program> prog) const {
    CHECKED_GL_CALL( glUniform3f(
        prog->getUniform("eyePosition"), position.x + cameraDistance, position.y, position.z) );
}

void Player::jump() {
    velocity.y += 0.2f;
}

void Player::restrictCamera() {
    cameraPhi = glm::clamp(cameraPhi, cameraPhiMin, cameraPhiMax);
}

void Player::moveForward() { //speed is ~0.2f
    velocity.x += speed * speedMod.x; //pSpeedMod.x is forward movement scalar (prob 100%)
}
void Player::moveLeft() {
    velocity.z -= speed * speedMod.y; //pSpeedMod.x is forward movement scalar (prob 100%)
}
void Player::moveRight() {
    velocity.z += speed * speedMod.y; //pSpeedMod.x is forward movement scalar (prob 100%)
}
void Player::moveBackward() {
    velocity.x -= speed * speedMod.z; //pSpeedMod.x is forward movement scalar (prob 100%)
}
