#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/TextLabelComponent.h"
#include "../lib/glm/glm.hpp"
#include <random>
#include <time.h>


EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Window* Game::window;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* map;
bool isPlaying;

int maxTime = 60;
int currentTime = maxTime;

Game::Game()
{
	this->isRunning = false;
	this->isCarrying = false;
}

bool Game::IsRunning() const
{
	return this->isRunning;
}

void Game::Initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}
	if (TTF_Init() != 0)
	{
		std::cerr << "Error initializing SDL TTF" << std::endl;
		return;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	LoadLevel(0);

	isRunning = true;
	points = 0;
	isColliding = false;
	isPlaying = false;
	return;
}

Entity& player(manager.AddEntity("ant", PLAYER_LAYER));
Entity& pointDisplay(manager.AddEntity("LabelLevelName", UI_LAYER));
Entity& timer(manager.AddEntity("Timer", UI_LAYER));

int tempX;
int tempY;

Entity& background(manager.AddEntity("BackGround", ENDING_SCREEN_LAYER));
Entity& playText(manager.AddEntity("Playtext", ABOVE_ALL_LAYER));
Entity& quitText(manager.AddEntity("Quittext", ABOVE_ALL_LAYER));
Entity& finalPointText(manager.AddEntity("FinalPointText", ABOVE_ALL_LAYER));

Entity& redAnt1(manager.AddEntity("redAnt1", ENEMY_LAYER));
Entity& redAnt2(manager.AddEntity("redAnt2", ENEMY_LAYER));
Entity& redAnt3(manager.AddEntity("redAnt3", ENEMY_LAYER));
Entity& redAnt4(manager.AddEntity("redAnt4", ENEMY_LAYER));
Entity& redAnt5(manager.AddEntity("redAnt5", ENEMY_LAYER));
Entity& redAnt6(manager.AddEntity("redAnt6", ENEMY_LAYER));
Entity& redAnt7(manager.AddEntity("redAnt7", ENEMY_LAYER));
Entity& redAnt8(manager.AddEntity("redAnt8", ENEMY_LAYER));
Entity& redAnt9(manager.AddEntity("redAnt9", ENEMY_LAYER));
Entity& redAnt10(manager.AddEntity("redAnt10", ENEMY_LAYER));
Entity& redAnt11(manager.AddEntity("redAnt11", ENEMY_LAYER));
Entity& redAnt12(manager.AddEntity("redAnt12", ENEMY_LAYER));


