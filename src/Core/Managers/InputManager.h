#ifndef InputManager_h
#define InputManager_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace Core
{

enum class InputMappings
{
    // Mouse Actions.
    eMouse1,
    eMouse2,
    eMouse3,
    eMouseMotion,

    // Navigation Actions.
    eRight,
    eLeft,
    eUp,
    eDown,
    eRun,

    // Gameplay Actions.
    eInteract,
    eAction,

    // System Actions.
    eESCMenu,
    eTabMenu,

    // Debug Actions.
    eDebug1,
    eDebug2,
    eDebug3,
    eDebug4,

};

struct InputMappingsData
{
    // Debug Keys.
    bool m_bF1 = false;
    bool m_bF2 = false;
    bool m_bF3 = false;
    bool m_F4 = false;

    // Mouse Actions.
    bool m_bLeftClicked = false;
    bool m_bRightClicked = false;
    bool m_bMiddleClicked = false;
    bool m_bMouseMotion = false;

    // System Keys.
    bool m_bEscape = false;
    bool m_bTab = false;

    // Player Keys.
    bool m_bUpArrow = false;
    bool m_bDownArrow = false;
    bool m_bLeftArrow = false;
    bool m_bRightArrow = false;
    bool m_bW = false;
    bool m_bA = false;
    bool m_bS = false;
    bool m_bD = false;

    bool m_bSpace = false;

    // Gameplay Keys.
    bool m_bE = false;
    bool m_bJ = false;
};

struct HeldInputMappingsData
{
    InputMappingsData m_InputMappingData;

    // Debug Keys.
    int64_t m_F1Stamp = -1;
    int64_t m_F2Stamp = -1;
    int64_t m_F3Stamp = -1;
    int64_t m_F4Stamp = -1;

    // Mouse Actions.
    int64_t m_LeftClickedStamp = -1;
    int64_t m_RightClickedStamp = -1;
    int64_t m_MiddleClickedStamp = -1;

    // System Keys.
    int64_t m_EscapeStamp = -1;
    int64_t m_TabStamp = -1;

    // Player Keys.
    int64_t m_UpArrowStamp = -1;
    int64_t m_DownArrowStamp = -1;
    int64_t m_LeftArrowStamp = -1;
    int64_t m_RightArrowStamp = -1;
    int64_t m_WStamp = -1;
    int64_t m_AStamp = -1;
    int64_t m_SStamp = -1;
    int64_t m_DStamp = -1;

    int64_t m_SpaceStamp = -1;

    // Gameplay Keys.
    int64_t m_EStamp = -1;
    int64_t m_JStamp = -1;
};

struct MouseMotionData
{
    int8_t m_iMotionX = 0;
    int8_t m_iMotionY = 0;
};

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void ProcessInputs();

    bool GetActionPressed(const InputMappings& mapping);
    bool GetActionHeld(const InputMappings& mapping);
    int64_t GetActionHeldTimestamp(const InputMappings& mapping);

    const MouseMotionData& GetMouseMotionData() const { return m_MouseMotionData; }

    bool GetMouseClickAbsorbedByUI() { return m_bMouseClickAbsorbedByUI; };
    void SetMouseClickAbsorbedByUI(const bool absorbed) { m_bMouseClickAbsorbedByUI = absorbed; };


private:

    void ResetAllPressedData();

    void OnKeyUpEvent();
    void OnMouseEvent();
    void OnKeyDownEvent();


private:

    SDL_Event* m_SDLEvent;

    InputMappingsData m_InputMappingPressedData;
    HeldInputMappingsData m_InputMappingHeldData;
    MouseMotionData m_MouseMotionData;

    bool m_bMouseClickAbsorbedByUI;

};

extern InputManager g_InputManager;

}

#endif