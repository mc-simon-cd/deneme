/**
 * Açık Dünya Projesi - C++ Fizik Sistemi
 * Basit collision detection ve fizik hesaplamaları
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <memory>

// 3D Vektör sınıfı
struct Vector3 {
    float x, y, z;
    
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    
    float length() const {
        return std::sqrt(x*x + y*y + z*z);
    }
    
    Vector3 normalize() const {
        float len = length();
        if (len > 0) {
            return Vector3(x/len, y/len, z/len);
        }
        return *this;
    }
    
    float distanceTo(const Vector3& other) const {
        return (*this - other).length();
    }
};

// Bounding Box için AABB (Axis-Aligned Bounding Box)
struct AABB {
    Vector3 min;
    Vector3 max;
    
    AABB(const Vector3& center, float size) 
        : min(center.x - size/2, center.y - size/2, center.z - size/2),
          max(center.x + size/2, center.y + size/2, center.z + size/2) {}
    
    bool intersects(const AABB& other) const {
        return (min.x <= other.max.x && max.x >= other.min.x) &&
               (min.y <= other.max.y && max.y >= other.min.y) &&
               (min.z <= other.max.z && max.z >= other.min.z);
    }
};

// Fizik objesi
class PhysicsObject {
public:
    std::string name;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    float mass;
    float boundingSize;
    bool isKinematic;
    
    PhysicsObject(const std::string& name, const Vector3& pos, float mass = 1.0f, bool kinematic = false)
        : name(name), position(pos), mass(mass), boundingSize(1.0f), isKinematic(kinematic) {}
    
    AABB getBoundingBox() const {
        return AABB(position, boundingSize);
    }
    
    void update(float deltaTime) {
        if (isKinematic) return;
        
        // Velocity güncelleme (acceleration uygula)
        velocity = velocity + acceleration * deltaTime;
        
        // Hava sürtünmesi
        velocity = velocity * 0.98f;
        
        // Position güncelleme
        position = position + velocity * deltaTime;
        
        // Yerçekimi
        if (position.y > 0) {
            acceleration.y -= 9.8f * deltaTime;
        } else {
            position.y = 0;
            velocity.y = 0;
            acceleration.y = 0;
        }
    }
};

// Collision Manager
class CollisionManager {
private:
    std::vector<PhysicsObject*> objects;
    
public:
    void addObject(PhysicsObject* obj) {
        objects.push_back(obj);
    }
    
    std::vector<std::pair<std::string, std::string>> checkCollisions() {
        std::vector<std::pair<std::string, std::string>> collisions;
        
        for (size_t i = 0; i < objects.size(); ++i) {
            for (size_t j = i + 1; j < objects.size(); ++j) {
                AABB box1 = objects[i]->getBoundingBox();
                AABB box2 = objects[j]->getBoundingBox();
                
                if (box1.intersects(box2)) {
                    collisions.push_back({objects[i]->name, objects[j]->name});
                    std::cout << "[COLLISION] " << objects[i]->name 
                              << " <-> " << objects[j]->name << std::endl;
                }
            }
        }
        
        return collisions;
    }
    
    void clear() {
        objects.clear();
    }
};

int main() {
    std::cout << "=== C++ Fizik Sistemi Testi ===" << std::endl << std::endl;
    
    // Fizik objeleri oluştur
    PhysicsObject player("Oyuncu", Vector3(0, 5, 0), 70.0f);
    PhysicsObject enemy("Düşman", Vector3(2, 0, 3), 50.0f);
    PhysicsObject chest("Sandık", Vector3(10, 0, 10), 0, true); // Kinematic (hareket etmez)
    PhysicsObject projectile("Ok", Vector3(0, 5, 1), 0.1f);
    
    // Projectile'a hız ver
    projectile.velocity = Vector3(0, 0, 10);
    
    CollisionManager collisionMgr;
    collisionMgr.addObject(&player);
    collisionMgr.addObject(&enemy);
    collisionMgr.addObject(&chest);
    collisionMgr.addObject(&projectile);
    
    // Simülasyon döngüsü
    float deltaTime = 0.016f; // ~60 FPS
    
    for (int frame = 0; frame < 10; ++frame) {
        std::cout << "\n--- Frame " << (frame + 1) << " ---" << std::endl;
        
        // Fizik güncellemesi
        player.update(deltaTime);
        enemy.update(deltaTime);
        projectile.update(deltaTime);
        
        // Pozisyonları yazdır
        std::cout << "Oyuncu: (" << player.position.x << ", " 
                  << player.position.y << ", " << player.position.z << ")" << std::endl;
        std::cout << "Ok: (" << projectile.position.x << ", " 
                  << projectile.position.y << ", " << projectile.position.z << ")" << std::endl;
        
        // Collision kontrolü
        collisionMgr.checkCollisions();
    }
    
    std::cout << "\n=== Mesafe Hesaplama Testi ===" << std::endl;
    float dist = player.position.distanceTo(enemy.position);
    std::cout << "Oyuncu-Düşman mesafesi: " << dist << " birim" << std::endl;
    
    std::cout << "\n=== Test Tamamlandı ===" << std::endl;
    
    return 0;
}