void Game::LoadLevel(int levelNumber)
{

#pragma region MainMenu
	if (levelNumber == 0)
	{
		std::cout << "Level 0" << std::endl;
		assetManager->AddTexture("background", std::string("./assets/images/BG.png").c_str());
		assetManager->AddFont("charriot-font-main", std::string("./assets/fonts/charriot.ttf").c_str(), 50);

		background.AddComponent<TransformComponent>(0, 0, 0, 0, 1920, 1080, 1);
		background.AddComponent<SpriteComponent>("background", false);

		playText.AddComponent<TextLabelComponent>(WINDOW_WIDTH / 6 ,WINDOW_HEIGHT / 4, "PRESS ENTER TO PLAY", "charriot-font-main", WHITE_COLOR);

		quitText.AddComponent<TextLabelComponent>(WINDOW_WIDTH / 6 - 5, WINDOW_HEIGHT / 2, "PRESS ESCAPE TO EXIT", "charriot-font-main", WHITE_COLOR);
	}
#pragma endregion

#pragma region Level 1
if (levelNumber == 1)
	{
	background.GetComponent<TransformComponent>()->position.x = 10000;

		/* Start including new assets to the assetmanager list */
		assetManager->AddTexture("ant_animated-image", std::string("./assets/images/ant-animation.png").c_str());
		assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
		assetManager->AddTexture("ant-hole-image", std::string("./assets/images/ant-hole.png").c_str());
		assetManager->AddTexture("pretzel-image", std::string("./assets/images/Pretzel.png").c_str());
		assetManager->AddTexture("bread-image", std::string("./assets/images/Bread.png").c_str());
		assetManager->AddTexture("mushroom-image", std::string("./assets/images/Mushroom.png").c_str());
		assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

		assetManager->AddTexture("red-ant-down", std::string("./assets/images/red-ant-down.png").c_str());
		assetManager->AddTexture("red-ant-up", std::string("./assets/images/red-ant-up.png").c_str());
		assetManager->AddTexture("red-ant-left", std::string("./assets/images/red-ant-left.png").c_str());
		assetManager->AddTexture("red-ant-right", std::string("./assets/images/red-ant-right.png").c_str());


		map = new Map("jungle-tiletexture", 2, 32);
		map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

		/* Start including entities and also components to them */
		player.AddComponent<TransformComponent>(240, 106, 0, 0, 41, 41, 1);
		player.AddComponent<SpriteComponent>("ant_animated-image", 1, 90, true, false);
		player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
		player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 41, 41);

	#pragma region RedAnts

		tempY = ReturnRandomInt(-50, 300);
		redAnt1.AddComponent<TransformComponent>(0, tempY, 30, 0, 41, 41, 1);
		redAnt1.AddComponent<SpriteComponent>("red-ant-right", 1, 90, true, false);
		redAnt1.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempY = ReturnRandomInt(300, 500);
		redAnt2.AddComponent<TransformComponent>(0, tempY, 30, 0, 41, 41, 1);
		redAnt2.AddComponent<SpriteComponent>("red-ant-right", 1, 90, true, false);
		redAnt2.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempY = ReturnRandomInt(500, 1000);
		redAnt3.AddComponent<TransformComponent>(0, tempY, 30, 0, 41, 41, 1);
		redAnt3.AddComponent<SpriteComponent>("red-ant-right", 1, 90, true, false);
		redAnt3.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempY = ReturnRandomInt(-50, 300);
		redAnt4.AddComponent<TransformComponent>(850, tempY, -30, 0, 41, 41, 1);
		redAnt4.AddComponent<SpriteComponent>("red-ant-left", 1, 90, true, false);
		redAnt4.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempY = ReturnRandomInt(300, 500);
		redAnt5.AddComponent<TransformComponent>(850, tempY, -30, 0, 41, 41, 1);
		redAnt5.AddComponent<SpriteComponent>("red-ant-left", 1, 90, true, false);
		redAnt5.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempY = ReturnRandomInt(500, 1000);
		redAnt6.AddComponent<TransformComponent>(850, tempY, -30, 0, 41, 41, 1);
		redAnt6.AddComponent<SpriteComponent>("red-ant-left", 1, 90, true, false);
		redAnt6.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempX = ReturnRandomInt(0, 1000);
		redAnt7.AddComponent<TransformComponent>(tempX, 0, 0, 30, 41, 41, 1);
		redAnt7.AddComponent<SpriteComponent>("red-ant-down", 1, 90, true, false);
		redAnt7.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempX = ReturnRandomInt(0, 1000);
		redAnt8.AddComponent<TransformComponent>(tempX, 0, 0, 30, 41, 41, 1);
		redAnt8.AddComponent<SpriteComponent>("red-ant-down", 1, 90, true, false);
		redAnt8.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempX = ReturnRandomInt(0, 1000);
		redAnt9.AddComponent<TransformComponent>(tempX, 0, 0, 30, 41, 41, 1);
		redAnt9.AddComponent<SpriteComponent>("red-ant-down", 1, 90, true, false);
		redAnt9.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempX = ReturnRandomInt(0, 1000);
		redAnt10.AddComponent<TransformComponent>(tempX, 800, 0, -30, 41, 41, 1);
		redAnt10.AddComponent<SpriteComponent>("red-ant-up", 1, 90, true, false);
		redAnt10.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempX = ReturnRandomInt(0, 1000);
		redAnt11.AddComponent<TransformComponent>(tempX, 800, 0, -30, 41, 41, 1);
		redAnt11.AddComponent<SpriteComponent>("red-ant-up", 1, 90, true, false);
		redAnt11.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		tempX = ReturnRandomInt(0, 1000);
		redAnt12.AddComponent<TransformComponent>(tempX, 800, 0, -30, 41, 41, 1);
		redAnt12.AddComponent<SpriteComponent>("red-ant-up", 1, 90, true, false);
		redAnt12.AddComponent<ColliderComponent>("ENEMY", 240, 106, 41, 41);

		

#pragma endregion

	#pragma region Mushrooms
		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& mushroom1(manager.AddEntity("mushroom1", ENEMY_LAYER));
		mushroom1.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		mushroom1.AddComponent<SpriteComponent>("mushroom-image");
		mushroom1.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& mushroom2(manager.AddEntity("mushroom2", ENEMY_LAYER));
		mushroom2.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		mushroom2.AddComponent<SpriteComponent>("mushroom-image");
		mushroom2.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& mushroom3(manager.AddEntity("mushroom3", ENEMY_LAYER));
		mushroom3.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		mushroom3.AddComponent<SpriteComponent>("mushroom-image");
		mushroom3.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& mushroom4(manager.AddEntity("mushroom4", ENEMY_LAYER));
		mushroom4.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		mushroom4.AddComponent<SpriteComponent>("mushroom-image");
		mushroom4.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& mushroom5(manager.AddEntity("mushroom5", ENEMY_LAYER));
		mushroom5.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		mushroom5.AddComponent<SpriteComponent>("mushroom-image");
		mushroom5.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

#pragma endregion //Mushrooms

	#pragma region Bread

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& bread1(manager.AddEntity("bread1", ENEMY_LAYER));
		bread1.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		bread1.AddComponent<SpriteComponent>("bread-image");
		bread1.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& bread2(manager.AddEntity("bread2", ENEMY_LAYER));
		bread2.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		bread2.AddComponent<SpriteComponent>("bread-image");
		bread2.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& bread3(manager.AddEntity("bread3", ENEMY_LAYER));
		bread3.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		bread3.AddComponent<SpriteComponent>("bread-image");
		bread3.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& bread4(manager.AddEntity("bread4", ENEMY_LAYER));
		bread4.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		bread4.AddComponent<SpriteComponent>("bread-image");
		bread4.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& bread5(manager.AddEntity("bread5", ENEMY_LAYER));
		bread5.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		bread5.AddComponent<SpriteComponent>("bread-image");
		bread5.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);
