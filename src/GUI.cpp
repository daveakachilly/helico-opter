//
//  GUI.cpp
//  Helico-opter
//
//  Created by David McIntyre on 3/1/18.
//

#include "GUI.hpp"

using namespace std;
using namespace glm; //glm::radians() --> radians(); glm::vec3 --> vec3

void GUI::init() {
	int width, height, bpp;
	toStart = stbi_load( "/resources/UI/tostart.png", &width, &height, &bpp, STBI_rgb_alpha);
}

void GUI::showToStart() {
	if(toStart == nullptr)
    throw(std::string("Failed to load texture"));

	glGenTextures(1, &m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if(bpp == 3)
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, toStart);
	else if(bpp == 4)
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, toStart);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(toStart);
}