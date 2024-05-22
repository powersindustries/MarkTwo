#ifndef UIManager_H
#define UIManager_H

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include <map>

#include "Core/UI/Types/StyleTypes.h"
#include "Core/UI/Types/Widget.h"
#include "rapidxml.hpp"

namespace UI
{

class UIManager
{
public:

    UIManager();

    void Initialize();

    Widget* GetWidgetByID(const std::string& id);
    UIBase* GetPrimitiveByID(const std::string& id);
    TTF_Font* GetDefaultFont();

    inline const TextBlockStyle& GetTextBlockStyle(const uint32_t styleId) { return m_TextBlockStyles[styleId]; }
    inline const ButtonStyle& GetButtonStyle(const uint32_t styleId) { return m_ButtonStyles[styleId]; }

    void DEBUG_HOTRELOAD();


private:

    void InitializeWidgetData();
    void InitializeStyleData();
    void LoadWidgetFile(const std::string& filePath);

    UIBase* SerializeXmlToUiPrimitive(const rapidxml::xml_node<>* node);


    // Helper Functions.
    SDL_Color StringToSDLColor(const std::string& string);
    Margin StringToMargin(const std::string& string);
    Anchor StringToAnchor(const std::string& string);
    UIVisibility StringToUIVisibility(const std::string& string);
    Core::Vec2i StringToSizeVector(const std::string& string);

    void FormatString(std::string& string);


private:

    std::string m_sWidgetFilepath;
    std::string m_sStyleFilepath;

    std::map<uint32_t, TextBlockStyle> m_TextBlockStyles; // ID as hash, TextBlockStyle Data
    std::map<uint32_t, ButtonStyle> m_ButtonStyles; // ID as hash, ButtonStyle Data

    std::unordered_map<std::string, Widget*> m_WidgetMap;
    std::unordered_map<std::string, UIBase*> m_UIBaseMap;

};

extern UIManager g_UIManager;
}

#endif
