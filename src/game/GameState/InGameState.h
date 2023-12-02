#include "../../engine/GameState/GameState.h"

#include "../../engine/Notifications/NotificationManager.h"

#include <string>
#include "../../engine/Time.h"

enum Turn { P1, P2 };

class InGameState : public GameState
{
public:
    void Enter()
    {
        // Initialize game over resources
        BOBO_INFO("Entered In-Game State");

        // Set stuff
        m_SolidBallsRemaining = 8;
        m_StripedBallsRemaining = 8;
        m_ShotPower = 0.0f;

        m_Turn = Turn::P1;
    }

    void Exit()
    {
        // Clean up game over resources
        BOBO_INFO("Exited In-Game State");
    }

    void Update()
    {
        if (m_Turn != m_TurnLastUpdate)
        {
            std::string newTurn;
            if (m_Turn == Turn::P1)
            {
                newTurn = "P1";
            }
            else
            {
                newTurn = "P2";
            }
            NotificationManager::SendBannerNotification(newTurn + " Turn Start", NotificationTextColor::WHITE);
        }
        m_TurnLastUpdate = m_Turn;

        // Update game over logic, such as checking for restart or exit
        if (m_SolidBallsRemaining <= 0)
        {
            GameOverState* gameOverState = (GameOverState*)GameStateManager::FetchGameState(GameStateLabel::GAME_OVER);
            gameOverState->SetWinner("Solids");
            GameStateManager::EnterGameState(GameStateLabel::GAME_OVER);
        }

        if (m_StripedBallsRemaining <= 0)
        {
            GameOverState* gameOverState = (GameOverState*)GameStateManager::FetchGameState(GameStateLabel::GAME_OVER);
            gameOverState->SetWinner("Stripes");
            GameStateManager::EnterGameState(GameStateLabel::GAME_OVER);
        }
    }

    void Render()
    {
        // Render the game over screen to the display
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

        // Solids UI
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 25, main_viewport->WorkPos.y + 25), 0);
        ImGui::SetNextWindowSize(ImVec2(225, 80), 0);

        if (m_Turn == Turn::P1)
        {
            ImGui::StyleColorsLight();
        }
        else
        {
            ImGui::StyleColorsDark();
        }

        ImGui::Begin("P1", NULL, ImGuiHelpers::MakeFlags(false, true, true, true, true, true, true, false, false, false));

        std::string solidLabel = "Solid Balls Remaining " + std::to_string(m_SolidBallsRemaining);
        ImGuiHelpers::MakeCenterText(solidLabel);

        // Move Cursor down some
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

        if (ImGuiHelpers::MakeCenterButton("Sink Solid") && m_Turn == Turn::P1)
        {
            m_SolidBallsRemaining--;
            NotificationManager::SendDefaultNotification("A Solid Ball has been Sunk", NotificationTextColor::BLUE);
            m_Turn = Turn::P2;
        }

        ImGui::End();

        // Striped UI
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + WINDOW_WIDTH - 250, main_viewport->WorkPos.y + 25), 0);
        ImGui::SetNextWindowSize(ImVec2(225, 80), 0);

        if (m_Turn == Turn::P2)
        {
            ImGui::StyleColorsLight();
        }
        else
        {
            ImGui::StyleColorsDark();
        }

        ImGui::Begin("P2", NULL, ImGuiHelpers::MakeFlags(false, true, true, true, true, true, true, false, false, false));

        std::string stripedLabel = "Striped Balls Remaining " + std::to_string(m_StripedBallsRemaining);
        ImGuiHelpers::MakeCenterText(stripedLabel);

        // Move Cursor down some
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

        if (ImGuiHelpers::MakeCenterButton("Sink Striped") && m_Turn == Turn::P2)
        {
            m_StripedBallsRemaining--;
            NotificationManager::SendDefaultNotification("A Striped Ball has been Sunk", NotificationTextColor::RED);
            m_Turn = Turn::P1;
        }

        ImGui::End();

        // Turn UI
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + WINDOW_WIDTH - 225, main_viewport->WorkPos.y + WINDOW_HEIGHT - 50), 0);
        ImGui::SetNextWindowSize(ImVec2(200, 25), 0);

        ImGui::StyleColorsClassic();
        ImGui::Begin("Turn", NULL, ImGuiHelpers::MakeFlags(true, true, true, true, true, true, true, false, false, false));

        // Construct turn label
        std::string currentTurn;
        if (m_Turn == Turn::P1)
            currentTurn = "P1";
        else
            currentTurn = "P2";
        std::string turnLabel = "Shooting: " + currentTurn;
        ImGuiHelpers::MakeCenterText(turnLabel.c_str(), true, true);

        ImGui::End();

        // Power Bar
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + WINDOW_WIDTH / 2 - 131, main_viewport->WorkPos.y + WINDOW_HEIGHT - 200), 0);
        ImGui::SetNextWindowSize(ImVec2(262, 60), 0);

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 5.3f;
        style.WindowPadding = ImVec2(3.0f, 3.0f);

        // Increase the progress bar if space is being held down
        if (Input::GetKey(GLFW_KEY_SPACE))
        {
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
            if (m_ShotPower < 100.0f)
                m_ShotPower += 1.0f  * Time::DeltaTime();
        }
        else
        {
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.89f, 0.89f, 0.95f, 1.00f);
            m_ShotPower = 0.0f;
        }

        ImGui::Begin("Test", NULL, ImGuiHelpers::MakeFlags(true, true, true, true, true, true, true, false, false, false));

        // Construct the progress bar
        ImGui::ProgressBar(m_ShotPower, ImVec2(256.0f, 54.0f));

        ImGui::End();
    }
private:
    int m_StripedBallsRemaining;
    int m_SolidBallsRemaining;
    Turn m_Turn;
    Turn m_TurnLastUpdate;
    float m_ShotPower;
};