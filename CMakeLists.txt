cmake_minimum_required(VERSION 3.7)
project(MarkTwo VERSION 2.2)

# Set version of C++.
set (CMAKE_CXX_STANDARD 11)

# Set Source directory to be used in game.
add_definitions(-DPROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Set Source directory to be used in game.
add_definitions(-DVERSION_NUMBER="${CMAKE_PROJECT_VERSION}")

# Set build types.
IF(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
  add_definitions(-DDEBUG_BUILD=false)
ELSE()
  message("Debug build.")
  add_definitions(-DDEBUG_BUILD=true)
ENDIF()

# Remove warnings from C deprication warnings.
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_BUILD_TYPE Debug)

# Set CMake Library/Package Paths.
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/ )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


# Set Libraries for Windows.
if(WIN32)

    # Setup SDL include directory and libraries.
    set( SDL2_INCLUDE_DIRS        "${CMAKE_CURRENT_LIST_DIR}/External/SDL2/include" )
    set( SDL2_IMAGE_INCLUDE_DIRS  "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_image/include" )
    set( SDL2_TTF_INCLUDE_DIRS    "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_ttf/include" )
    set( SDL2_MIXER_INCLUDE_DIRS  "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_mixer/include" )

    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)

        set( SDL2_LIBRARIES        "${CMAKE_CURRENT_LIST_DIR}/External/SDL2/lib/x64/SDL2.lib;" )
        set( SDL2_IMAGE_LIBRARIES  "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_image/lib/x64/SDL2_image.lib;" )
        set( SDL2_TTF_LIBRARIES    "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_ttf/lib/x64/SDL2_ttf.lib;" )
        set( SDL2_MIXER_LIBRARIES  "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_mixer/lib/x64/SDL2_mixer.lib;" )

    else ()

        set( SDL2_LIBRARIES        "${CMAKE_CURRENT_LIST_DIR}/External/SDL2/lib/x86/SDL2.lib;" )
        set( SDL2_IMAGE_LIBRARIES  "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_image/lib/x86/SDL2_image.lib;" )
        set( SDL2_TTF_LIBRARIES    "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_ttf/lib/x86/SDL2_ttf.lib;" )
        set( SDL2_MIXER_LIBRARIES  "${CMAKE_CURRENT_LIST_DIR}/External/SDL2_mixer/lib/x86/SDL2_mixer.lib;" )

    endif ()

# Set Libraries for Linux.
else()


    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)

endif()


# Include RapidXml includes.
set( RAPID_XML_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/External/RapidXml" )


# Add Resource paths to includes.
set(RESOURCE_FILES

src/Data/AssetManifest.xml
src/Data/Settings.xml
src/Data/Styles.xml

src/Data/MapsManifest.xml
src/Data/Maps/mp_1.xml

src/Data/TileMaps/tm_1.xml

src/Assets/Textures/ChopperSpritesheet.png
src/Assets/Textures/testIcon.png
src/Assets/Textures/testTileMap.png

)

# Add Source Files to includes.
set(SOURCE_FILES

src/Main.cpp
src/GameGlobals.h

src/Core/Game.h
src/Core/Game.cpp

src/Core/Types/Sprite.h
src/Core/Types/Sprite.cpp
src/Core/Types/Transform.h
src/Core/Types/Transform.cpp
src/Core/Types/String.h
src/Core/Types/String.cpp
src/Core/Types/Texture.h
src/Core/Types/Texture.cpp

src/Core/Systems/Systems.h
src/Core/Systems/Assert.h
src/Core/Systems/Logging.h
src/Core/Systems/Hash.h

        src/Core/Managers/InputManager.h
src/Core/Managers/InputManager.cpp
src/Core/Managers/SettingsManager.h
src/Core/Managers/SettingsManager.cpp
src/Core/Managers/SoundManager.h
src/Core/Managers/SoundManager.cpp
src/Core/Managers/AssetManager.h
src/Core/Managers/AssetManager.cpp
src/Core/UI/Types/StyleTypes.h
src/Core/UI/Types/StyleTypes.cpp

src/Core/Math/VectorMethods.h
src/Core/Math/VectorMethods.cpp
src/Core/Math/Utility.h
src/Core/Math/Utility.cpp

src/Core/UI/Types/Widget.h
src/Core/UI/Types/Widget.cpp
src/Core/UI/Types/UIBase.h
src/Core/UI/Types/UIBase.cpp
src/Core/UI/UIManager.h
src/Core/UI/UIManager.cpp
src/Core/UI/Types/UICoreTypes.h
src/Core/UI/Types/UICoreTypes.cpp
src/Core/UI/Types/UIScreenBase.h
src/Core/UI/Types/UIScreenBase.cpp
src/Core/UI/Primitives/Box.h
src/Core/UI/Primitives/Box.cpp
src/Core/UI/Primitives/Button.h
src/Core/UI/Primitives/Button.cpp
src/Core/UI/Primitives/VerticalStack.h
src/Core/UI/Primitives/VerticalStack.cpp
src/Core/UI/Primitives/HorizontalStack.h
src/Core/UI/Primitives/HorizontalStack.cpp
src/Core/UI/Primitives/TextBlock.h
src/Core/UI/Primitives/TextBlock.cpp
src/Core/UI/Primitives/Icon.h
src/Core/UI/Primitives/Icon.cpp

src/Game/Player/Player.h
src/Game/Player/Player.cpp
src/Game/Player/PlayerMovement.h
src/Game/Player/PlayerMovement.cpp

src/Game/UIScreens/HUDScreen.h
src/Game/UIScreens/HUDScreen.cpp
src/Game/UIScreens/PauseScreen.h
src/Game/UIScreens/PauseScreen.cpp

src/Game/Managers/FrontendManager.h
src/Game/Managers/FrontendManager.cpp
        src/Core/Managers/EventManager.h
        src/Core/Managers/EventManager.cpp
src/Game/Managers/MapManager.h
src/Game/Managers/MapManager.cpp

${RESOURCE_FILES}
        src/Core/UI/Types/StackBase.h
        src/Core/UI/Types/StackBase.cpp


)


include_directories(src)
include_directories( ${SDL2_INCLUDE_DIRS} ) 
include_directories( ${SDL2_IMAGE_INCLUDE_DIRS} ) 
include_directories( ${SDL2_TTF_INCLUDE_DIRS} )
include_directories( ${SDL2_MIXER_INCLUDE_DIRS} )
include_directories( ${RAPID_XML_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(
    ${PROJECT_NAME} 
    
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Powers Industries, LLC")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An ongoing open sourse game engine project made by Powers Industries, LLC.")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_PROJECT_VERSION_MAJOR 2)
set(CPACK_PROJECT_VERSION_MINOR 1)

include(CPack)
