#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "../../include/terrain_data.h"

// Basit bir Perlin Noise benzeri yükseklik fonksiyonu (Gerçek projede gürültü kütüphanesi kullanılır)
float get_height(float x, float z) {
    return sin(x * 0.1) * cos(z * 0.1) * 10.0f + 5.0f;
}

class TerrainChunk {
public:
    int chunkX, chunkZ;
    int size;
    std::vector<float> heights;

    TerrainChunk(int cx, int cz, int s) : chunkX(cx), chunkZ(cz), size(s) {
        heights.resize(size * size);
        generate();
    }

    void generate() {
        std::cout << "Generating chunk at (" << chunkX << ", " << chunkZ << ")..." << std::endl;
        for (int z = 0; z < size; ++z) {
            for (int x = 0; x < size; ++x) {
                float worldX = chunkX * size + x;
                float worldZ = chunkZ * size + z;
                heights[z * size + x] = get_height(worldX, worldZ);
            }
        }
    }

    float getHeightAt(int localX, int localZ) {
        if (localX >= 0 && localX < size && localZ >= 0 && localZ < size) {
            return heights[localZ * size + localX];
        }
        return 0.0f;
    }
};

class WorldManager {
private:
    std::map<std::pair<int, int>, TerrainChunk*> loadedChunks;
    int chunkSize;
    int renderDistance;

public:
    WorldManager(int cSize, int rDist) : chunkSize(cSize), renderDistance(rDist) {}

    ~WorldManager() {
        for (auto& pair : loadedChunks) {
            delete pair.second;
        }
    }

    void updatePlayerPosition(float playerX, float playerZ) {
        int currentChunkX = floor(playerX / chunkSize);
        int currentChunkZ = floor(playerZ / chunkSize);

        // Yeni chunkları yükle
        for (int x = -renderDistance; x <= renderDistance; ++x) {
            for (int z = -renderDistance; z <= renderDistance; ++z) {
                int targetX = currentChunkX + x;
                int targetZ = currentChunkZ + z;
                auto key = std::make_pair(targetX, targetZ);

                if (loadedChunks.find(key) == loadedChunks.end()) {
                    loadedChunks[key] = new TerrainChunk(targetX, targetZ, chunkSize);
                }
            }
        }

        // Uzak chunkları temizle (Basit LRU mantığı yerine hepsini tutup sadece demo için yazdırıyoruz)
        // Gerçek projede burada silme işlemi yapılır.
        std::cout << "Active Chunks Count: " << loadedChunks.size() << std::endl;
    }

    float getTerrainHeight(float x, float z) {
        int cx = floor(x / chunkSize);
        int cz = floor(z / chunkSize);
        int lx = (int)x % chunkSize;
        int lz = (int)z % chunkSize;
        if (lx < 0) lx += chunkSize;
        if (lz < 0) lz += chunkSize;

        auto key = std::make_pair(cx, cz);
        if (loadedChunks.find(key) != loadedChunks.end()) {
            return loadedChunks[key]->getHeightAt(lx, lz);
        }
        return 0.0f; // Yüklenmemiş alan
    }
};

int main() {
    std::cout << "--- C++ Terrain System Test ---" << std::endl;
    WorldManager world(16, 2); // 16x16 chunklar, 2 birim görüş mesafesi

    // Oyuncu hareketi simülasyonu
    world.updatePlayerPosition(5.0f, 5.0f);
    float h1 = world.getTerrainHeight(5.0f, 5.0f);
    std::cout << "Height at (5, 5): " << h1 << std::endl;

    world.updatePlayerPosition(20.0f, 20.0f); // Farklı chunk'a geçiş
    float h2 = world.getTerrainHeight(20.0f, 20.0f);
    std::cout << "Height at (20, 20): " << h2 << std::endl;

    return 0;
}
