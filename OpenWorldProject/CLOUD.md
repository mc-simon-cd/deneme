# ☁️ Açık Dünya Projesi - Bulut Dokümantasyonu

## 📋 Proje Özeti

C, C++, C# ve TypeScript dillerini birleştiren, açık lisanslı (CC0) karakterlerle desteklenen çok katmanlı bir açık dünya oyun projesi.

### 🎯 Temel Özellikler
- **Çok Dilli Mimari:** Her dilin güçlü yönlerinden yararlanma
- **Açık Lisanslı:** Tüm assetler CC0/MIT lisanslı
- **Modüler Yapı:** Kolayca genişletilebilir sistem
- **Cross-Platform:** Windows, Linux, macOS desteği

---

## 🏗️ Mimari Katmanlar

| Katman | Dil | Sorumluluk |
|--------|-----|------------|
| **Core** | C | Bellek yönetimi, temel veri yapıları |
| **Engine** | C++ | Render, fizik, terrain sistemi |
| **Logic** | C# | Görevler, envanter, AI davranışları |
| **Tools** | TypeScript | Web paneli, harita editörü |
| **AI** | Python | NPC durum makineleri |

---

## 📂 Dizin Yapısı

```
OpenWorldProject/
├── src/
│   ├── c/                  # C: character_manager.c
│   ├── cpp/                # C++: engine, terrain, physics
│   ├── python/             # Python: ai_npc.py
│   └── cs/                 # C#: GameLogic.cs
├── web/
│   └── src/                # TS: types.ts, server.ts
├── include/                # Header dosyaları
├── assets/                 # CC0 modeller, dokular
├── build/                  # Derlenmiş binary'ler
├── docs/                   # Dokümantasyon
├── PROGRESS.md             # İlerleme raporu
├── CLOUD.md                # Bu dosya
└── .cloudignore            # Bulut ignore kuralları
```

---

## 🚀 Kurulum Talimatları

### Gereksinimler
- GCC/G++ 12+
- Python 3.8+
- Node.js 18+ (TypeScript için)
- .NET SDK 7+ (C# için - opsiyonel)
- CMake 3.20+

### Adım 1: C/C++ Modülleri
```bash
cd OpenWorldProject
mkdir -p build && cd build

# Karakter yönetimi (C)
gcc -o char_manager ../src/c/character_manager.c
./char_manager

# Fizik sistemi (C++)
g++ -std=c++17 -o physics_system ../src/cpp/physics_system.cpp
./physics_system

# Terrain sistemi (C++)
g++ -std=c++17 -o terrain ../src/cpp/terrain_system.cpp
./terrain
```

### Adım 2: Python AI
```bash
python3 src/python/ai_npc.py
```

### Adım 3: TypeScript Web Paneli
```bash
cd web
npm install
npm run build
npm start
```

### Adım 4: C# Oyun Mantığı (Opsiyonel)
```bash
cd src/cs
dotnet run
```

---

## 🎮 Kullanım Örnekleri

### C - Karakter Ekleme
```c
Character* hero = create_character(1, "Kahraman", 0, 0, 0);
move_character(hero, 10.5f, 0, 5.2f);
```

### C++ - Fizik Objesi
```cpp
PhysicsObject player("Oyuncu", Vector3(0, 5, 0));
player.velocity = Vector3(1, 0, 0);
player.update(0.016f);
```

### Python - NPC Davranışı
```python
npc = NPC("Köylü", Vector3(10, 0, 10))
npc.update(player_pos, delta_time)
```

### TypeScript - API Çağrısı
```typescript
const chars = await api.getCharacters();
const height = await api.getHeightAt(50, 50);
```

---

## 📄 Lisans Bilgileri

| Bileşen | Lisans |
|---------|--------|
| Kod (C/C++/C#/TS/Py) | MIT |
| Karakter Modelleri | CC0 (Kenney, OpenGameArt) |
| Dokular | CC0 / CC-BY |
| Ses Dosyaları | CC0 |

Detaylı lisans bilgileri için `docs/ASSET_LICENSES.md` dosyasına bakınız.

---

## 🔗 Bağlantılar

- **İlerleme Raporu:** [PROGRESS.md](./PROGRESS.md)
- **Asset Lisansları:** [docs/ASSET_LICENSES.md](./docs/ASSET_LICENSES.md)
- **Geliştirme Günlüğü:** [docs/DEV_LOG.md](./docs/DEV_LOG.md)

---

## 📞 Destek

Sorularınız için GitHub Issues açabilir veya dokümantasyonu inceleyebilirsiniz.
