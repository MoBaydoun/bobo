#pragma once

#include "engine/Bobo.h"

#include "../engine/Physics/Rigidbody.h"

#include "GameComponents/FunnyMove.h"
#include "GameComponents/ObjectTag.h"
#include "GameComponents/GameManager.h"

#include "../engine/GameState/GameStateManager.h"
#include "GameState/GameOverState.h"
#include "GameState/MainMenuState.h"
#include "GameState/PauseMenuState.h"
#include "GameState/InGameState.h"

#include "../engine/Notifications/NotificationManager.h"
#include "../engine/Popups/PopupManager.h"

class Game
{
public:
	Game()
	{
		Setup();
	}

private:

	// Constants for objects position / rotation / scale
	const glm::vec3 m_tablePosition = glm::vec3{ 0, -1.5, -4.5 };
	const glm::vec3 m_ballScale = glm::vec3{ 0.2, 0.2, 0.2 };
	const glm::vec3 m_firstBallPos = glm::vec3{ m_tablePosition.x, m_tablePosition.y + 0.1, m_tablePosition.z - 1 };
	const float m_ballDistance = .42;
	// other game objects
	GameObject* cueball;

	void SetBallPos(GameObject* ball, float xOffset, float zOffset)
	{
		ball->GetComponent<Transform>()->position = m_firstBallPos;
		ball->GetComponent<Transform>()->position.x += xOffset;
		ball->GetComponent<Transform>()->position.z += zOffset;
		ball->GetComponent<Transform>()->scale = m_ballScale;
		ball->GetComponent<Transform>()->rotation.y = -glm::pi<float>()/2;
		ball->GetComponent<Transform>()->rotation.z = glm::pi<float>() / 2;
	}

