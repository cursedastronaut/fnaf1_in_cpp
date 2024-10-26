#pragma once
#include "resources.hpp"

class Displaying
{
private:
	Resources res;
public:
	void keepLoading(std::string);
	Displaying(/* args */);
	~Displaying();

	bool		hasFinishedLoadingTextures();
	size_t		getNumberOfTextureToLoad();
	size_t		getNumberOfTextureLoaded();
	ImTexture	*getTexture(size_t index);
};


