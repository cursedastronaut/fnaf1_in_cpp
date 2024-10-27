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
	dl = ImGui::GetBackgroundDrawList();
	switch (scenes)
	{
	case 0:
		loading();
		break;
	
	case 1:
		mainMenu();
		break;
	
	case 2:
		inGame();
		break;
	
	default:
		break;
	}
	dis.draw(ImGui::GetBackgroundDrawList());
}

void Game::mainMenu() {
	ImGui::Begin("debug");
	if (ImGui::Button("Start night")) {
		Init();
		scenes = 2;
	}
	ImGui::End();

	//ImGui::GetBackgroundDrawList()->AddImage((ImTextureID)(intptr_t)dis.getTexture(0)->texture, ImVec2(0,0), ImVec2(dis.getTexture(0)->width, dis.getTexture(0)->height), ImVec2(0, 0), ImVec2(1, 1));
	dis.drawSpriteFS(189, 1);
	dis.drawSpriteFS(506, 2);
}

void Game::inGame() {

}

void Game::loading() {
	if (dis.hasFinishedLoadingTextures()) {
		scenes = 1;
		return;
	}

	if (dis.getNumberOfTextureLoaded() > 1) {
		ImTexture *it = dis.getTexture(0);
		dis.drawSprite(0, {(float)SCREEN_WIDTH/2.f - (float)it->width/2.f, (float)SCREEN_HEIGHT/2.f - (float)it->height/2.f}, 1);
		it = dis.getTexture(1);
		dis.drawSprite(1, {(float)SCREEN_WIDTH - (float)it->width, (float)SCREEN_HEIGHT - 10.f - (float)it->height}, 1);
	}

	dl->AddRectFilled(ImVec2(0, 710), ImVec2( 1280 * ((float)dis.getNumberOfTextureLoaded() / (float)dis.getNumberOfTextureToLoad()) ,720), IM_COL32_WHITE);
	dis.keepLoading("resources/ordered/");
}