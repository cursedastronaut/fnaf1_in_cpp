#include "game/constants.h"
#include "game/animatronics.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
//#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct ImTexture {
	GLuint texture;
	int width;
	int height;
};

class Resources
{
private:
	size_t currentIndex = 0;
	// Simple helper function to load an image into a OpenGL texture with common settings
	bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);
	// Open and read a file, then forward to LoadTextureFromMemory()
	bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);
	
	bool hasFinishedLoading = false;
	std::vector<ImTexture> textures;
	std::vector<std::string> lines;

public:
	Resources();
	~Resources();
	
	void keepLoading(std::string folder);

	bool hasFinishedLoadingTextures();
	size_t getNumberOfTextureToLoad();
	size_t getNumberOfTextureLoaded();
	ImTexture *getTexture(size_t index);
	std::vector<ImTexture>* getTextures();
	
};



