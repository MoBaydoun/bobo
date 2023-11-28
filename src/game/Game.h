#pragma once

#include "engine/Bobo.h"

#include "../engine/Physics/Rigidbody.h"

#include "GameComponents/FunnyMove.h"

#include "../engine/GameState/GameStateManager.h"
#include "GameState/GameOverState.h"
#include "GameState/MainMenuState.h"
#include "GameState/PauseMenuState.h"
#include "GameState/InGameState.h"

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


		/*----------physics Test ---------------*/
		auto physicsball = new GameObject();

		physicsball->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_2"));
		physicsball->AddComponent<Rigidbody>(new SphereShape(1), RVec3(0.0, 10, 0.0), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
		auto physicsBallRb = physicsball->GetComponent<Rigidbody>();
		physicsBallRb->SetTransform(physicsball->GetComponent<Transform>());
		physicsBallRb->SetOnCollision([](JPH::BodyID other) {
			std::cout << "collision happened on beautiful planet earth" << std::endl;
			});

		auto staticBall = new GameObject();

		staticBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("8_ball"));
		staticBall->AddComponent<Rigidbody>(new SphereShape(1), RVec3(0.5f, -3.0f, 0.0), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		auto staticBallRb = staticBall->GetComponent<Rigidbody>();
		staticBallRb->SetTransform(staticBall->GetComponent<Transform>());
		staticBallRb->SetOnCollisionEnd([](JPH::BodyID other) {
			std::cout << "a collision has ended in lego city" << std::endl;
			});

		// Creating point lights
		auto pointlight = new GameObject();
		Pointlight pl;
		pl.baseColor = { 0.7f, 0.3f, 0.1f }; // RGB, each value goes up to 1.0
		pl.position = { -5.0f, -5.0f, 5.0f }; // X, Y, Z (Positive Z is closer to camera)
		pl.intensity = 250.0f;
		pointlight->AddComponent<PointlightComponent>(pl);

		auto spotlight = new GameObject();
		Spotlight sl;
		sl.baseColor = { 0.7, 0.7, 0.7 }; // RGB, same as before
		sl.cutoffAngle = 45.0f; // The radius of the cone
		sl.direction = { 0.0f, -1.0f, 0.0f }; // Direction of the light
		sl.position = { 0.0f, 5.0f, 0.0f }; // X, Y, Z
		spotlight->AddComponent<SpotlightComponent>(sl);

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