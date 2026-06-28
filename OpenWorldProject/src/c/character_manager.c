/**
 * Open World Project - C Implementasyonu
 * Karakter yönetim sistemi
 */

#include "character_data.h"
#include <string.h>
#include <stdio.h>

void character_init(Character* chr, uint32_t id, const char* name, CharacterType type) {
    if (!chr) return;
    
    chr->id = id;
    strncpy(chr->name, name, MAX_NAME_LENGTH - 1);
    chr->name[MAX_NAME_LENGTH - 1] = '\0';
    chr->type = type;
    chr->position = (Vector3){0.0f, 0.0f, 0.0f};
    chr->rotation = (Vector3){0.0f, 0.0f, 0.0f};
    chr->health = 100.0f;
    chr->speed = 5.0f;
    chr->isActive = true;
    
    // Varsayılan CC0 lisanslı asset yolları
    strcpy(chr->modelPath, "assets/characters/default_character.fbx");
    strcpy(chr->texturePath, "assets/textures/default_texture.png");
}

void character_update_position(Character* chr, Vector3 newPos) {
    if (!chr) return;
    chr->position = newPos;
}

bool character_manager_add(CharacterManager* mgr, Character* chr) {
    if (!mgr || !chr || mgr->count >= MAX_CHARACTERS) {
        return false;
    }
    
    mgr->characters[mgr->count] = *chr;
    mgr->count++;
    return true;
}

Character* character_manager_get(CharacterManager* mgr, uint32_t id) {
    if (!mgr) return NULL;
    
    for (uint32_t i = 0; i < mgr->count; i++) {
        if (mgr->characters[i].id == id) {
            return &mgr->characters[i];
        }
    }
    return NULL;
}

void character_manager_remove(CharacterManager* mgr, uint32_t id) {
    if (!mgr) return;
    
    for (uint32_t i = 0; i < mgr->count; i++) {
        if (mgr->characters[i].id == id) {
            // Silinen karakterin yerine son karakteri koy
            if (i != mgr->count - 1) {
                mgr->characters[i] = mgr->characters[mgr->count - 1];
            }
            mgr->count--;
            return;
        }
    }
}

// Test fonksiyonu
#ifdef STANDALONE_TEST
int main() {
    CharacterManager mgr = {0};
    Character hero;
    
    character_init(&hero, 1, "Kahraman", CHAR_TYPE_HUMAN);
    character_manager_add(&mgr, &hero);
    
    Character* found = character_manager_get(&mgr, 1);
    if (found) {
        printf("Karakter bulundu: %s (ID: %u)\n", found->name, found->id);
        printf("Konum: (%.2f, %.2f, %.2f)\n", 
               found->position.x, found->position.y, found->position.z);
    }
    
    return 0;
}
#endif
