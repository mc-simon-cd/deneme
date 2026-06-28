"use strict";
/**
 * Open World Project - TypeScript Web Araçları
 * Karakter Editörü ve Yönetim Paneli
 * Lisans: MIT
 */
Object.defineProperty(exports, "__esModule", { value: true });
exports.MapEditor = exports.CharacterManager = exports.CharacterType = void 0;
// Karakter tip tanımlamaları
var CharacterType;
(function (CharacterType) {
    CharacterType[CharacterType["Human"] = 0] = "Human";
    CharacterType[CharacterType["Animal"] = 1] = "Animal";
    CharacterType[CharacterType["Monster"] = 2] = "Monster";
    CharacterType[CharacterType["NPC"] = 3] = "NPC";
})(CharacterType || (exports.CharacterType = CharacterType = {}));
// Açık dünya karakter yöneticisi (Web arayüzü için)
class CharacterManager {
    constructor() {
        this.characters = new Map();
    }
    /**
     * Yeni karakter ekle
     */
    addCharacter(character) {
        if (this.characters.has(character.id)) {
            console.warn(`Karakter ID ${character.id} zaten mevcut!`);
            return false;
        }
        this.characters.set(character.id, character);
        console.log(`Karakter eklendi: ${character.name}`);
        return true;
    }
    /**
     * Karakter getir
     */
    getCharacter(id) {
        return this.characters.get(id);
    }
    /**
     * Karakter güncelle
     */
    updateCharacter(id, updates) {
        const character = this.characters.get(id);
        if (!character) {
            return false;
        }
        Object.assign(character, updates);
        return true;
    }
    /**
     * Karakter sil
     */
    removeCharacter(id) {
        return this.characters.delete(id);
    }
    /**
     * Tüm karakterleri listele
     */
    getAllCharacters() {
        return Array.from(this.characters.values());
    }
    /**
     * Karakter sayısını al
     */
    getCount() {
        return this.characters.size;
    }
    /**
     * Karakterleri JSON olarak dışa aktar
     */
    exportToJSON() {
        return JSON.stringify(this.getAllCharacters(), null, 2);
    }
    /**
     * JSON'dan karakterleri içe aktar
     */
    importFromJSON(jsonString) {
        const characters = JSON.parse(jsonString);
        characters.forEach(char => this.addCharacter(char));
    }
}
exports.CharacterManager = CharacterManager;
// Harita editörü yardımcı sınıfı
class MapEditor {
    constructor(size = 100) {
        this.gridSize = 100;
        this.terrainData = [];
        this.gridSize = size;
        this.initializeTerrain();
    }
    initializeTerrain() {
        this.terrainData = Array(this.gridSize).fill(0).map(() => Array(this.gridSize).fill(0));
    }
    setHeight(x, y, height) {
        if (x >= 0 && x < this.gridSize && y >= 0 && y < this.gridSize) {
            this.terrainData[x][y] = height;
        }
    }
    getHeight(x, y) {
        if (x >= 0 && x < this.gridSize && y >= 0 && y < this.gridSize) {
            return this.terrainData[x][y];
        }
        return 0;
    }
    exportTerrainData() {
        return JSON.stringify(this.terrainData);
    }
}
exports.MapEditor = MapEditor;
// Örnek kullanım
if (require.main === module) {
    const manager = new CharacterManager();
    // Örnek karakterler ekle
    manager.addCharacter({
        id: 1,
        name: "Kahraman",
        type: CharacterType.Human,
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 0, y: 0, z: 0 },
        health: 100,
        speed: 5,
        isActive: true,
        modelPath: "assets/characters/hero.fbx",
        texturePath: "assets/textures/hero.png"
    });
    manager.addCharacter({
        id: 2,
        name: "Köylü",
        type: CharacterType.NPC,
        position: { x: 10, y: 0, z: 5 },
        rotation: { x: 0, y: 90, z: 0 },
        health: 50,
        speed: 3,
        isActive: true,
        modelPath: "assets/characters/villager.fbx",
        texturePath: "assets/textures/villager.png"
    });
    console.log(`Toplam karakter sayısı: ${manager.getCount()}`);
    console.log("Karakter listesi:");
    console.log(manager.exportToJSON());
    // Harita editörü örneği
    const mapEditor = new MapEditor(50);
    mapEditor.setHeight(10, 10, 5);
    mapEditor.setHeight(11, 10, 6);
    console.log("\nHarita yükseklik verisi (örnek):");
    console.log(`(10,10) yüksekliği: ${mapEditor.getHeight(10, 10)}`);
}
//# sourceMappingURL=index.js.map