//
//  Camera.hpp
//  Helico-opter
//
//  Created by Alex Saalberg on 1/29/18.
//

#ifndef GUI_hpp
#define GUI_hpp

#include <stdio.h>
#include <memory> //std::shared_ptr

#include <glm/gtc/type_ptr.hpp> //value_ptr( std::shared_ptr )
#include "GLSL.h" //CHECKED_GL_CALL

#include "MatrixStack.h"

#include "Program.h"



class GUI
{
public:
    unsigned char* toStart;
    void init();
    void showToStart();
};

#endif /* GUI_hpp */