	// setting up balls initial positions
	void BallsSetup()
	{
		Ref<SphereShape> s = new SphereShape(0.2);
		s->SetDensity(400);

		// 1st row
		auto solidOneBall = new GameObject();
		solidOneBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_1"));
		solidOneBall->GetComponent<Transform>()->position = m_firstBallPos;
		solidOneBall->GetComponent<Transform>()->scale = m_ballScale;
		solidOneBall->AddComponent<ObjectTag>("solid");
		addRigidBodyToBall(solidOneBall, s);
		// 2nd row
		auto StripedNineBall = new GameObject();
		StripedNineBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_9"));
		StripedNineBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedNineBall, -0.5 * m_ballDistance, -m_ballDistance);
		addRigidBodyToBall(StripedNineBall, s);
		//
		auto SolidTwoBall = new GameObject();
		SolidTwoBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_2"));
		SolidTwoBall->AddComponent<ObjectTag>("solid");
		SetBallPos(SolidTwoBall, 0.5 * m_ballDistance, -m_ballDistance);
		addRigidBodyToBall(SolidTwoBall, s);
		// 3rd row
		auto StripedTenBall = new GameObject();
		StripedTenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_10"));
		StripedTenBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedTenBall, -m_ballDistance, -2 * m_ballDistance);
		addRigidBodyToBall(StripedTenBall, s);
		//
		auto SolidEightBall = new GameObject();
		SolidEightBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("8_ball"));
		SolidEightBall->AddComponent<ObjectTag>("8ball");
		SetBallPos(SolidEightBall, 0, -2 * m_ballDistance);
		addRigidBodyToBall(SolidEightBall, s);
		//
		auto SolidThreeBall = new GameObject();
		SolidThreeBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_3"));
		SolidThreeBall->AddComponent<ObjectTag>("solid");
		SetBallPos(SolidThreeBall, m_ballDistance, -2 * m_ballDistance);
		addRigidBodyToBall(SolidThreeBall, s);
		// 4th row 
		auto StripedElevenBall = new GameObject();
		StripedElevenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_11"));
		StripedElevenBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedElevenBall, -1.5 * m_ballDistance, -3 * m_ballDistance);
		addRigidBodyToBall(StripedElevenBall, s);
		//
		auto SolidSevenBall = new GameObject();
		SolidSevenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_7"));
		SolidSevenBall->AddComponent<ObjectTag>("solid");
		SetBallPos(SolidSevenBall, -0.5 * m_ballDistance, -3 * m_ballDistance);
		addRigidBodyToBall(SolidSevenBall, s);
		//
		auto StripedFourteenBall = new GameObject();
		StripedFourteenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_14"));
		StripedFourteenBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedFourteenBall, 0.5 * m_ballDistance, -3 * m_ballDistance);
		addRigidBodyToBall(StripedFourteenBall, s);
		//
		auto SolidFourBall = new GameObject();
		SolidFourBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_4"));
		SolidFourBall->AddComponent<ObjectTag>("solid");
		SetBallPos(SolidFourBall, 1.5 * m_ballDistance, -3 * m_ballDistance);
		addRigidBodyToBall(SolidFourBall, s);
		// 5th row
		auto SolidFiveBall = new GameObject();
		SolidFiveBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_5"));
		SolidFiveBall->AddComponent<ObjectTag>("solid");
		SetBallPos(SolidFiveBall, -2 * m_ballDistance, -4 * m_ballDistance);
		addRigidBodyToBall(SolidFiveBall, s);
		//
		auto StripedThirteenBall = new GameObject();
		StripedThirteenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_13"));
		StripedThirteenBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedThirteenBall, -1 * m_ballDistance, -4 * m_ballDistance);
		addRigidBodyToBall(StripedThirteenBall, s);
		//
		auto StripedFifteenBall = new GameObject();
		StripedFifteenBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_15"));
		StripedFifteenBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedFifteenBall, 0, -4 * m_ballDistance);
		addRigidBodyToBall(StripedFifteenBall, s);
		//
		auto SolidSixBall = new GameObject();
		SolidSixBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("solid_6"));
		SolidSixBall->AddComponent<ObjectTag>("solid");
		SetBallPos(SolidSixBall, m_ballDistance, -4 * m_ballDistance);
		addRigidBodyToBall(SolidSixBall, s);
		//
		auto StripedTwelveBall = new GameObject();
		StripedTwelveBall->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("striped_12"));
		StripedTwelveBall->AddComponent<ObjectTag>("striped");
		SetBallPos(StripedTwelveBall, 2 * m_ballDistance, -4 * m_ballDistance);
		addRigidBodyToBall(StripedTwelveBall, s);
		// cue ball
		cueball = new GameObject();
		cueball->AddComponent<Material>(ModelLoader::GetModel("ball"), TextureLoader::GetTexture("white"));
		cueball->GetComponent<Transform>()->position = m_firstBallPos + glm::vec3(0, 0, 3);
		cueball->GetComponent<Transform>()->scale = glm::vec3(.2, .2, .2);
		cueball->AddComponent<ObjectTag>("cueBall");
		Ref<SphereShape> s2 = new SphereShape(0.2);
		s2->SetDensity(600);
		addRigidBodyToBall(cueball, s2);
	}

	void addRigidBodyToBall(GameObject *ball, Ref<SphereShape> s) 
	{
		auto transform = ball->GetComponent<Transform>();
		ball->AddComponent<Rigidbody>(s, transform->position, Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
		ball->GetComponent<Rigidbody>()->SetTransform(transform);
		ball->GetComponent<Rigidbody>()->SetBounce(0.4);
		ball->GetComponent<Rigidbody>()->SetFriction(.4);
	}

	void CreateHoleTriggers(float xOffset, float zOffset)
	{
		// create and set the trigger box for a hole
		auto triggerBox = new GameObject();
		triggerBox->GetComponent<Transform>()->scale = glm::vec3{ 0.15,.2, 0.15 };
		triggerBox->GetComponent<Transform>()->position = m_firstBallPos + glm::vec3(xOffset, 0, zOffset);
		triggerBox->AddComponent<Rigidbody>(new BoxShape(RVec3{ 0.15,.25, 0.15 }),
			triggerBox->GetComponent<Transform>()->position, Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING, nullptr, true);
		auto triggerBoxRb = triggerBox->GetComponent<Rigidbody>();
		triggerBoxRb->SetTransform(triggerBox->GetComponent<Transform>());
		triggerBoxRb->SetOnCollision([](JPH::BodyID other) {
			Entity en = Physics::GetInstance()->GetEntityFromJoltRb(other);
			auto scene = SceneManager::GetActiveScene();
			auto objects = scene->GetComponentsOfType<GameManager>();
			string balltag;
			// get balls tag that is either "striped" or "solid" 
			if (scene->GetComponent<ObjectTag>(en)) {
				balltag = scene->GetComponent<ObjectTag>(en)->tag;
			}
			for (auto& object : objects)
			{
				// decrease striped or solid ball amount when it is sunk
				if (balltag == "striped")
				{
					object->stripesAmount -= 1;
					auto rb = scene->GetComponent<Rigidbody>(en);
					auto transform = scene->GetComponent<Transform>(en);
					transform->position = glm::vec3{ 100,100,100 };
					rb->DisableBody();
					//scene->DestroyEntity(en);
					NotificationManager::SendAlphaBannerNotification("A striped ball was sunk!", NotificationTextColor::GREEN);
				}
				else if (balltag == "solid")
				{
					object->solidsAmount -= 1;
					auto rb = scene->GetComponent<Rigidbody>(en);
					auto transform = scene->GetComponent<Transform>(en);
					transform->position = glm::vec3{ 100,100,100 };
					rb->DisableBody();
					//scene->DestroyEntity(en);
					NotificationManager::SendAlphaBannerNotification("A solid ball was sunk!", NotificationTextColor::GREEN);
				}
			}

			});
	}

	void TableRigidBodySetUp()
	{
		// table creation
		auto table = new GameObject();
		table->AddComponent<Material>(ModelLoader::GetModel("Pool_Table"), TextureLoader::GetTexture("Table_Top"));
		auto tableTransform = table->GetComponent<Transform>();
		tableTransform->position = m_tablePosition;
		table->AddComponent<Rigidbody>(new BoxShape(RVec3(4.2, .25, 6.5)), tableTransform->position, Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		table->GetComponent<Rigidbody>()->SetFriction(.4);

		// adding table sides
		auto tableSide1 = new GameObject();
		auto tableSide2 = new GameObject();
		auto tableSide3 = new GameObject();
		auto tableSide4 = new GameObject();
		tableSide1->AddComponent<Rigidbody>(new BoxShape(RVec3(.5, 10, 6.5)), tableTransform->position + glm::vec3(4.6, 0, 0), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		tableSide2->AddComponent<Rigidbody>(new BoxShape(RVec3(.5, 10, 6.5)), tableTransform->position + glm::vec3(-4.6, 0, 0), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		tableSide3->AddComponent<Rigidbody>(new BoxShape(RVec3(4.2, 10, .5)), tableTransform->position + glm::vec3(0, 0, 6.5), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		tableSide4->AddComponent<Rigidbody>(new BoxShape(RVec3(4.2, 10, .5)), tableTransform->position + glm::vec3(0, 0, -6.5), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		tableSide1->GetComponent<Rigidbody>()->SetFriction(0);
		tableSide1->GetComponent<Rigidbody>()->SetBounce(1);
		tableSide2->GetComponent<Rigidbody>()->SetFriction(0);
		tableSide2->GetComponent<Rigidbody>()->SetBounce(1);
		tableSide3->GetComponent<Rigidbody>()->SetFriction(0);
		tableSide3->GetComponent<Rigidbody>()->SetBounce(1);
		tableSide4->GetComponent<Rigidbody>()->SetFriction(0);
		tableSide4->GetComponent<Rigidbody>()->SetBounce(1);

		// adding hole trigger areas at (x, z) positions
		CreateHoleTriggers(4.01, 1);
		CreateHoleTriggers(-4.01, 1);
		CreateHoleTriggers(4.01, 6.9);
		CreateHoleTriggers(-4.01, 6.9);
		CreateHoleTriggers(4.01, -4.9);
		CreateHoleTriggers(-4.01, -4.9);
	}

	// Setting up the scene models
	void SceneSetup() 
	{
		//// display line creation
		//auto shotIndicator = new GameObject();
		//shotIndicator->AddComponent<Material>(ModelLoader::GetModel("cube"), TextureLoader::GetTexture("8_ball"));
		//shotIndicator->GetComponent<Transform>()->scale = glm::vec3{ 0.05,0.05,1 };
		//shotIndicator->GetComponent<Transform>()->position = m_firstBallPos + glm::vec3(0, 0.35, 3) + glm::vec3(0, 0, -1);
		//shotIndicator->GetComponent<Transform>()->rotation = glm::vec3(0, 0, 0);
		//shotIndicator->AddComponent<ObjectTag>("cue");
		// cue creation
		auto cue = new GameObject();
		cue->AddComponent<Material>(ModelLoader::GetModel("pool_cue"), TextureLoader::GetTexture("cue"));
		cue->GetComponent<Transform>()->position = m_firstBallPos + glm::vec3(0, 1.3, 6);;
		cue->GetComponent<Transform>()->rotation = glm::vec3{ -0.3, 0, 0 };
		cue->GetComponent<Transform>()->scale = glm::vec3{ 0.7, 0.7, 0.7 };

		// lamp creation
		auto lamp = new GameObject();
		lamp->AddComponent<Material>(ModelLoader::GetModel("lamp"), TextureLoader::GetTexture("lamp"));
		lamp->GetComponent<Transform>()->position = m_tablePosition;
		lamp->GetComponent<Transform>()->position += glm::vec3{ 0, 5, 0 };

		auto spotlight = new GameObject();
		Spotlight sl;
		sl.baseColor = { 0.7, 0.7, 0.7 }; // RGB, same as before
		sl.cutoffAngle = 50.0f; // The radius of the cone
		sl.direction = { 0.0f, -1.0f, 0.0f }; // Direction of the light
		sl.position = lamp->GetComponent<Transform>()->position; // X, Y, Z
		spotlight->AddComponent<SpotlightComponent>(sl);

		// bookshelves creation
		auto shelf1 = new GameObject();
		shelf1->AddComponent<Material>(ModelLoader::GetModel("book_shelf"), TextureLoader::GetTexture("wood"));
		shelf1->GetComponent<Transform>()->position = m_tablePosition;
		shelf1->GetComponent<Transform>()->position += glm::vec3{ -7, 3, -20 };
		shelf1->GetComponent<Transform>()->rotation = glm::vec3{ 0, -glm::pi<float>() / 2, 0 };
		auto shelf2 = new GameObject();
		shelf2->AddComponent<Material>(ModelLoader::GetModel("book_shelf"), TextureLoader::GetTexture("wood"));
		shelf2->GetComponent<Transform>()->position = m_tablePosition;
		shelf2->GetComponent<Transform>()->position += glm::vec3{ 7, 3, -20 };
		shelf2->GetComponent<Transform>()->rotation = glm::vec3{ 0, -glm::pi<float>() / 2, 0 };

		// chairs creation
		auto chair1 = new GameObject();
		chair1->AddComponent<Material>(ModelLoader::GetModel("chair_1"));
		chair1->GetComponent<Transform>()->position = m_tablePosition;
		chair1->GetComponent<Transform>()->position += glm::vec3{ 7, 0, 0 };
		chair1->GetComponent<Transform>()->rotation = glm::vec3{ 0, glm::pi<float>() / 4, 0 };
		auto chair2 = new GameObject();
		chair2->AddComponent<Material>(ModelLoader::GetModel("chair_2"));
		chair2->GetComponent<Transform>()->position = m_tablePosition;
		chair2->GetComponent<Transform>()->position += glm::vec3{ -7, 0, 0 };
		chair2->GetComponent<Transform>()->rotation = glm::vec3{ 0, glm::pi<float>(), 0 };



		auto floatingIsland = new GameObject();
		floatingIsland->AddComponent<Material>(ModelLoader::GetModel("floatingisland"), TextureLoader::GetTexture("floatingislandtexture"));
		floatingIsland->GetComponent<Transform>()->position = m_tablePosition;
		floatingIsland->GetComponent<Transform>()->position += glm::vec3{ 0, -7.5, -5 };


		// setup initial balls position and rigidbody
		//BallsSetup();
		SetUpWalls();
		TableRigidBodySetUp();
	}


	void SetUpWalls() 
	{
		Ref<BoxShape> b = new BoxShape(JPH::Vec3(1,5,10));
		b->SetDensity(400);
		
		Ref<BoxShape> floorB = new BoxShape(JPH::Vec3(25, 1, 25));


		Ref<SphereShape> s = new SphereShape(2);
		s->SetDensity(5000);

		// 1st row
		auto rightball = new GameObject();
		rightball->GetComponent<Transform>()->position = glm::vec3(7,5,-9);
		rightball->GetComponent<Transform>()->scale = glm::vec3(2,2,2);
		rightball->AddComponent<ObjectTag>("solid");
		addRigidBodyToBall(rightball, s);
		rightball->GetComponent<Rigidbody>()->AddLinearVelocity(JPH::Vec3(80,0,0));
		
		
		auto leftBall = new GameObject();
		leftBall->GetComponent<Transform>()->position = glm::vec3(-7,5,-9);
		leftBall->GetComponent<Transform>()->scale = glm::vec3(2,2,2);
		leftBall->AddComponent<ObjectTag>("solid");
		addRigidBodyToBall(leftBall, s);
		leftBall->GetComponent<Rigidbody>()->AddLinearVelocity(JPH::Vec3(-80,0,0));

		auto backBall = new GameObject();
		backBall->GetComponent<Transform>()->position = glm::vec3(0,5,-14);
		backBall->GetComponent<Transform>()->scale = glm::vec3(2,2,2);
		backBall->AddComponent<ObjectTag>("solid");
		addRigidBodyToBall(backBall, s);
		backBall->GetComponent<Rigidbody>()->AddLinearVelocity(JPH::Vec3(0,0,-80));


		auto floor = new GameObject();
		floor->AddComponent<Material>(ModelLoader::GetModel("floor"), TextureLoader::GetTexture("floor"));
		floor->GetComponent<Transform>()->position = m_tablePosition;
		floor->GetComponent<Transform>()->position += glm::vec3{ 0, -7.5, -5 };

		auto groundbox = new GameObject();
		//groundbox->AddComponent<Material>(ModelLoader::GetModel("cube2"), TextureLoader::GetTexture("brick"));
		groundbox->GetComponent<Transform>()->position = m_tablePosition;
		groundbox->GetComponent<Transform>()->position += glm::vec3{ 0, -6, -5 };
		auto transform = groundbox->GetComponent<Transform>();
		groundbox->AddComponent<Rigidbody>(floorB, transform->position, Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		groundbox->GetComponent<Rigidbody>()->SetTransform(transform);

		
		auto rightwallPos = glm::vec3{20,-6,-5};

		auto wallR1 = new GameObject();
		wallR1->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallR1->GetComponent<Transform>()->position = m_tablePosition;
		wallR1->GetComponent<Transform>()->position += rightwallPos + glm::vec3(0,6,-10);
		addRigidbodyToWall(wallR1, b);

		auto wallR2 = new GameObject();
		wallR2->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallR2->GetComponent<Transform>()->position = m_tablePosition;
		wallR2->GetComponent<Transform>()->position += rightwallPos + glm::vec3(0,6,10);
		addRigidbodyToWall(wallR2, b);


		auto wallR3 = new GameObject();
		wallR3->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallR3->GetComponent<Transform>()->position = m_tablePosition;
		wallR3->GetComponent<Transform>()->position += rightwallPos + glm::vec3(0,16,10);
		addRigidbodyToWall(wallR3, b);


		auto wallR4 = new GameObject();
		wallR4->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallR4->GetComponent<Transform>()->position = m_tablePosition;
		wallR4->GetComponent<Transform>()->position += rightwallPos + glm::vec3(0,16,-10);;
		addRigidbodyToWall(wallR4, b);


		auto leftwallPos = glm::vec3{-20,-6,-5};

		auto wallL1 = new GameObject();
		wallL1->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallL1->GetComponent<Transform>()->position = m_tablePosition;
		wallL1->GetComponent<Transform>()->position += leftwallPos + glm::vec3(0,6,-10);
		addRigidbodyToWall(wallL1, b);

		auto wallL2 = new GameObject();
		wallL2->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallL2->GetComponent<Transform>()->position = m_tablePosition;
		wallL2->GetComponent<Transform>()->position += leftwallPos + glm::vec3(0,6,10);
		addRigidbodyToWall(wallL2, b);


		auto wallL3 = new GameObject();
		wallL3->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallL3->GetComponent<Transform>()->position = m_tablePosition;
		wallL3->GetComponent<Transform>()->position += leftwallPos + glm::vec3(0,16,10);
		addRigidbodyToWall(wallL3, b);


		auto wallL4 = new GameObject();
		wallL4->AddComponent<Material>(ModelLoader::GetModel("wallpiece"), TextureLoader::GetTexture("brick"));
		wallL4->GetComponent<Transform>()->position = m_tablePosition;
		wallL4->GetComponent<Transform>()->position += leftwallPos + glm::vec3(0,16,-10);;
		addRigidbodyToWall(wallL4, b);



		auto backwallpos = glm::vec3{0,-6,-24};
		Ref<BoxShape> b2 = new BoxShape(JPH::Vec3(10,5,1));
		b2->SetDensity(400);

		auto wallB1 = new GameObject();
		wallB1->AddComponent<Material>(ModelLoader::GetModel("backwallpiece"), TextureLoader::GetTexture("brick"));
		wallB1->GetComponent<Transform>()->position = m_tablePosition;
		wallB1->GetComponent<Transform>()->position += backwallpos + glm::vec3(-10,6,0);
		addRigidbodyToWall(wallB1, b2);

		auto wallB2 = new GameObject();
		wallB2->AddComponent<Material>(ModelLoader::GetModel("backwallpiece"), TextureLoader::GetTexture("brick"));
		wallB2->GetComponent<Transform>()->position = m_tablePosition;
		wallB2->GetComponent<Transform>()->position += backwallpos + glm::vec3(10,6,0);
		addRigidbodyToWall(wallB2, b2);


		auto wallB3 = new GameObject();
		wallB3->AddComponent<Material>(ModelLoader::GetModel("backwallpiece"), TextureLoader::GetTexture("brick"));
		wallB3->GetComponent<Transform>()->position = m_tablePosition;
		wallB3->GetComponent<Transform>()->position += backwallpos + glm::vec3(10,16,0);
		addRigidbodyToWall(wallB3, b2);


		auto wallB4 = new GameObject();
		wallB4->AddComponent<Material>(ModelLoader::GetModel("backwallpiece"), TextureLoader::GetTexture("brick"));
		wallB4->GetComponent<Transform>()->position = m_tablePosition;
		wallB4->GetComponent<Transform>()->position += backwallpos + glm::vec3(-10,16,0);;
		addRigidbodyToWall(wallB4, b2);

	}



	void addRigidbodyToWall(GameObject *wall, Ref<BoxShape> b) 
	{
		auto transform = wall->GetComponent<Transform>();
		wall->AddComponent<Rigidbody>(b, transform->position, Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
		wall->GetComponent<Rigidbody>()->SetTransform(transform);
		auto wallRb = wall->GetComponent<Rigidbody>();
	}

	

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

		// setup the game manager for holding game info like striped and solid balls remaining
		auto gameManager = new GameObject();
		gameManager->AddComponent<GameManager>();
		gameManager->AddComponent<ObjectTag>("gamemanager");

		// Setting up initial scene
		SceneSetup();

		// Creating point lights
		auto pointlight = new GameObject();
		Pointlight pl;
		pl.baseColor = { 0.7f, 0.3f, 0.1f }; // RGB, each value goes up to 1.0
		pl.position = { -5.0f, -5.0f, 5.0f }; // X, Y, Z (Positive Z is closer to camera)
		pl.intensity = 250.0f;
		pointlight->AddComponent<PointlightComponent>(pl);

		PopupManager::MakePopup(
			"Welcome",
			"Hey there Gamer! (Derogatory)",
			ImVec2(250, 85),
			AnchorPos::CENTER_CENTER,
			ImVec2(0, 0));

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