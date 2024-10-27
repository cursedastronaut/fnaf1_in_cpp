#pragma once
#include "resources.hpp"
#include <algorithm>
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

struct sprite
{
	size_t		index;
	ImVec2		p_min;
	ImVec2		p_max;
	uint64_t	z;
};


class Displaying
{
private:
	Resources res;
	std::vector<sprite> sprites;

public:
	void keepLoading(std::string);
	Displaying(/* args */);
	~Displaying();

	bool		hasFinishedLoadingTextures();
	size_t		getNumberOfTextureToLoad();
	size_t		getNumberOfTextureLoaded();
	ImTexture	*getTexture(size_t index);
	void		drawSpriteFS(size_t spriteID, const uint64_t z);
	void		drawSprite(const size_t spriteID, const ImVec2 p_min, const uint64_t z);
	void		drawSprite(const size_t spriteID, const ImVec2 p_min, const ImVec2 p_max, const uint64_t z);

	void		draw(ImDrawList *);
};


