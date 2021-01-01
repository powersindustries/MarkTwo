#include <iostream>
#include <vector>

#include "../lib/glm/glm.hpp"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/TextLabelComponent.h"
#include "Components/ProjectileEmitterComponent.h"
#include "Components/PlayerProjectileEmitterController.h"
#include "Utilities/FileReader.h"

#include "../lib/rapidxml/rapidxml.hpp"
#include "../lib/rapidxml/rapidxml_utils.hpp"

#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "SoundManager.h"

namespace MarkTwo
{
    namespace GameCore
    {

        EntityManager manager;
        AssetManager* Game::m_AssetManager = new AssetManager(&manager);
        SDL_Renderer* Game::m_Renderer;
        SDL_Event Game::m_Event;
        SDL_Rect Game::m_Camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        Map* map;
        Entity* Player = NULL;


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Game::Game()
        {
            m_bIsRunning = true;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Game::~Game()
        {
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::Initialize(int width, int height)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            {
                std::cerr << "Error init sdl." << std::endl;
                return;
            }

            if (TTF_Init() != 0)
            {
                std::cerr << "Error init sdl ttf" << std::endl;
                return;
            }

            m_Window = SDL_CreateWindow("MarkTwo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);

            if (!m_Window)
            {
                std::cerr << "Window didnt work!" << std::endl;
                return;
            }

            // -1 is default driver
            m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

            if (!m_Renderer)
            {
                std::cerr << "Renderer didnt work!" << std::endl;
                return;
            }

            LoadLevel(1);

            m_bIsRunning = true;

            return;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::Update()
        {
            // Wait until 16ms has happened since last frame
            int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - m_iTicksLastFrame);

            if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
            {
                SDL_Delay(timeToWait);
            }

            // Time in seconds
            float deltaTime = (SDL_GetTicks() - m_iTicksLastFrame) / 1000.0f;

            // Clamp deltaTime to max value
            deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;

            m_iTicksLastFrame = SDL_GetTicks();

            manager.Update(deltaTime);

            CameraMovement();
            CheckCollisions();
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        bool Game::IsRunning() const
        {
            return m_bIsRunning;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::ProcessInput()
        {
            SDL_PollEvent(&m_Event);

            switch (m_Event.type)
            {
            case SDL_QUIT:
                m_bIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (m_Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    m_bIsRunning = false;
                }
                break;
            default:
                break;
            }

        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::Render()
        {
            SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
            SDL_RenderClear(m_Renderer);

            if (manager.HasNoEntities())
            {
                return;
            }

            manager.Render();

            SDL_RenderPresent(m_Renderer);
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::Destroy()
        {
            SDL_DestroyRenderer(m_Renderer);
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::CameraMovement()
        {
            if (Player)
            {
                TransformComponent* playerTransform = Player->GetComponent<TransformComponent>();
                
                m_Camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
                m_Camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

                // Clamp to size of tilemap
                m_Camera.x = m_Camera.x < 0 ? 0 : m_Camera.x;
                m_Camera.y = m_Camera.y < 0 ? 0 : m_Camera.y;
                m_Camera.x = m_Camera.x > m_Camera.w ? m_Camera.w : m_Camera.x;
                m_Camera.y = m_Camera.y > m_Camera.h ? m_Camera.h : m_Camera.y;
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::CheckCollisions()
        {
            CollisionType collisionType = manager.CheckCollisions();

            if (collisionType == PLAYER_ENEMY_COLLISION)
            {
                ProceedGameOver();
            }
            if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION)
            {
                ProceedNextLevel(1);
            }
            if (collisionType == PLAYER_PROJECTILE_COLLISION)
            {
                ProceedGameOver();
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::ProceedNextLevel(int level)
        {
            std::cout << "Next Level" << std::endl;
            m_bIsRunning = false;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::ProceedGameOver()
        {
            std::cout << "Game Over bitch" << std::endl;
            m_bIsRunning = false;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Game::LoadLevel(int levelNumber)
        {
            // --------------------------------------
            // SETUP XML PARSING WITH RAPIDXML
            // --------------------------------------
            std::string stringFilePath = "assets/data/Level" + std::to_string(levelNumber) + ".xml";
            
            rapidxml::file<> xmlFile(stringFilePath.c_str());
            rapidxml::xml_document<> doc;
            doc.parse<0>(xmlFile.data());


            // --------------------------------------
            // LOAD ASSETS FROM XML TO ASSET MANAGER
            // --------------------------------------
            rapidxml::xml_node<>* assetNode = doc.first_node()->first_node("Assets");
            std::vector<GameAssetData> gameAssets;
            for (rapidxml::xml_node<>* child = assetNode->first_node(); child; child = child->next_sibling())
            {
                GameAssetData currentAsset;

                currentAsset.m_Type = child->first_attribute("Type")->value();

                if (currentAsset.m_Type == "texture")
                {
                    currentAsset.m_ID = child->first_attribute("ID")->value();
                    currentAsset.m_FilePath = child->first_attribute("FilePath")->value();
                    currentAsset.m_FontSize = NULL;
               
                    m_AssetManager->AddTexture(currentAsset.m_ID, currentAsset.m_FilePath.c_str());
                }

                if (currentAsset.m_Type == "font")
                {
                    currentAsset.m_ID = child->first_attribute("ID")->value();
                    currentAsset.m_FilePath = child->first_attribute("FilePath")->value();
                    currentAsset.m_FontSize = std::stoi(child->first_attribute("FontSize")->value());

                    m_AssetManager->AddFont(currentAsset.m_ID, currentAsset.m_FilePath.c_str(), currentAsset.m_FontSize);
                }

                if (currentAsset.m_Type == "sound")
                {
                    currentAsset.m_ID = child->first_attribute("ID")->value();
                    currentAsset.m_FilePath = child->first_attribute("FilePath")->value();
                    currentAsset.m_FontSize = NULL;

                    m_AssetManager->AddSound(currentAsset.m_ID, currentAsset.m_FilePath.c_str());
                }

                gameAssets.emplace_back(currentAsset);

                // ----------- TESTING -----------
                //std::cout << "Asset Name: " << currentAsset.m_Type << std::endl;
                // ----------- TESTING -----------
            }


            // --------------------------------------
            // LOAD ASSETS FROM XML TO ASSET MANAGER
            // --------------------------------------
            rapidxml::xml_node<>* mapNode = doc.first_node()->first_node("Map");
            MapData mapData;
            mapData.m_TextureAssetID = mapNode->first_attribute("TextureAssetID")->value();
            mapData.m_FilePath       = mapNode->first_attribute("FilePath")->value();
            mapData.m_LevelMusicID   = mapNode->first_attribute("LevelMusicID")->value();
            mapData.m_Scale          = std::stoi(mapNode->first_attribute("Scale")->value());
            mapData.m_MapSizeX       = std::stoi(mapNode->first_attribute("MapSizeX")->value());
            mapData.m_MapSizeY       = std::stoi(mapNode->first_attribute("MapSizeY")->value());
            mapData.m_TileSize       = std::stoi(mapNode->first_attribute("TileSize")->value()); 

            // check if level music exists, if it does play it
            if (mapData.m_LevelMusicID != "")
            {
                std::string assetFilePath = m_AssetManager->GetSound(mapData.m_LevelMusicID);
                g_SoundManager.PlaySound(assetFilePath.c_str());
            }

            map = new Map(mapData.m_TextureAssetID, mapData.m_Scale, mapData.m_TileSize);
            map->LoadMap(mapData.m_FilePath, mapData.m_MapSizeX, mapData.m_MapSizeY);


            // --------------------------------------
            // LOAD ENTITIES FROM XML TO ENTITY MANAGER
            // --------------------------------------
            rapidxml::xml_node<>* entitiesNode = doc.first_node()->first_node("Entities");
            for (rapidxml::xml_node<>* child = entitiesNode->first_node(); child; child = child->next_sibling())
            {
                std::string entityName = child->first_attribute("Name")->value();
                LayerType entityLayer  = (LayerType)(std::stoi(child->first_attribute("Layer")->value()));

                // ----------- TESTING -----------
                //std::cout << "Entity Name: " << entityName << std::endl;
                // ----------- TESTING -----------

                auto& newEntity(manager.AddEntity(entityName, entityLayer));

                // Add Transform component
                TransformData transformData;
                if (child->first_node("Transform") != NULL)
                {
                    transformData.m_PositionX = std::stoi(child->first_node("Transform")->first_attribute("PositionX")->value());
                    transformData.m_PositionY = std::stoi(child->first_node("Transform")->first_attribute("PositionY")->value());
                    transformData.m_VelocityX = std::stoi(child->first_node("Transform")->first_attribute("VelocityX")->value());
                    transformData.m_VelocityY = std::stoi(child->first_node("Transform")->first_attribute("VelocityY")->value());
                    transformData.m_Width     = std::stoi(child->first_node("Transform")->first_attribute("Width")->value());
                    transformData.m_Height    = std::stoi(child->first_node("Transform")->first_attribute("Height")->value());
                    transformData.m_Scale     = std::stoi(child->first_node("Transform")->first_attribute("Scale")->value());
                    transformData.m_Rotation  = std::stoi(child->first_node("Transform")->first_attribute("Rotation")->value());

                    newEntity.AddComponent<TransformComponent>(transformData.m_PositionX, transformData.m_PositionY, transformData.m_VelocityX, transformData.m_VelocityY, transformData.m_Width, transformData.m_Height, transformData.m_Scale);
                }

                // Add Sprite Component
                SpriteData spriteData;
                if (child->first_node("Sprite") != NULL)
                {
                    spriteData.m_TextureAssetID = child->first_node("Sprite")->first_attribute("TextureAssetID")->value();
                    spriteData.m_IsAnimated     = MarkTwo::Utilities::g_Math.StringToBool(child->first_node("Sprite")->first_attribute("Animated")->value());

                    if (spriteData.m_IsAnimated)
                    {
                        spriteData.m_FrameCount = std::stoi(child->first_node("Sprite")->first_attribute("FrameCount")->value());
                        spriteData.m_AnimationSpeed = std::stoi(child->first_node("Sprite")->first_attribute("AnimationSpeed")->value());
                        spriteData.m_IsFixed  = MarkTwo::Utilities::g_Math.StringToBool(child->first_node("Sprite")->first_attribute("Fixed")->value());
                        spriteData.m_HasDirections = MarkTwo::Utilities::g_Math.StringToBool(child->first_node("Sprite")->first_attribute("Directions")->value());
                        
                        newEntity.AddComponent<SpriteComponent>(spriteData.m_TextureAssetID, spriteData.m_FrameCount, spriteData.m_AnimationSpeed, spriteData.m_HasDirections, spriteData.m_IsFixed);
                    }
                    else
                    {
                        newEntity.AddComponent<SpriteComponent>(spriteData.m_TextureAssetID, false);
                    }
                }

                // Add input control component
                InputData inputData;
                if (child->first_node("Input") != NULL)
                {
                    inputData.m_UpKey    = child->first_node("Input")->first_attribute("Up")->value();
                    inputData.m_LeftKey  = child->first_node("Input")->first_attribute("Left")->value();
                    inputData.m_DownKey  = child->first_node("Input")->first_attribute("Down")->value();
                    inputData.m_RightKey = child->first_node("Input")->first_attribute("Right")->value();
                    inputData.m_ShootKey = child->first_node("Input")->first_attribute("Shoot")->value();

                    newEntity.AddComponent<KeyboardControlComponent>(inputData.m_UpKey, inputData.m_RightKey, inputData.m_DownKey, inputData.m_LeftKey, inputData.m_ShootKey);
                }

                // Add Collider component
                if (child->first_node("Collider") != NULL)
                {
                    std::string colliderTag = child->first_node("Collider")->first_attribute("Tag")->value();

                    newEntity.AddComponent<ColliderComponent>(colliderTag, transformData.m_PositionX, transformData.m_PositionY, transformData.m_Width, transformData.m_Height);
                }

                // Add Projectile emitter component
                if (child->first_node("ProjectileEmitter") != NULL)
                {
                    ProjectileData projectileData;
                    projectileData.m_ProjectileAssetID = child->first_node("ProjectileEmitter")->first_attribute("TextureAssetID")->value();
                    projectileData.m_ProjectileWidth   = std::stoi(child->first_node("ProjectileEmitter")->first_attribute("Width")->value());
                    projectileData.m_ProjectileHeight  = std::stoi(child->first_node("ProjectileEmitter")->first_attribute("Height")->value());
                    projectileData.m_ProjectileSpeed   = std::stoi(child->first_node("ProjectileEmitter")->first_attribute("Speed")->value());
                    projectileData.m_ProjectileRange   = std::stoi(child->first_node("ProjectileEmitter")->first_attribute("Range")->value());
                    projectileData.m_ProjectileAngle   = std::stoi(child->first_node("ProjectileEmitter")->first_attribute("Angle")->value());
                    projectileData.m_ShouldLoop        = MarkTwo::Utilities::g_Math.StringToBool(child->first_node("ProjectileEmitter")->first_attribute("ShouldLoop")->value());

                    Entity& projectile(manager.AddEntity("projectile", ePROJECTILE_LAYER));

                    projectile.AddComponent<TransformComponent>(
                        transformData.m_PositionX + (transformData.m_Width / 2),
                        transformData.m_PositionY + (transformData.m_Height / 2),
                        0, 0, projectileData.m_ProjectileWidth, projectileData.m_ProjectileHeight, 1);

                    projectile.AddComponent<SpriteComponent>(projectileData.m_ProjectileAssetID);
                    projectile.AddComponent<ProjectileEmitterComponent>(projectileData.m_ProjectileSpeed, projectileData.m_ProjectileAngle, projectileData.m_ProjectileRange, projectileData.m_ShouldLoop);
                    
                    // Check to see if its a player shot projectile
                    projectile.AddComponent<ColliderComponent>("PROJECTILE", transformData.m_PositionX, transformData.m_PositionY, transformData.m_Width, transformData.m_Height);
                }

            }

            Player = manager.GetEntityByName("player");

        }
    }
}
