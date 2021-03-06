//
//  Application.hpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/25/18.
//

#ifndef Application_hpp
#define Application_hpp

#include <iostream>
#include <glad/glad.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"
#include "WindowManager.h"
#include "GLTextureWriter.h"

//Helico-opter
#include "State.hpp"

#include "Camera.hpp"
#include "GameObject.hpp"

//Components
#include "Component.hpp"

#include "DefaultInputComponent.hpp"
#include "DefaultPhysicsComponent.hpp"
#include "DefaultGraphicsComponent.hpp"

#include "PlayerInputComponent.hpp"
#include "PlayerGraphicsComponent.hpp"
#include "PlayerPhysicsComponent.hpp"

#include "CagePhysicsComponent.hpp"

#include "PlayerbirdPhysicsComponent.hpp"
#include "PlayerbirdInputComponent.hpp"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "DDS_Loader.hpp"

#include "Box2D/Box2D.h"
#include "B2Draw_OpenGL.hpp"

class Application : public EventCallbacks
{
//const (private?)
    const double pixelsToDegrees_X = 40;
    const double pixelsToDegrees_Y = 40;
    
    const float gridDistanceFromCenter = 10.0f;
    const float gridHeight = -1.5f;
    
    //birds
    const float winDistance = 2000.0f;
    const int numberOfBirds = 300;
    const float bufferDistance = 150.0f; //don't want birds X meters from start or finish
    //vvv (1000-30*2) = 940; 940/100 = 9.4f
    const float distancePerBird = (winDistance - bufferDistance * 2.0f) / (float) numberOfBirds;
    const float birdInitialHorizontalVelocity = -10.0f;
    const float highBirdY = 6.0f;
    const float lowBirdY = 3.0f;
public:
//Variables
    
    bool gameOver = false;
    int playerHealth = 3;
    
    double w = 0; //w is for sin wave frequency.
    
    bool mouseDown = false;
	int copterHealth = 3;
	int manHealth = 3;

    WindowManager * windowManager = nullptr;
    
    //Shader Programs
    std::shared_ptr<Program> mainProgram;
    std::shared_ptr<Program> simpleProgram;
    std::shared_ptr<Program> groundProgram;
	std::shared_ptr<Program> sky;
    
    //Physics & Collisions
    //at global scope
    std::shared_ptr<b2World> world;
    std::shared_ptr<B2Draw_OpenGL> debugDraw;
    
    //State
    std::shared_ptr<State> currentState;
    std::shared_ptr<State> previousState;
    
    std::shared_ptr<Camera> camera;
    
    bool playerBirdIsFlying = false;
    std::shared_ptr<GameObject> player;
    std::shared_ptr<GameObject> cage;
    std::shared_ptr<GameObject> playerbird;
    b2Vec2 ropeAnchorPlayer;
    b2Vec2 ropeAnchorCage;
    b2DistanceJoint *distanceJoint; //A = helicopter, B = cage
    b2RopeJoint *ropeJoint; //A = helicopter, B = cage
    
	std::shared_ptr<GameObject> copterHealthObjs[5];
	std::shared_ptr<PlayerInputComponent> playerInputComponent;
    std::shared_ptr<PlayerbirdInputComponent> playerbirdInputComponent;
    std::shared_ptr<GameObject> temporaryGameObjectPointer;
    float ropeLength = 1.0f;
    
    std::shared_ptr<Model> temporaryModel;
    std::shared_ptr<Model> sphereModel;
    std::shared_ptr<Model> birdModel;
    std::shared_ptr<Model> helicopterModel;
    std::shared_ptr<Model> propellerModel;
    std::shared_ptr<Model> blimpModel;
    std::shared_ptr<Model> cloudModel;
    std::shared_ptr<Model> pirateModel;
    std::shared_ptr<Model> birdcageModel;
    std::shared_ptr<Model> playerbirdModel;
    
    std::vector< std::shared_ptr<Model> > models;
    
    std::vector< std::shared_ptr<InputComponent> > inputComponents;
    std::vector< std::shared_ptr<PhysicsComponent> > physicsComponents;
    std::vector< std::shared_ptr<GraphicsComponent> > graphicsComponents;
    
    std::shared_ptr<Texture> heightmapTexture;
    std::shared_ptr<Texture> grassTexture;
    std::shared_ptr<Texture> waterTexture;
    
    
    //ground plane info
    GLuint GroundBufferObject, GroundNormalBufferObject, GroundTextureBufferObject, GroundIndexBufferObject;
    int gGiboLen;
    
//Functions
    /* Initilizations */
    void init(const std::string& resourceDirectory);
    
    void initEntities();
    void initBox2DWorld();
    
    void initShaders(const std::string& resourceDirectory);
    void initMainProgram(const std::string& resourceDirectory);
    void initSimpleProgram(const std::string& resourceDirectory);
    void initGroundProgram(const std::string& resourceDirectory);

    void initTextures(const std::string& resourceDirectory);
	// Separate texture for water
    void initWaterTextures(const std::string& resourceDirectory);

    void initGeom(const std::string& resourceDirectory);
    
    b2Body* createBodyFromModel(std::shared_ptr<Model> model, float mass, glm::vec2 position, char const* name);
    void initPlayer(std::shared_ptr<Model> model, std::shared_ptr<Model> propModel);
    void initRope();
    void initCage(std::shared_ptr<Model> model);
    void initPlayerbird(std::shared_ptr<Model> model);
    void initCamera();
    
    void createBlimp(std::shared_ptr<Model> model, glm::vec2 position);
    void initBlimps();
    
    void createBird(std::shared_ptr<Model> model, glm::vec2 position);
    void initBirds();
    
    void initQuad();
    
    void renderGround();

	//Skybox
	GLuint vbo, vao, tex_cube;

	void initSkybox(const std::string& resourceDirectory, 
		const std::string& skyboxDirectory);
	void createCubeMap(const std::string& front, const std::string& back,
		const std::string& top, const std::string& bottom, const std::string& left,
		const std::string& right, GLuint* tex_cube);
	bool loadCubeMapSide(GLuint texture, GLenum side_target,
		const std::string& filename);
    
    //Physics
    void integrate(float t, float dt);
    void render(float t,  float alpha);
    void renderState(State& state, float t);
    
    void simulate(float dt);
    
    // helper function to set materials for shading
    static void SetMaterial(const std::shared_ptr<Program> prog, int i);
    
    //[0,1.0]
    float randomFloat();
    //[-1.0, 1.0]
    float randomFloatNegativePossible();

	void initGUI();
	void moveGUIElements();
    
    void gameLost();
    
    void accelerateLadderman(float acceleration);
    void createPlayerBird(b2Vec2 direction);
    
    //Control Callbacks
    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void scrollCallback(GLFWwindow* window, double deltaX, double deltaY);
    void mouseCallback(GLFWwindow *window, int button, int action, int mods);
    void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    void resizeCallback(GLFWwindow *window, int width, int height);

	//Menu
	int menuOption = 1;
	int gSiboLen;
	bool on = true;
	bool instructions = false;

	GLuint StBuffObj, StNorBuffObj, StTexBuffObj, StIndxBuffObj;

	std::shared_ptr<Program> menuProgram;
	std::shared_ptr<Texture> menuStartTex;

	void initMenuProgram(const std::string& resourceDirectory);
	void initMenu();
	void renderMenu();

};

#endif /* Application_hpp */
