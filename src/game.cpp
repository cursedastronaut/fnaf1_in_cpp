#include "game.hpp"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init() {
	if (isCustomNight) {
		return;
	}

	if (night < 1 || night >= 7) {
		std::cerr << "WARN: Night count is not between 1 and 7 (both included), it is " << night << ". It has been reset to 7.";
		night = 7;
	}

	freddy_init(&freddy,	NIGHT[night == 7 ? 6 : night][FREDDY]);
	bonnie_init(&bonnie,	NIGHT[night == 7 ? 6 : night][BONNIE]);
	bonnie_init(&chica,		NIGHT[night == 7 ? 6 : night][CHICA ]);
	foxy_init  (&foxy,		NIGHT[night == 7 ? 6 : night][FOXY  ]);
}

void Game::Main() {
	if (!dis.hasFinishedLoadingTextures()) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 650), ImVec2( 1280 * ((float)dis.getNumberOfTextureLoaded() / (float)dis.getNumberOfTextureToLoad()) ,720), IM_COL32_WHITE);
		dis.keepLoading("resources/ordered/");
		return;
	}
	switch (scenes)
	{
	case 0:
		mainMenu();
		break;
	
	case 1:
		inGame();
		break;
	
	default:
		break;
	}
}

void Game::mainMenu() {
	ImGui::Begin("debug");
	if (ImGui::Button("Start night")) {
		Init();
		scenes = 1;
	}
	ImGui::End();

	ImGui::GetBackgroundDrawList()->AddImage((ImTextureID)(intptr_t)dis.getTexture(0)->texture, ImVec2(0,0), ImVec2(dis.getTexture(0)->width, dis.getTexture(0)->height), ImVec2(0, 0), ImVec2(1, 1));
}

void Game::inGame() {

}