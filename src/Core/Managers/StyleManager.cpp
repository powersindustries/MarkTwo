#include "StyleManager.h"
#include <vector>

#include "rapidxml_utils.hpp"

#include "GameGlobals.h"
#include "../Systems/Logging.h"
#include "../Systems/Hash.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager g_StyleManager;


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager::StyleManager()
{
    m_sStyleFilepath.append(__PROJECT_DIRECTORY__);
    m_sStyleFilepath.append("/src/Data/Styles.xml");
}


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager::~StyleManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StyleManager::Initialize()
{
    rapidxml::file<> xmlFile(m_sStyleFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    // Load TextBlock Styles.
    rapidxml::xml_node<>* textBlockNode = doc.first_node()->first_node("TextBlocks");
    if (textBlockNode)
    {
        for (rapidxml::xml_node<>* child = textBlockNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in StyleManager::Initialize() method is nullptr.");
                continue;
            }

            TextBlockStyle textBlockStyle;
            textBlockStyle.m_uiID = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            textBlockStyle.m_uiFont = Core::StringToHash32(std::string(child->first_attribute("Font")->value()));
            textBlockStyle.m_Color = ColorStringToSDLColor(std::string(child->first_attribute("Color")->value()));
            textBlockStyle.m_sDefaultText = std::string(child->first_attribute("DefaultText")->value());

            m_TextBlockStyles.insert({ textBlockStyle.m_uiID, textBlockStyle });
        }
    }

    // Load Button Styles.
    rapidxml::xml_node<>* buttonNode = doc.first_node()->first_node("Buttons");
    if (buttonNode)
    {
        for (rapidxml::xml_node<>* child = buttonNode->first_node(); child; child = child->next_sibling())
        {
            ButtonStyle buttonStyle;
            buttonStyle.m_uiID = Core::StringToHash32(child->first_attribute("ID")->value());
            buttonStyle.m_uiFont = Core::StringToHash32(child->first_attribute("Font")->value());

            buttonStyle.m_HoverColor = ColorStringToSDLColor(child->first_attribute("HoverColor")->value());
            buttonStyle.m_PressedColor = ColorStringToSDLColor(child->first_attribute("PressedColor")->value());
            buttonStyle.m_TextColor = ColorStringToSDLColor(child->first_attribute("TextColor")->value());
            buttonStyle.m_BaseColor = ColorStringToSDLColor(child->first_attribute("BaseColor")->value());

            buttonStyle.m_sDefaultText = std::string(child->first_attribute("DefaultText")->value());

            m_ButtonStyles.insert({ buttonStyle.m_uiID, buttonStyle });
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Style Data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Color StyleManager::ColorStringToSDLColor(std::string inString)
{
    std::vector<int> vTempVector;
    std::string sTempString = "";

    const uint8_t uiStringSize = static_cast<uint8_t>(inString.length());
    for (uint8_t x = 0; x < uiStringSize; ++x)
    {
        const char currChar = inString[x];

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
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Unable to load color from string!");
    }

    return output;
}

}
