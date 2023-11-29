#include "../../engine/GameState/GameState.h"

#include "../../engine/Time.h"

class PauseMenuState : public GameState
{
public:
    void Enter()
    {
        // Initialize pause menu resources
        BOBO_INFO("Entered Pause Menu State");

        Time::SetTimeScale(0);
    }

    void Exit()
    {
        // Clean up pause menu resources
        BOBO_INFO("Exited Pause Menu State");

        Time::SetTimeScale(1);
    }

    void Update()
    {
        // Update pause menu logic
    }

    void Render()
    {
        // Render the pause menu to the screen
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), 0);
        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), 0);

        ImGui::Begin("Pause Menu", NULL, ImGuiHelpers::MakeFlags(true, true, true, true, true, true, true, false, false, false));

        ImGuiHelpers::MakeCenterText("Game Paused");

        ImGuiHelpers::LowerCursor();

        if (ImGuiHelpers::MakeCenterButton("Resume"))
        {
            GameStateManager::TogglePauseState();
        }

        ImGuiHelpers::LowerCursor();

        if (ImGuiHelpers::MakeCenterButton("Go to Game Over State"))
        {
            GameStateManager::EnterGameState(GameStateLabel::GAME_OVER);
        }

        ImGui::End();
    }
};