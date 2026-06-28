/**
 * Open World Project - C++ Katmanı
 * Oyun Motoru Çekirdeği: Grafik, Fizik ve Render Sistemi
 * Lisans: MIT
 */

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "../include/character_data.h"

namespace OpenWorld {

// Modern C++ ile karakter sarmalayıcı
class CharacterEntity {
public:
    CharacterEntity(uint32_t id, const std::string& name, CharacterType type);
    
    void updatePosition(float x, float y, float z);
    void updateRotation(float pitch, float yaw, float roll);
    void render(); // Grafik motoru entegrasyonu
    
    uint32_t getId() const { return m_id; }
    const std::string& getName() const { return m_name; }
    CharacterType getType() const { return m_type; }
    Vector3 getPosition() const { return m_position; }
    
private:
    uint32_t m_id;
    std::string m_name;
    CharacterType m_type;
    Vector3 m_position;
    Vector3 m_rotation;
    float m_health;
    float m_speed;
    std::string m_modelPath;
    std::string m_texturePath;
};

// Açık Dünya Yöneticisi
class OpenWorldManager {
public:
    OpenWorldManager();
    ~OpenWorldManager();
    
    bool addCharacter(std::unique_ptr<CharacterEntity> character);
    CharacterEntity* getCharacter(uint32_t id);
    void removeCharacter(uint32_t id);
    
    void updateWorld(float deltaTime);
    void renderWorld();
    
    size_t getCharacterCount() const { return m_characters.size(); }
    
private:
    std::vector<std::unique_ptr<CharacterEntity>> m_characters;
    float m_worldTime;
};

// Grafik Motoru Arayüzü (Vulkan/OpenGL/DirectX için)
class GraphicsEngine {
public:
    virtual bool initialize(int width, int height) = 0;
    virtual void renderCharacter(const CharacterEntity& character) = 0;
    virtual void shutdown() = 0;
};

// Fizik Motoru Arayüzü
class PhysicsEngine {
public:
    virtual void update(CharacterEntity& character, float deltaTime) = 0;
    virtual bool checkCollision(const Vector3& pos1, const Vector3& pos2) = 0;
};

} // namespace OpenWorld
