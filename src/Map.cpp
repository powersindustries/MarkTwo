#include <fstream>
#include "Map.h"
#include "Game.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"

namespace MarkTwo
{
    namespace GameCore
    {
        extern EntityManager manager;

        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Map::Map(std::string textureId, int scale, int tileSize)
        {
            m_TextureId = textureId;
            m_Scale = scale;
            m_TileSize = tileSize;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Map::~Map()
        {
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
        {
            std::fstream mapFile;
            mapFile.open(filePath);

            for (int y = 0; y < mapSizeY; ++y) // y columns
            {
                for (int x = 0; x < mapSizeX; ++x) // x rows
                {
                    char ch;

                    mapFile.get(ch);
                    int sourceRectY = atoi(&ch) * m_TileSize;

                    mapFile.get(ch);
                    int sourceRectX = atoi(&ch) * m_TileSize;

                    AddTile(sourceRectX, sourceRectY, x * (m_Scale * m_TileSize), y * (m_Scale * m_TileSize));
                    mapFile.ignore();
                }
            }

            mapFile.close();
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Map::AddTile(int sourceX, int sourceY, int x, int y)
        {
            Entity& newTile(manager.AddEntity("Tile", eTILEMAP_LAYER));
            newTile.AddComponent<TileComponent>(sourceX, sourceY, x, y, m_TileSize, m_Scale, m_TextureId);
        }

    }
}
