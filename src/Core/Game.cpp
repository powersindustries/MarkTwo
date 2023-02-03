#include "Game.h"
#include "GameGlobals.h"
#include "Game/Player/Player.h"
#include "Systems/Logging.h"
#include "Game/Managers/LoadManager.h"
#include "Game/Managers/UIManager.h"
#include "Game/Managers/EventManager.h"
#include "Managers/SettingsManager.h"

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

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Game was created.");
}


// -------------------------------------------------------
// -------------------------------------------------------
Game::~Game()
{
    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Game was destroyed.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::InitializeSession()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Error with SDL_Init.");
        return;
    }

    if (TTF_Init() != 0)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Error with TTF_Init.");
        return;
    }

    // Initialize game settings.
    CoreManagers::g_SettingsManager.InitializeSettings();


    // Create Window.
    m_Window = SDL_CreateWindow(
        CoreManagers::g_SettingsManager.GetTitle().c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CoreManagers::g_SettingsManager.GetScreenWidth(),
        CoreManagers::g_SettingsManager.GetScreenHeight(),
        SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Window did not work.");
        return;
    }

    // -1 is default driver
    m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

    if (!m_Renderer)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Renderer did not work.");
        return;
    }

    // Do initial loading stuff here
    g_EventManager.InitializeEvents();
    g_LoadManager.InitialLoad(m_Renderer);
    g_Player.InitializePlayer();
    g_UIManager.InitializeUIScreens();

    g_GameGlobals.m_bGameRunning = true;

    return;
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
    CoreManagers::g_InputManager.ProcessInputs();
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


    // Update Loop here
    int sdlTicks = SDL_GetTicks();
    float deltaTime = (sdlTicks - m_iTicksLastFrame) / 1000.0f;
    m_iTicksLastFrame = sdlTicks;


    // Turn On/Off Pause Screen
    if (CoreManagers::g_InputManager.GetActionPressed(CoreManagers::InputMappings::eESCMenu))
    {
        g_GameGlobals.m_bGamePaused = !g_GameGlobals.m_bGamePaused;
        g_UIManager.ActivatePauseMenu();
    }

    // Turn on/off debug collision textures with F1 key
    if (CoreManagers::g_InputManager.GetActionPressed(CoreManagers::InputMappings::eDebug1))
    {
        g_GameGlobals.m_bGraphicsDebugMode = !g_GameGlobals.m_bGraphicsDebugMode;
    }


    // Update Managers
    g_LoadManager.Update(deltaTime);

    if (!g_GameGlobals.m_bGamePaused)
    {
        g_Player.Update(deltaTime);
    }

    g_UIManager.Update();
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


    if (!g_GameGlobals.m_bGamePaused)
    {
        g_Player.Draw(m_Renderer);
    }

    g_UIManager.Draw(m_Renderer);


    SDL_RenderPresent(m_Renderer);
}

}