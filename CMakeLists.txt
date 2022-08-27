cmake_minimum_required(VERSION 3.7)
project(MarkTwo VERSION 2.0)


# Set Source directory to be used in game
add_definitions(-DPROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Remove warnings from C deprication warnings
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Set Library/Package Paths
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories( ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} )


# Add Resource paths to includes
set(RESOURCE_FILES

src/Data/AssetManifest.xml

src/Assets/Textures/ChopperSpritesheet.png

src/Assets/Fonts/arial.ttf
src/Assets/Fonts/charriot.ttf

)


# Add Source Files to includes
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

src/Core/Systems/Systems.h
src/Core/Systems/Assert.h
src/Core/Systems/Logging.h
src/Core/Systems/Hash.h
src/Core/Systems/Event.h

src/Core/Math/VectorMethods.h
src/Core/Math/VectorMethods.cpp

src/Core/UI/UICoreTypes.h
src/Core/UI/UICoreTypes.cpp
src/Core/UI/Types/Box.h
src/Core/UI/Types/Box.cpp
src/Core/UI/Types/Button.h
src/Core/UI/Types/Button.cpp
src/Core/UI/Types/StackPanel.h
src/Core/UI/Types/StackPanel.cpp
src/Core/UI/Types/TextBlock.h
src/Core/UI/Types/TextBlock.cpp

src/Game/Player/Player.h
src/Game/Player/Player.cpp
src/Game/Player/PlayerMovement.h
src/Game/Player/PlayerMovement.cpp

src/Game/UIScreens/HUDScreen.h
src/Game/UIScreens/HUDScreen.cpp
src/Game/UIScreens/PauseScreen.h
src/Game/UIScreens/PauseScreen.cpp

src/Game/Managers/InputManager.h
src/Game/Managers/InputManager.cpp
src/Game/Managers/LoadManager.h
src/Game/Managers/LoadManager.cpp
src/Game/Managers/UIManager.h
src/Game/Managers/UIManager.cpp
src/Game/Managers/EventManager.h
src/Game/Managers/EventManager.cpp

${RESOURCE_FILES}

)

include_directories(src)

include_directories(${CMAKE_SOURCE_DIR}/External/rapidxml/)
include_directories(${CMAKE_SOURCE_DIR}/External/glm/)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})


# Add SDL2.dll to exe folder
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2/lib/x64/SDL2.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else ()
  add_custom_command(TARGET MarkTwo POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2/lib/x86/SDL2.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()

# Add SDL2.dll to exe folder
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_image/lib/x64/SDL2_image.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else ()
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_image/lib/x86/SDL2_image.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()

# Add SDL2.dll to exe folder
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_ttf/lib/x64/SDL2_ttf.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else ()
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_ttf/lib/x86/SDL2_ttf.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()

# Add libfreetype-6.dll to exe folder
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_ttf/lib/x64/libfreetype-6.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else ()
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_ttf/lib/x86/libfreetype-6.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()

# Add zlib1.dll to exe folder
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_ttf/lib/x64/zlib1.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else ()
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/External/SDL2_ttf/lib/x86/zlib1.dll"
         $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()