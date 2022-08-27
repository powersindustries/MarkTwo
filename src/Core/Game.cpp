#include "Game.h"
#include "GameGlobals.h"
#include "Game/Player/Player.h"
#include "Systems/Logging.h"
#include "Game/Managers/LoadManager.h"
#include "Game/Managers/UIManager.h"
#include "Game/Managers/InputManager.h"
#include "Game/Managers/EventManager.h"

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

    m_Window = SDL_CreateWindow(
        g_GameGlobals.TITLE_NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        g_GameGlobals.WINDOW_WIDTH,
        g_GameGlobals.WINDOW_HEIGHT,
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
    g_InputManager.Refresh();

    while (SDL_PollEvent(&g_GameGlobals.m_SDLEvent))
    {
        switch (g_GameGlobals.m_SDLEvent.type)
        {
        case SDL_QUIT:
        {
            g_GameGlobals.m_bGameRunning = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            g_InputManager.ManageKeyState(g_GameGlobals.m_SDLEvent.key);
            break;
        }
        case SDL_KEYUP:
        {
            if (g_GameGlobals.m_SDLEvent.key.keysym.sym == SDLK_BACKSPACE)
            {
                g_GameGlobals.m_bGameRunning = false;
            }

            g_InputManager.RefreshKeyboardState(g_GameGlobals.m_SDLEvent.key);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            g_InputManager.ManageMouseButtonState(g_GameGlobals.m_SDLEvent.button);
            break;
        }
        default:
            break;
        }
    }
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
    if (g_InputManager.m_KeyboardPressedData.m_Escape)
    {
        g_GameGlobals.m_bGamePaused = !g_GameGlobals.m_bGamePaused;
        g_UIManager.ActivatePauseMenu();
    }

    // Turn on/off debug collision textures with F1 key
    if (g_InputManager.m_KeyboardPressedData.m_F1)
    {
        g_GameGlobals.m_bGraphicsDebugMode = !g_GameGlobals.m_bGraphicsDebugMode;
    }


    // Update Managers
    g_LoadManager.Update(&deltaTime);

    if (!g_GameGlobals.m_bGamePaused)
    {
        g_Player.Update(&deltaTime);
    }

    g_UIManager.Update();


    // Update stored last SDL_Event
    g_GameGlobals.m_PreviousSDLEvent = g_GameGlobals.m_SDLEvent;
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