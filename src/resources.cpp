#include "resources.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool Resources::LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload pixels into texture
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}

// Open and read a file, then forward to LoadTextureFromMemory()
bool Resources::LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height)
{
	FILE* f = fopen(file_name, "rb");
	if (f == NULL)
		return false;
	fseek(f, 0, SEEK_END);
	size_t file_size = (size_t)ftell(f);
	if (file_size == 0)
		return false;
	fseek(f, 0, SEEK_SET);
	void* file_data = IM_ALLOC(file_size);
	fread(file_data, 1, file_size, f);
	bool ret = LoadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
	IM_FREE(file_data);
	return ret;
}

Resources::Resources()
{
	std::ifstream file = std::ifstream("tools/file_list.txt");
	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	file.close();
}

Resources::~Resources()
{
	for (ImTexture& img : textures) {
		if (img.texture != 0) {
			glDeleteTextures(1, &img.texture);
			img.texture = 0; // Reset image ID to 0 to avoid dangling references
		}
	}
	textures.clear(); // Clear the vector to release any remaining resources
	lines.clear();
}

void Resources::keepLoading(std::string folder) {
	if (currentIndex >= lines.size()) {
		hasFinishedLoading = true;
		return;
	}

	ImTexture img = {0, 0, 0};
	bool ret = LoadTextureFromFile((folder + lines.at(currentIndex)).c_str(), &img.texture, &img.width, &img.height);
	++currentIndex;
	if (!ret) {
		std::cerr << "Failed to load texture from file: " << lines.at(currentIndex-1) << std::endl;
		return; // Skip adding to `images` if loading fails
	}
	textures.push_back(img); // Only push if loading succeeds
}

bool Resources::hasFinishedLoadingTextures() {
	return hasFinishedLoading;
}

size_t Resources::getNumberOfTextureToLoad() {
	return lines.size();
}

size_t Resources::getNumberOfTextureLoaded() {
	return textures.size();
}

std::vector<ImTexture>* Resources::getTextures() {
	return &textures;
}

ImTexture *Resources::getTexture(size_t index) {
	if (index >= textures.size()) throw std::out_of_range("getTexture(size_t): No texture at specified index.");
	return &textures[index];
}
