# ☁️ Open World Project - Cloud Dokümantasyonu

## Proje Özeti
Bu proje, C, C++, C# ve TypeScript dillerinin birlikte kullanıldığı, açık lisanslı (CC0, MIT) karakter varlıklarıyla desteklenen modüler bir **Açık Dünya (Open World)** oyun motoru ve altyapısıdır.

### 🏗️ Mimari Katmanlar

| Katman | Dil | Sorumluluk | Durum |
|--------|-----|------------|-------|
| **Core** | C++ | Oyun döngüsü, Render, Fizik, Terrain | ✅ Aktif |
| **System** | C | Bellek yönetimi, Veri yapıları, Network | ✅ Aktif |
| **Logic** | C# | Görevler, Envanter, AI, UI Mantığı | ⚠️ Hazır |
| **Tools** | TypeScript | Web Editörü, Debug Paneli, API | ✅ Aktif |

### 📂 Dizin Yapısı

```text
OpenWorldProject/
├── src/
│   ├── c/                  # C sistem kütüphaneleri
│   ├── cpp/                # C++ motor çekirdeği
│   └── cs/                 # C# oyun mantığı
├── include/                # Paylaşılan header dosyaları
├── web/                    # TypeScript web araçları
├── assets/                 # 3D Modeller, Dokular (CC0)
├── docs/                   # Teknik dokümantasyon
├── build/                  # Derleme çıktıları (GitIgnore)
├── CMakeLists.txt          # C++ ve C build konfigürasyonu
├── PROGRESS.md             # Geliştirme ilerleme raporu
└── README.md               # Genel proje açıklaması
```

### 🛠️ Kurulum ve Çalıştırma

#### 1. Gereksinimler
- **C/C++:** GCC/Clang, CMake (>3.20)
- **C#:** .NET SDK (>6.0)
- **TS:** Node.js (>18), npm/yarn

#### 2. Derleme (C/C++)
```bash
mkdir build && cd build
cmake ..
make
./open_world_engine
```

#### 3. Web Aracı (TypeScript)
```bash
cd web
npm install
npm run dev
# http://localhost:3000 adresinde çalışır
```

#### 4. Oyun Mantığı (C#)
```bash
dotnet run --project src/cs/OpenWorld.csproj
```

### 🎮 Temel Özellikler
- **Dinamik Terrain:** 16x16 chunk sistemi ile sonsuz dünya simülasyonu.
- **Çok Dilli Yapı:** Her dilin güçlü yönlerini kullanan hibrit mimari.
- **Açık Kaynak Varlıklar:** Telif hakkı sorunu olmayan CC0 karakterler.
- **Web Entegrasyonu:** Tarayıcı üzerinden dünya düzenleme ve izleme.

### 📄 Lisans
- **Kod:** MIT License
- **Varlıklar (Assets):** CC0 1.0 Universal (Kullanılan asset'in kaynağına göre değişebilir, bkz: `docs/ASSET_LICENSES.md`)

### 🤝 Katkıda Bulunma
1. Projeyi fork edin.
2. Yeni bir branch oluşturun (`feature/yeni-ozellik`).
3. Değişikliklerinizi commit edin.
4. Pull Request gönderin.

---
*Bu dokümantasyon bulut ortamında senkronize edilmek üzere hazırlanmıştır.*
