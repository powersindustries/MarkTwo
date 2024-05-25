#include "UIManager.h"
#include "GameGlobals.h"
#include "rapidxml_utils.hpp"
#include "Core/Systems/Logging.h"
#include "Core/Systems/Hash.h"

#include "Core/UI/Types/UIBase.h"
#include "Core/UI/Primitives/Box.h"
#include "Core/UI/Types/Widget.h"
#include "Core/UI/Primitives/TextBlock.h"
#include "Core/UI/Primitives/Button.h"
#include "Core/UI/Primitives/VerticalStack.h"
#include "Core/UI/Primitives/HorizontalStack.h"
#include "Core/Managers/AssetManager.h"
#include "Game/Managers/EventManager.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
UIManager g_UIManager;


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::UIManager()
{
    m_sStyleFilepath = __PROJECT_DIRECTORY__;
    m_sStyleFilepath.append("/src/Data/Styles.xml");

    m_sWidgetFilepath = __PROJECT_DIRECTORY__;
    m_sWidgetFilepath.append("/src/Data/Widgets");
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Initialize()
{
    InitializeStyleData();
    InitializeWidgetData();
}


// -------------------------------------------------------
// -------------------------------------------------------
Widget* UIManager::GetWidgetById(const std::string& id)
{
    return m_WidgetMap[id];
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::InitializeStyleData()
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
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning,
                                  "Child node in StyleTypes::Initialize() method is nullptr.");
                continue;
            }

            TextBlockStyle textBlockStyle;
            textBlockStyle.m_uiId = Core::StringToHash(std::string(child->first_attribute("ID")->value()));
            textBlockStyle.m_uiFont = Core::StringToHash(std::string(child->first_attribute("Font")->value()));
            textBlockStyle.m_Color = StringToSDLColor(std::string(child->first_attribute("Color")->value()));
            textBlockStyle.m_sDefaultText = std::string(child->first_attribute("DefaultText")->value());

            m_TextBlockStyles.insert({textBlockStyle.m_uiId, textBlockStyle});
        }
    }

    // Load Button Styles.
    rapidxml::xml_node<>* buttonNode = doc.first_node()->first_node("Buttons");
    if (buttonNode)
    {
        for (rapidxml::xml_node<>* child = buttonNode->first_node(); child; child = child->next_sibling())
        {
            ButtonStyle buttonStyle;
            buttonStyle.m_uiId = Core::StringToHash(child->first_attribute("ID")->value());
            buttonStyle.m_uiFont = Core::StringToHash(child->first_attribute("Font")->value());

            buttonStyle.m_HoverColor = StringToSDLColor(child->first_attribute("HoverColor")->value());
            buttonStyle.m_PressedColor = StringToSDLColor(child->first_attribute("PressedColor")->value());
            buttonStyle.m_TextColor = StringToSDLColor(child->first_attribute("TextColor")->value());
            buttonStyle.m_BaseColor = StringToSDLColor(child->first_attribute("BaseColor")->value());

            buttonStyle.m_sDefaultText = std::string(child->first_attribute("DefaultText")->value());

            m_ButtonStyles.insert({buttonStyle.m_uiId, buttonStyle});
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Style Data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::InitializeWidgetData()
{
    assert(std::__fs::filesystem::is_directory(m_sWidgetFilepath));

    for (const auto& entry: std::__fs::filesystem::directory_iterator(m_sWidgetFilepath))
    {
        const auto& widgetPath = entry.path();
        LoadWidgetFile(widgetPath);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::LoadWidgetFile(const std::string& filePath)
{
    rapidxml::file<> xmlFile(filePath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* rootNode = doc.first_node("Widget");
    assert(rootNode);

    const std::string& widgetId = rootNode->first_attribute("id")->value();
    assert(!widgetId.empty());

    Widget* newWidget = new Widget(widgetId);
    if (newWidget)
    {
        // Iterate through UI Primitives.
        for (rapidxml::xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling())
        {
            UIBase* newPrimitive = SerializeXmlToUiPrimitive(node);
            if (newPrimitive)
            {
                newWidget->AddPrimitive(newPrimitive);
            }
        }

        m_WidgetMap.insert({newWidget->GetId(), newWidget});
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
UIBase* UIManager::SerializeXmlToUiPrimitive(const rapidxml::xml_node<>* node)
{
    if (!node)
    {
        return nullptr;
    }

    UIBase* newPrimitive = nullptr;

    // Create instance of new Primitive based on Node name.
    const std::string& primitiveType = node->name();
    if (primitiveType == "Box")
    {
        newPrimitive = new Box();
    }
    else if (primitiveType == "TextBlock")
    {
        newPrimitive = new TextBlock();
    }
    else if (primitiveType == "Button")
    {
        newPrimitive = new Button();
    }
    else if (primitiveType == "VerticalStack")
    {
        newPrimitive = new VerticalStack();
    }
    else if (primitiveType == "HorizontalStack")
    {
        newPrimitive = new HorizontalStack();
    }

    // Continue if primitive isn't supported.
    if (!newPrimitive)
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Primitive name " + primitiveType + " is not supported.");
        return nullptr;
    }

    rapidxml::xml_attribute<>* idAttribute = node->first_attribute("id");
    if (idAttribute)
    {
        newPrimitive->m_sId = idAttribute->value();
    }

    // Serialize XML attributes and set properties in each primitive.
    for (rapidxml::xml_attribute<>* currAttribute = node->first_attribute(); currAttribute; currAttribute = currAttribute->next_attribute())
    {
        std::string attribute = currAttribute->name();
        std::string value = currAttribute->value();

        // Format attribute.
        FormatString(attribute);

        // Populate general UI values.
        if (attribute == "anchor")
        {
            FormatString(value);
            newPrimitive->SetAnchor(StringToAnchor(value));
        }
        else if (attribute == "alignment")
        {
            FormatString(value);
            newPrimitive->SetAlignment(StringToAnchor(value));
        }
        else if (attribute == "color")
        {
            newPrimitive->SetColor(StringToSDLColor(value));
        }
        else if (attribute == "size")
        {
            Core::Vec2i sizeVector = StringToSizeVector(value);
            newPrimitive->SetSize(sizeVector.m_X, sizeVector.m_Y);
        }
        else if (attribute == "visibility")
        {
            FormatString(value);
            newPrimitive->SetVisibility(StringToUIVisibility(value));
        }
        else if (attribute == "offset")
        {
            Core::Vec2i sizeVector = StringToSizeVector(value);
            newPrimitive->SetOffset(sizeVector.m_X, sizeVector.m_Y);
        }

        // Primitive Specific UI values.
        if (attribute == "text")
        {
            if (primitiveType == "TextBlock")
            {
                TextBlock* newPrimitiveAsTextblock = dynamic_cast<TextBlock*>(newPrimitive);
                if (newPrimitiveAsTextblock)
                {
                    newPrimitiveAsTextblock->SetText(value);
                }
                else
                {
                    Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Primitive failed to cast to type: " + primitiveType);
                }
            }
            else if (primitiveType == "Button")
            {
                Button* newPrimitiveAsButton = dynamic_cast<Button*>(newPrimitive);
                if (newPrimitiveAsButton)
                {
                    newPrimitiveAsButton->SetText(value);
                }
                else
                {
                    Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Primitive failed to cast to type: " + primitiveType);
                }
            }
        }
        else if (attribute == "padding" && (primitiveType == "VerticalStack" || primitiveType == "HorizontalStack"))
        {
            StackBase* newPrimitiveAsStack = dynamic_cast<StackBase*>(newPrimitive);
            if (newPrimitiveAsStack)
            {
                newPrimitiveAsStack->SetPadding(std::stoi(value));
            }
            else
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Primitive failed to cast to type: " + primitiveType);
            }
        }
        else if (attribute == "margin" && primitiveType == "Box")
        {
            Box* newPrimitiveAsBox = dynamic_cast<Box*>(newPrimitive);
            if (newPrimitiveAsBox)
            {
                newPrimitiveAsBox->SetMargin(StringToMargin(value));
            }
            else
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Primitive failed to cast to type: " + primitiveType);
            }
        }
    }

    // Handle nested children for Stack types.
    if (primitiveType == "VerticalStack" || primitiveType == "HorizontalStack" || primitiveType == "Box")
    {
        for (rapidxml::xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling())
        {
            UIBase* childPrimitive = SerializeXmlToUiPrimitive(childNode);
            if (childPrimitive)
            {
                if (primitiveType == "Box")
                {
                    Box* newPrimitiveAsBox = dynamic_cast<Box*>(newPrimitive);
                    if (newPrimitiveAsBox)
                    {
                        newPrimitiveAsBox->AddChild(childPrimitive);
                    }
                }
                else
                {
                    StackBase* newPrimitiveAsStack = dynamic_cast<StackBase*>(newPrimitive);
                    if (newPrimitiveAsStack)
                    {
                        newPrimitiveAsStack->AddChild(childPrimitive);
                    }
                }
            }
        }
    }

    m_UIBaseMap.insert({newPrimitive->m_sId, newPrimitive});

    return newPrimitive;
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::FormatString(std::string& string)
{
    const uint8_t attributeSize = static_cast<uint8_t>(string.size());
    for (uint8_t x = 0; x < attributeSize; ++x)
    {
        string[x] = std::tolower(string[x]);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
Anchor UIManager::StringToAnchor(const std::string& string)
{
    if (string == "topleft")
    {
        return Anchor::eTopLeft;
    }
    else if (string == "topcenter" || string == "centertop")
    {
        return Anchor::eTopCenter;
    }
    else if (string == "topright")
    {
        return Anchor::eTopRight;
    }
    else if (string == "centerleft")
    {
        return Anchor::eCenterLeft;
    }
    else if (string == "center")
    {
        return Anchor::eCenter;
    }
    else if (string == "centerright")
    {
        return Anchor::eCenterRight;
    }
    else if (string == "bottomleft")
    {
        return Anchor::eBottomLeft;
    }
    else if (string == "bottomcenter")
    {
        return Anchor::eBottomCenter;
    }
    else if (string == "bottomright")
    {
        return Anchor::eBottomRight;
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Anchor type does not exist or is not supported.");
    return Anchor::eTopLeft;
}


// -------------------------------------------------------
// -------------------------------------------------------
UIVisibility UIManager::StringToUIVisibility(const std::string& string)
{
    if (string == "visible")
    {
        return UIVisibility::eVisible;
    }
    else if (string == "hidden")
    {
        return UIVisibility::eHidden;
    }
    else if (string == "disabled")
    {
        return UIVisibility::eDisabled;
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UIVisibility type does not exist or is not supported.");
    return UIVisibility::eVisible;
}


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Color UIManager::StringToSDLColor(const std::string& string)
{
    std::vector<int> tempVector;
    std::string tempString = "";

    const uint8_t stringSize = static_cast<uint8_t>(string.length());
    for (uint8_t x = 0; x < stringSize; ++x)
    {
        const char currChar = string[x];

        if (currChar == ' ')
        {
            tempVector.push_back(std::stoi(tempString));
            tempString.clear();
        }
        else
        {
            tempString += currChar;
        }
    }
    tempVector.push_back(std::stoi(tempString));

    SDL_Color output;
    if (tempVector.size() == 4)
    {
        output.r = tempVector[0];
        output.g = tempVector[1];
        output.b = tempVector[2];
        output.a = tempVector[3];
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Unable to load color from string!");
    }

    return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
Margin UIManager::StringToMargin(const std::string& string)
{
    std::vector<int> tempVector;
    std::string tempString = "";

    const uint8_t stringSize = static_cast<uint8_t>(string.length());
    for (uint8_t x = 0; x < stringSize; ++x)
    {
        const char currChar = string[x];

        if (currChar == ' ')
        {
            tempVector.push_back(std::stoi(tempString));
            tempString.clear();
        }
        else
        {
            tempString += currChar;
        }
    }
    tempVector.push_back(std::stoi(tempString));

    Margin output;
    if (tempVector.size() == 4)
    {
        output.m_iLeft = tempVector[0];
        output.m_iTop = tempVector[1];
        output.m_iRight = tempVector[2];
        output.m_iBottom = tempVector[3];
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Unable to load color from string!");
    }

    return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
Core::Vec2i UIManager::StringToSizeVector(const std::string& string)
{
    std::vector<int> tempVector;
    std::string tempString = "";

    const uint8_t stringSize = static_cast<uint8_t>(string.length());
    for (uint8_t x = 0; x < stringSize; ++x)
    {
        const char currChar = string[x];

        if (currChar == ' ')
        {
            tempVector.push_back(std::stoi(tempString));
            tempString.clear();
        }
        else
        {
            tempString += currChar;
        }
    }
    tempVector.push_back(std::stoi(tempString));

    Core::Vec2i output;
    if (tempVector.size() > 0)
    {
        output.m_X = tempVector[0];
        output.m_Y = tempVector[1];
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Unable to load color from string!");
    }

    return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
TTF_Font* UIManager::GetDefaultFont()
{
    return Core::g_AssetManager.m_FontAssetsMap[Core::StringToHash(std::string("fnt_Orbitron"))].m_Font;
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::DEBUG_HOTRELOAD()
{
    // Reset data.
    m_TextBlockStyles.clear();
    m_ButtonStyles.clear();
    m_WidgetMap.clear();

    Initialize();

    MarkTwo::g_EventManager.Broadcast(UI_DEBUG_EVENT_ID);
}


// -------------------------------------------------------
// -------------------------------------------------------
UIBase* UIManager::GetPrimitiveById(const std::string& id)
{
    return m_UIBaseMap[id];
}

}