#include "Game.h"
#include "GameGlobals.h"
#include "Game/Player/Player.h"
#include "Systems/Logging.h"
#include "Game/Managers/FrontendManager.h"
#include "Game/Managers/EventManager.h"
#include "Managers/SettingsManager.h"
#include "Managers/AssetManager.h"
#include "Core/UI/Types/StyleTypes.h"
#include "Game/Managers/MapManager.h"
#include "Core/UI/UIManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Renderer* Game::m_Renderer;
GameGlobals g_GameGlobals;


// -------------------------------------------------------
// -------------------------------------------------------
Game::Game()
{
    m_Window = nullptr;
    m_iTicksLastFrame = 0;

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Game was created.");
}


// -------------------------------------------------------
// -------------------------------------------------------
Game::~Game()
{
    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Game was destroyed.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::InitializeSession()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Error with SDL_Init.");
        return;
    }

    if (TTF_Init() != 0)
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Error with TTF_Init.");
        return;
    }

    // Initialize game settings.
    Core::g_SettingsManager.Initialize();

    // Create Window.
    m_Window = SDL_CreateWindow(
        Core::g_SettingsManager.GetTitle().c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Core::g_SettingsManager.GetScreenWidth(),
        Core::g_SettingsManager.GetScreenHeight(),
        SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Window did not work.");
        return;
    }

    // -1 is default driver
    m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

    if (!m_Renderer)
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Renderer did not work.");
        return;
    }

    // Initialization.
    Core::g_AssetManager.Initialize(m_Renderer);
    UI::g_UIManager.Initialize();

    g_MapManager.Initialize();
    g_Player.Initialize();
    g_FrontendManager.Initialize();

    g_GameGlobals.m_bGameRunning = true;

}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::EndSession()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::ProcessInputs()
{
    Core::g_InputManager.ProcessInputs();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::Update()
{
    // Wait 16ms since last frame to reach 60fps
    int timeToWait = g_GameGlobals.FRAME_TARGET_TIME - (SDL_GetTicks() - m_iTicksLastFrame);

    if (timeToWait > 0 && timeToWait <= g_GameGlobals.FRAME_TARGET_TIME)
    {
        SDL_Delay(timeToWait);
    }


    int sdlTicks = SDL_GetTicks();
    float deltaTime = (sdlTicks - m_iTicksLastFrame) / 1000.0f;
    m_iTicksLastFrame = sdlTicks;


    // Turn On/Off Pause Screen
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eESCMenu))
    {
        g_GameGlobals.m_bGamePaused = !g_GameGlobals.m_bGamePaused;
        if (g_FrontendManager.GetActiveScreenId() == g_FrontendManager.GetPauseMenuScreenId())
        {
            g_FrontendManager.RemoveScreen(g_FrontendManager.GetPauseMenuScreenId());
        }
        else
        {
            g_FrontendManager.ActivateScreen(g_FrontendManager.GetPauseMenuScreenId());
        }
    }

    // Turn on/off debug collision textures with F1 key
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eDebug1))
    {
        g_GameGlobals.m_bGraphicsDebugMode = !g_GameGlobals.m_bGraphicsDebugMode;
    }

    // Trigger UI hot reload F2 key.
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eDebug2))
    {
        g_UIManager.DEBUG_HOTRELOAD();
    }


    // Update Managers
    if (!g_GameGlobals.m_bGamePaused)
    {
        g_Player.Update(deltaTime);
    }

    g_FrontendManager.Update();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::Draw()
{
    SDL_SetRenderDrawColor(m_Renderer, 
    g_GameGlobals.COLOR_AQUA.r,
    g_GameGlobals.COLOR_AQUA.g,
    g_GameGlobals.COLOR_AQUA.b,
    g_GameGlobals.COLOR_AQUA.a);

    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

    g_MapManager.Draw(m_Renderer);
 
    if (!g_GameGlobals.m_bGamePaused)
    {
        g_Player.Draw(m_Renderer);
    }

    g_FrontendManager.Draw(m_Renderer);


    SDL_RenderPresent(m_Renderer);
}

}