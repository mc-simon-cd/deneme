/**
 * Open World Project - C Katmanı
 * Temel veri yapıları ve düşük seviyeli sistem işlemleri
 * Lisans: MIT / CC0
 */

#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 64
#define MAX_CHARACTERS 1000

// Karakter tipi tanımlamaları
typedef enum {
    CHAR_TYPE_HUMAN,
    CHAR_TYPE_ANIMAL,
    CHAR_TYPE_MONSTER,
    CHAR_TYPE_NPC
} CharacterType;

// 3D Konum yapısı
typedef struct {
    float x;
    float y;
    float z;
} Vector3;

// Açık lisanslı karakter verisi
typedef struct {
    uint32_t id;
    char name[MAX_NAME_LENGTH];
    CharacterType type;
    Vector3 position;
    Vector3 rotation;
    float health;
    float speed;
    bool isActive;
    char modelPath[256];  // CC0 lisanslı model yolu
    char texturePath[256]; // CC0 lisanslı doku yolu
} Character;

// Karakter yöneticisi
typedef struct {
    Character characters[MAX_CHARACTERS];
    uint32_t count;
} CharacterManager;

// Fonksiyon bildirimleri
void character_init(Character* chr, uint32_t id, const char* name, CharacterType type);
void character_update_position(Character* chr, Vector3 newPos);
bool character_manager_add(CharacterManager* mgr, Character* chr);
Character* character_manager_get(CharacterManager* mgr, uint32_t id);
void character_manager_remove(CharacterManager* mgr, uint32_t id);

#endif // CHARACTER_DATA_H