#pragma endregion //Bread

	#pragma region Pretzel
		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& pretzel1(manager.AddEntity("pretzel1", ENEMY_LAYER));
		pretzel1.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		pretzel1.AddComponent<SpriteComponent>("pretzel-image");
		pretzel1.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& pretzel2(manager.AddEntity("pretzel2", ENEMY_LAYER));
		pretzel2.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		pretzel2.AddComponent<SpriteComponent>("pretzel-image");
		pretzel2.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& pretzel3(manager.AddEntity("pretzel3", ENEMY_LAYER));
		pretzel3.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		pretzel3.AddComponent<SpriteComponent>("pretzel-image");
		pretzel3.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& pretzel4(manager.AddEntity("pretzel4", ENEMY_LAYER));
		pretzel4.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		pretzel4.AddComponent<SpriteComponent>("pretzel-image");
		pretzel4.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);

		tempX = ReturnRandomInt(0, PLAY_AREA_MAX_X); tempY = ReturnRandomInt(0, PLAY_AREA_MAX_Y);
		Entity& pretzel5(manager.AddEntity("pretzel5", ENEMY_LAYER));
		pretzel5.AddComponent<TransformComponent>(tempX, tempY, 0, 0, 48, 48, 1);
		pretzel5.AddComponent<SpriteComponent>("pretzel-image");
		pretzel5.AddComponent<ColliderComponent>("COIN", tempX, tempY, 48, 48);
#pragma endregion //Pretzel

		Entity& antHole(manager.AddEntity("Ant-hole", VEGETATION_LAYER));
		antHole.AddComponent<TransformComponent>(500, 500, 0, 0, 32, 32, 2);
		antHole.AddComponent<SpriteComponent>("ant-hole-image");
		antHole.AddComponent<ColliderComponent>("DROPOFF", 500, 500, 32, 32);

		pointDisplay.AddComponent<TextLabelComponent>(10, 10, "Points: 0", "charriot-font", WHITE_COLOR);
		timer.AddComponent<TextLabelComponent>(730, 10, "Time: " + std::to_string(maxTime), "charriot-font", WHITE_COLOR);
	}
