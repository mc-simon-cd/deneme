# Open World Project - Çok Dilli Açık Dünya Oyun Projesi

## 📋 Genel Bakış

Bu proje, C, C++, C# ve TypeScript dillerini birleştirerek oluşturulmuş, açık lisanslı karakter varlıkları kullanan modüler bir açık dünya oyun motorudur.

## 🏗️ Mimari Yapı

```
OpenWorldProject/
├── src/
│   ├── c/              # C ile yazılmış düşük seviyeli sistemler
│   ├── cpp/            # C++ oyun motoru çekirdeği
│   └── cs/             # C# oyun mantığı (görevler, envanter)
├── include/            # Header dosyaları
├── assets/
│   ├── characters/     # CC0 lisanslı karakter modelleri
│   ├── textures/       # CC0 lisanslı dokular
│   └── models/         # 3D modeller
├── web/                # TypeScript web araçları
└── docs/               # Dokümantasyon
```

## 🎯 Dil Kullanımı

### C (src/c/)
- Temel veri yapıları
- Düşük seviyeli sistem işlemleri
- Bellek yönetimi
- Platform bağımsız katman

### C++ (src/cpp/)
- Oyun motoru çekirdeği
- Grafik render sistemi
- Fizik motoru
- Yüksek performans gerektiren işlemler

### C# (src/cs/)
- Oyun mantığı
- Görev sistemi
- Envanter yönetimi
- Diyalog sistemleri
- AI davranışları

### TypeScript (web/)
- Web tabanlı harita editörü
- Karakter yönetim paneli
- Veri görselleştirme araçları
- Admin arayüzleri

## 📦 Lisanslı Varlıklar

Proje şu kaynaklardan açık lisanslı varlıklar kullanır:

- **Kenney.nl** - CC0 lisanslı modeller ve dokular
- **OpenGameArt.org** - CC-BY, MIT lisanslı assetler
- **Mixamo** - Ücretsiz animasyonlar
- **Sketchfab** - CC lisanslı 3D modeller

## 🚀 Kurulum

### Gereksinimler
- CMake 3.15+
- GCC/Clang veya MSVC
- .NET 6.0 SDK
- Node.js 18+ ve npm

### Derleme

```bash
# C/C++ derlemesi
cd /workspace/OpenWorldProject
cmake -B build
cmake --build build

# C# derlemesi
cd src/cs
dotnet build

# TypeScript derlemesi
cd web
npm install
npm run build
```

## 📝 Kullanım Örnekleri

### C API
```c
CharacterManager mgr = {0};
Character hero;
character_init(&hero, 1, "Kahraman", CHAR_TYPE_HUMAN);
character_manager_add(&mgr, &hero);
```

### C++ API
```cpp
OpenWorld::OpenWorldManager world;
auto hero = std::make_unique<CharacterEntity>(1, "Kahraman", CHAR_TYPE_HUMAN);
world.addCharacter(std::move(hero));
```

### C# API
```csharp
var gameLogic = new OpenWorldGameLogic();
gameLogic.AddCharacter(1, "Kahraman", CharacterType.Human);
gameLogic.StartQuest("İlk Görev", player);
```

### TypeScript API
```typescript
const manager = new CharacterManager();
manager.addCharacter({
    id: 1,
    name: "Kahraman",
    type: CharacterType.Human,
    position: { x: 0, y: 0, z: 0 }
});
```

## 🔧 Geliştirme

### Proje Yapısını Genişletme

1. Yeni C modülleri için `src/c/` dizinine `.c` dosyası ekleyin
2. Yeni C++ sistemleri için `src/cpp/` dizinine `.cpp` dosyası ekleyin
3. C# oyun mantığı için `src/cs/` dizinine sınıf ekleyin
4. Web araçları için `web/src/` dizinine TypeScript dosyası ekleyin

### Test Etme

```bash
# C testi
gcc -DSTANDALONE_TEST src/c/character_manager.c -o test_c && ./test_c

# C++ testi
g++ -DSTANDALONE_TEST -std=c++17 src/cpp/open_world_engine.cpp -o test_cpp && ./test_cpp

# TypeScript testi
cd web && npm run build && node dist/index.js
```

## 📄 Lisans

- Kod: MIT License
- Assetler: İlgili kaynakların lisanslarına tabi (genellikle CC0, CC-BY)

## 🤝 Katkıda Bulunma

1. Projeyi fork edin
2. Yeni bir branch oluşturun
3. Değişikliklerinizi commit edin
4. Pull request gönderin

## 📞 İletişim

Sorularınız için issue açın veya tartışmalara katılın.

---

**Not:** Bu proje eğitim ve prototip amaçlıdır. Production ortamında kullanım için ek optimizasyonlar ve güvenlik önlemleri gereklidir.
