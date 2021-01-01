#pragma once
#include <SDL2/include/SDL.h>
#include <SDL2/include/SDL_image.h>
#include <SDL2/include/SDL_ttf.h>

#include "../lib/rapidxml/rapidxml.hpp"

#include <string>

#include "EntityManager.h"
#include "Entity.h"
#include "Constants.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class AssetManager;

        class Game
        {
        public:
            Game();
            ~Game();

            bool IsRunning() const;

            void Initialize(int width, int height);
            void ProcessInput();
            void Update();
            void Render();
            void Destroy();
            void CameraMovement();
            void CheckCollisions();
            void ProceedNextLevel(int level);
            void ProceedGameOver();

            void LoadLevel(int levelNumber);

        public:
            SDL_Window* m_Window;
            static SDL_Renderer* m_Renderer;
            static AssetManager* m_AssetManager;
            static SDL_Event m_Event;
            static SDL_Rect m_Camera;
           

        private:
            bool m_bIsRunning;
            int m_iTicksLastFrame;

        };

        // DATA STRUCTS
        struct TransformData
        {
            int m_PositionX;
            int m_PositionY;
            int m_VelocityX;
            int m_VelocityY;
            int m_Width;
            int m_Height;
            int m_Scale;
            int m_Rotation;
        };

        struct SpriteData
        {
            std::string m_TextureAssetID;

            int m_FrameCount;
            int m_AnimationSpeed;

            bool m_IsAnimated;
            bool m_IsFixed;
            bool m_HasDirections;
        };

        struct InputData
        {
            std::string m_UpKey;
            std::string m_LeftKey;
            std::string m_DownKey;
            std::string m_RightKey;
            std::string m_ShootKey;
        };

        struct GameAssetData
        {
            std::string m_Type;
            std::string m_ID;
            std::string m_FilePath;

            int m_FontSize;
        };

        struct MapData
        {
            std::string m_TextureAssetID;
            std::string m_FilePath;
            std::string m_LevelMusicID;
            
            int m_Scale;
            int m_TileSize;
            int m_MapSizeX;
            int m_MapSizeY;
        };

        struct ProjectileData
        {
            std::string m_ProjectileAssetID;

            int m_ProjectileWidth;
            int m_ProjectileHeight;
            int m_ProjectileSpeed;
            int m_ProjectileRange;
            int m_ProjectileAngle;
            
            bool m_ShouldLoop;
        };

    }
}
