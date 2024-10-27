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

void		Displaying::drawSpriteFS(size_t spriteID, const uint64_t z) {
	sprites.push_back({spriteID, {0, 0}, {1280, 720}, z});
}

void		Displaying::drawSprite(const size_t spriteID, const ImVec2 p_min, const ImVec2 p_max, const uint64_t z) {
	sprites.push_back({spriteID, p_min, p_max, z});
}

void		Displaying::drawSprite(const size_t spriteID, const ImVec2 p_min, const uint64_t z) {
	try	{
		ImTexture *texture = res.getTexture(spriteID);
		sprites.push_back({spriteID, p_min, ImVec2(p_min.x + texture->width, p_min.y + texture->height), z});
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

void		Displaying::draw(ImDrawList *dl) {
	if (dl == nullptr) {
		#if !defined(NDEBUG)
		std::cerr << "ERROR: Displaying::draw(ImDrawList *dl): *dl is nullptr!" << std::endl;
		#endif
		return;
	}

	std::sort(sprites.begin(), sprites.end(), [](const sprite& a, const sprite& b) {
		return a.z < b.z;
	});

	for (size_t i = 0, limit = sprites.size(); i < limit; ++i) {
		try	{
			ImTexture *texture = res.getTexture(sprites.at(i).index);
			dl->AddImage((ImTextureID)(intptr_t)texture->texture, sprites.at(i).p_min, sprites.at(i).p_max);
		} catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}

	sprites.clear();
}