#ifndef TERRAIN_DATA_H
#define TERRAIN_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

// C tarafında kullanılacak temel yükseklik verisi yapısı
typedef struct {
    float x, z;
    float height;
    int biomeType; // 0: Çimen, 1: Taş, 2: Su, 3: Kar
} TerrainVertex;

// Yükseklik hesaplama fonksiyonu (C++ ile paylaşılabilir)
float calculate_height(float x, float z);

#ifdef __cplusplus
}
#endif

#endif // TERRAIN_DATA_H
