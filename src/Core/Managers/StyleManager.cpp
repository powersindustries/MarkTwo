#include "StyleManager.h"
#include <vector>

#include "GameGlobals.h"
#include "../Systems/Logging.h"
#include "../Systems/Hash.h"
#include "../Types/LuaTableLoader.h"

namespace CoreManagers
{


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager g_StyleManager;


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager::StyleManager()
{
    m_sStyleFilepath.append(__PROJECT_DIRECTORY__);
    m_sStyleFilepath.append("/src/Data/Styles.lua");
}


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager::~StyleManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StyleManager::InitializeStyleManager()
{
    CoreTypes::LuaTableLoader* luaLoader = new CoreTypes::LuaTableLoader(m_sStyleFilepath);

    // Load TextBlock Styles.
    luaLoader->LoadTableByID("TextBlocks");

    const uint8_t uiTextblockTableSize = luaLoader->GetCurrentTableSize();
    for (uint8_t x=0; x < uiTextblockTableSize; ++x)
    {
        int indexOffset = x + 1;

        if (luaLoader->PushIntegerAndGetTable(indexOffset))
        {
            break;
        }

		TextBlockStyle textBlockStyle;
		textBlockStyle.m_uiID = CoreSystems::StringToHash32(luaLoader->GetStringByID("ID"));
		textBlockStyle.m_uiFont = CoreSystems::StringToHash32(luaLoader->GetStringByID("Font"));

		textBlockStyle.m_Color = ColorStringToSDLColor(luaLoader->GetStringByID("Color"));

		textBlockStyle.m_sDefaultText = luaLoader->GetStringByID("DefaultText");

		m_TextBlockStyles.insert({ textBlockStyle.m_uiID, textBlockStyle });

        luaLoader->PopTopTableElement();
    }

    // Load Button Styles.
    luaLoader->LoadTableByID("Buttons");

    const uint8_t uiButtonsTableSize = luaLoader->GetCurrentTableSize();
    for (uint8_t x=0; x < uiButtonsTableSize; ++x)
    {
        int indexOffset = x + 1;

        if (luaLoader->PushIntegerAndGetTable(indexOffset))
        {
            break;
        }

        ButtonStyle buttonStyle;
        buttonStyle.m_uiID = CoreSystems::StringToHash32(luaLoader->GetStringByID("ID"));
        buttonStyle.m_uiFont = CoreSystems::StringToHash32(luaLoader->GetStringByID("Font"));

        buttonStyle.m_HoverColor = ColorStringToSDLColor(luaLoader->GetStringByID("HoverColor"));
        buttonStyle.m_PressedColor = ColorStringToSDLColor(luaLoader->GetStringByID("PressedColor"));
        buttonStyle.m_TextColor = ColorStringToSDLColor(luaLoader->GetStringByID("TextColor"));
        buttonStyle.m_BaseColor = ColorStringToSDLColor(luaLoader->GetStringByID("BaseColor"));

        buttonStyle.m_sDefaultText = luaLoader->GetStringByID("DefaultText");
    
        m_ButtonStyles.insert( { buttonStyle.m_uiID, buttonStyle } );

        luaLoader->PopTopTableElement();
    }

    delete luaLoader;

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Style Data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Color StyleManager::ColorStringToSDLColor(std::string string)
{
    std::vector<int> vTempVector;
    std::string sTempString = "";

    const uint8_t uiStringSize = static_cast<uint8_t>(string.length());
    for (uint8_t x=0; x < uiStringSize; ++x)
    {
        const char currChar = string[x];

        if (currChar == ' ')
        {
            vTempVector.push_back(std::stoi(sTempString));
            sTempString.clear();
        }
        else
        {
            sTempString += currChar;
        }
    }
    vTempVector.push_back(std::stoi(sTempString));

    SDL_Color output;
    if (vTempVector.size() == 4)
    {
        output.r = vTempVector[0];
        output.g = vTempVector[1];
        output.b = vTempVector[2];
        output.a = vTempVector[3];
    }
    else
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Unable to load color from string!");
    }

    return output;
}

}