#pragma endregion

	if (levelNumber == 2)
	{
		ProcessGameOver();
	}
}

bool setBack = false;
void SetAntsBack()
{
	setBack = true;
	redAnt1.GetComponent<TransformComponent>()->position.x = 0;
	redAnt2.GetComponent<TransformComponent>()->position.x = 0;
	redAnt3.GetComponent<TransformComponent>()->position.x = 0;
	redAnt4.GetComponent<TransformComponent>()->position.x = 900;
	redAnt5.GetComponent<TransformComponent>()->position.x = 900;
	redAnt6.GetComponent<TransformComponent>()->position.x = 900;
	redAnt7.GetComponent<TransformComponent>()->position.y = 0;
	redAnt8.GetComponent<TransformComponent>()->position.y = 0;
	redAnt9.GetComponent<TransformComponent>()->position.y = 0;
	redAnt10.GetComponent<TransformComponent>()->position.y = 900;
	redAnt11.GetComponent<TransformComponent>()->position.y = 900;
	redAnt12.GetComponent<TransformComponent>()->position.y = 900;
}

void Game::ProcessInput()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				if (!isPlaying)
				{
					background.Destroy();
					playText.GetComponent<TextLabelComponent>()->SetLabelText("", "charriot-font-main");
					quitText.GetComponent<TextLabelComponent>()->SetLabelText("", "charriot-font-main");;

					isPlaying = true;
					LoadLevel(1);
				}
			}
		}
		default: {
			break;
		}
	}
}

int now;
int last = 0;

void Game::Update()
{
	// Wait until 16ms has ellapsed since the last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

	// Delta time is the difference in ticks from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// Clamp deltaTime to a maximum value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	// Sets the new ticks for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();


	manager.Update(deltaTime);
	if (isPlaying)
	{
		HandleCameraMovement();
		CheckCollisions();

		now = SDL_GetTicks(); //CPU intensive
		if (now - last >= 1000) //Ticks for one second, roughly
		{
			currentTime--;
			timer.GetComponent<TextLabelComponent>()->SetLabelText("Time: " + std::to_string(currentTime), "charriot-font");
			last = now;
			if (currentTime <= 0)
			{
				LoadLevel(2);
			}

			if (currentTime <= 30 && !setBack)
			{
				SetAntsBack();
			}
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	if (manager.HasNoEntities())
	{
		return;
	}

	manager.Render();
	
	SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement()
{
	TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
	CollisionType collisionType = manager.CheckCollisions();
	if (collisionType == PLAYER_COIN_COLLISION)
	{
		if (!isColliding && !isCarrying)
		{
			isColliding = true;
			isCarrying = true;
		}
	}
	if (collisionType == PLAYER_DROPOFF_COLLISION)
	{
		if (!isColliding && isCarrying)
		{
			points++;
			pointDisplay.GetComponent<TextLabelComponent>()->SetLabelText("Points: " + std::to_string(points), "charriot-font");
			isColliding = true;
			isCarrying = false;
		}
	}
	if (collisionType == PLAYER_ENEMY_COLLISION)
	{
		ProcessGameOver();
	}

	if (collisionType == NO_COLLISION) { isColliding = false; }
}

void Game::ProcessNextLevel(int levelNumber)
{
	std::cout << "Next Level" << std::endl;
	isRunning = false;
}

void Game::ProcessGameOver()
{
	isPlaying = false;
	background.GetComponent<TransformComponent>()->position.x = 0;
	finalPointText.AddComponent<TextLabelComponent>(60, WINDOW_HEIGHT / 4, "YOUR SCORE WAS " + std::to_string(points) + " POINTS!!!", "charriot-font-main", WHITE_COLOR);
	quitText.AddComponent<TextLabelComponent>(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 2, "PRESS ESC TO EXIT", "charriot-font-main", WHITE_COLOR);
	pointDisplay.Destroy();
	timer.Destroy();
	background.Activate();
}

int Game::ReturnRandomInt(int min, int max)
{ 
		static bool first = true;
		if (first)
		{
			srand(time(NULL)); //seeding for the first time only!
			first = false;
		}
		return min + rand() % ((max + 1) - min);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
