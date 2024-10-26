#include "displaying.hpp"

Displaying::Displaying(/* args */)
{
}

Displaying::~Displaying()
{
}

void Displaying::keepLoading(std::string folder) {
	res.keepLoading(folder);
}

bool		Displaying::hasFinishedLoadingTextures() {
	return res.hasFinishedLoadingTextures();
}

size_t		Displaying::getNumberOfTextureToLoad() {
	return res.getNumberOfTextureToLoad();
}

size_t		Displaying::getNumberOfTextureLoaded() {
	return res.getNumberOfTextureLoaded();
}

ImTexture	*Displaying::getTexture(size_t index) {
	return res.getTexture(index);
}