#pragma once

#include "engine/Bobo.h"

#include "GameComponents/FunnyMove.h"

#include "../engine/GameState/GameStateManager.h"
#include "GameState/GameOverState.h"
#include "GameState/MainMenuState.h"
#include "GameState/PauseMenuState.h"
#include "GameState/InGameState.h"
#include "../engine/Renderer/SkyBox/Skybox.h"

class Game
{
public:
	Game()
	{
		Setup();
	}

private:
	void Setup()
	{
		/*------ BASIC SETUP ------*/
		GameStateManager::InitWithGameStates(
			{ 
				{ GameStateLabel::GAME_OVER, new GameOverState() },
				{ GameStateLabel::IN_GAME, new InGameState() },
				{ GameStateLabel::MAIN_MENU, new MainMenuState() }},
			new PauseMenuState());
		GameStateManager::EnterGameState(GameStateLabel::MAIN_MENU);

		// Create Scene
		SceneManager::CreateScene("Scene1");

		/* Example of Creating Game Object Begins */
		// Create GameObject
		auto object = new GameObject();
		
		// Add a material component and tell that material what model to use and what texture to use
		// models are all loaded in from the assets/Models directory upon game start and the same is done for textures from the assets/Textures directory
		object->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_3"));
		/* End Example */

		/* Example of Adding a Component to a Game Object */
		// Get the 'Transform' component from GameObject; Game Objects by default will be created with a Transform component attatched unless 
		// an argument is passed to the GameObject constructor saying not to - new GameObject(false)
		auto transform = object->GetComponent<Transform>();

		// Add the component; In this case, FunnyMove needs two parameters: a transform reference & a speed at which the ball will rotate
		object->AddComponent<FunnyMove>(transform, 1);
		/* End Example */

		// Making a few balls
		auto solidTwoBall = new GameObject();
		solidTwoBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_2"));
		solidTwoBall->GetComponent<Transform>()->position.x = -4;

		auto stripedNineBall = new GameObject();
		stripedNineBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_9"));
		stripedNineBall->GetComponent<Transform>()->position.x = -2;

		auto stripedTenBall = new GameObject();
		stripedTenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_10"));
		stripedTenBall->GetComponent<Transform>()->position.x = 2;

		auto eightBall = new GameObject();
		eightBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("8_ball"));
		eightBall->GetComponent<Transform>()->position.x = 4;

		// Example of Creating a GameObject with a Parent GameObject
		auto childObject = new GameObject(*object);

		/*----- SKYBOX ------*/
		//Right, Left, Top, Bottom, Front, Back
		vector<std::string> faces;
		{
			"../../assets/Textures/SkyBox_Textures/PNGS/Skybox_001.png",
				"../../assets/Textures/SkyBox_Textures/PNGS/Skybox_003.png",
				"../../assets/Textures/SkyBox_Textures/PNGS/Skybox_006.png",
				"../../assets/Textures/SkyBox_Textures/PNGS/Skybox_005.png",
				"../../assets/Textures/SkyBox_Textures/PNGS/Skybox_002.png",
				"../../assets/Textures/SkyBox_Textures/PNGS/Skybox_004.png"
		};

		SkyBox skyBox = new SkyBox(faces);

		/*------ AUDIO ------*/

		// Audio files are loaded from the assets/Sounds directory, they must be .mp3
		// The files can be accessed through a string identifier, which corresponds to
		// the file name without extensions. Case doesn't matter
		Audio::PlaySound("boom");
		Audio::PlaySound("punch");

		/*------ COROUTINES ------*/
		// Should be all self-explanatory; Just some examples
		// Wait for Seconds
		float waitTime = 3;
		auto printSomething = [=]() { Log("Printed after {} seconds.", waitTime); };
		auto c = CoroutineScheduler::StartCoroutine<WaitForSeconds>(printSomething, waitTime);

		// Wait for another Coroutine
		auto printAfter = []() { Log("Printed after time print."); };
		CoroutineScheduler::StartCoroutine<WaitForCoroutine>(printAfter, c);

		// Wait for some Condition
		auto printAfterEvaluation = []() { Log("Printed after evaluation"); };
		auto evaluator = []() { return Time::RealTimeSinceStartup() > 10; };
		CoroutineScheduler::StartCoroutine<WaitUntil>(printAfterEvaluation, evaluator);
	}
};