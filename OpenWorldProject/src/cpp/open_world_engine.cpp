/**
 * Open World Project - C++ Implementasyonu
 * Oyun Motoru Çekirdeği
 */

#include "open_world_engine.hpp"
#include <iostream>
#include <algorithm>

namespace OpenWorld {

// CharacterEntity Implementasyonu
CharacterEntity::CharacterEntity(uint32_t id, const std::string& name, CharacterType type)
    : m_id(id), m_name(name), m_type(type), m_health(100.0f), m_speed(5.0f) {
    m_position = {0.0f, 0.0f, 0.0f};
    m_rotation = {0.0f, 0.0f, 0.0f};
    m_modelPath = "assets/characters/default_character.fbx";
    m_texturePath = "assets/textures/default_texture.png";
}

void CharacterEntity::updatePosition(float x, float y, float z) {
    m_position = {x, y, z};
}

void CharacterEntity::updateRotation(float pitch, float yaw, float roll) {
    m_rotation = {pitch, yaw, roll};
}

void CharacterEntity::render() {
    // Grafik motoru entegrasyonu buraya gelecek
    std::cout << "Rendering character: " << m_name 
              << " at (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")" << std::endl;
}

// OpenWorldManager Implementasyonu
OpenWorldManager::OpenWorldManager() : m_worldTime(0.0f) {}

OpenWorldManager::~OpenWorldManager() {
    m_characters.clear();
}

bool OpenWorldManager::addCharacter(std::unique_ptr<CharacterEntity> character) {
    if (!character) return false;
    m_characters.push_back(std::move(character));
    return true;
}

CharacterEntity* OpenWorldManager::getCharacter(uint32_t id) {
    auto it = std::find_if(m_characters.begin(), m_characters.end(),
        [id](const std::unique_ptr<CharacterEntity>& chr) {
            return chr->getId() == id;
        });
    
    return (it != m_characters.end()) ? it->get() : nullptr;
}

void OpenWorldManager::removeCharacter(uint32_t id) {
    m_characters.erase(
        std::remove_if(m_characters.begin(), m_characters.end(),
            [id](const std::unique_ptr<CharacterEntity>& chr) {
                return chr->getId() == id;
            }),
        m_characters.end());
}

void OpenWorldManager::updateWorld(float deltaTime) {
    m_worldTime += deltaTime;
    
    // Tüm karakterleri güncelle
    for (auto& character : m_characters) {
        // Fizik ve AI güncellemeleri buraya gelecek
    }
}

void OpenWorldManager::renderWorld() {
    for (auto& character : m_characters) {
        character->render();
    }
}

} // namespace OpenWorld

// Test main fonksiyonu
#ifdef STANDALONE_TEST
int main() {
    using namespace OpenWorld;
    
    OpenWorldManager world;
    
    auto hero = std::make_unique<CharacterEntity>(1, "Kahraman", CHAR_TYPE_HUMAN);
    hero->updatePosition(10.0f, 0.0f, 5.0f);
    
    auto npc = std::make_unique<CharacterEntity>(2, "Köylü", CHAR_TYPE_NPC);
    npc->updatePosition(-5.0f, 0.0f, 10.0f);
    
    world.addCharacter(std::move(hero));
    world.addCharacter(std::move(npc));
    
    std::cout << "Dünyada " << world.getCharacterCount() << " karakter var." << std::endl;
    
    world.renderWorld();
    
    CharacterEntity* found = world.getCharacter(1);
    if (found) {
        std::cout << "Karakter bulundu: " << found->getName() << std::endl;
    }
    
    return 0;
}
#endif
