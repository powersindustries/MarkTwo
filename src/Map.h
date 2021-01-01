#pragma once
#include <string>

namespace MarkTwo
{
    namespace GameCore
    {
        class Map
        {
        public:
            Map(std::string textureId, int scale, int tileSize);
            ~Map();

            void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
            void AddTile(int sourceX, int sourceY, int x, int y);

        private:
            std::string m_TextureId;
            int m_Scale;
            int m_TileSize;

        };

    }
}
