/**
 * Open World Project - TypeScript Web Araçları
 * Karakter Editörü ve Yönetim Paneli
 * Lisans: MIT
 */

// Karakter tip tanımlamaları
export enum CharacterType {
    Human = 0,
    Animal = 1,
    Monster = 2,
    NPC = 3
}

// 3D Vektör interface'i
export interface Vector3 {
    x: number;
    y: number;
    z: number;
}

// Karakter veri interface'i
export interface CharacterData {
    id: number;
    name: string;
    type: CharacterType;
    position: Vector3;
    rotation: Vector3;
    health: number;
    speed: number;
    isActive: boolean;
    modelPath: string;
    texturePath: string;
}

// Açık dünya karakter yöneticisi (Web arayüzü için)
export class CharacterManager {
    private characters: Map<number, CharacterData> = new Map();

    /**
     * Yeni karakter ekle
     */
    addCharacter(character: CharacterData): boolean {
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
    getCharacter(id: number): CharacterData | undefined {
        return this.characters.get(id);
    }

    /**
     * Karakter güncelle
     */
    updateCharacter(id: number, updates: Partial<CharacterData>): boolean {
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
    removeCharacter(id: number): boolean {
        return this.characters.delete(id);
    }

    /**
     * Tüm karakterleri listele
     */
    getAllCharacters(): CharacterData[] {
        return Array.from(this.characters.values());
    }

    /**
     * Karakter sayısını al
     */
    getCount(): number {
        return this.characters.size;
    }

    /**
     * Karakterleri JSON olarak dışa aktar
     */
    exportToJSON(): string {
        return JSON.stringify(this.getAllCharacters(), null, 2);
    }

    /**
     * JSON'dan karakterleri içe aktar
     */
    importFromJSON(jsonString: string): void {
        const characters = JSON.parse(jsonString) as CharacterData[];
        characters.forEach(char => this.addCharacter(char));
    }
}

// Harita editörü yardımcı sınıfı
export class MapEditor {
    private gridSize: number = 100;
    private terrainData: number[][] = [];

    constructor(size: number = 100) {
        this.gridSize = size;
        this.initializeTerrain();
    }

    private initializeTerrain(): void {
        this.terrainData = Array(this.gridSize).fill(0).map(() => 
            Array(this.gridSize).fill(0)
        );
    }

    setHeight(x: number, y: number, height: number): void {
        if (x >= 0 && x < this.gridSize && y >= 0 && y < this.gridSize) {
            this.terrainData[x][y] = height;
        }
    }

    getHeight(x: number, y: number): number {
        if (x >= 0 && x < this.gridSize && y >= 0 && y < this.gridSize) {
            return this.terrainData[x][y];
        }
        return 0;
    }

    exportTerrainData(): string {
        return JSON.stringify(this.terrainData);
    }
}

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
