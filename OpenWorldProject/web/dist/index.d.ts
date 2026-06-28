/**
 * Open World Project - TypeScript Web Araçları
 * Karakter Editörü ve Yönetim Paneli
 * Lisans: MIT
 */
export declare enum CharacterType {
    Human = 0,
    Animal = 1,
    Monster = 2,
    NPC = 3
}
export interface Vector3 {
    x: number;
    y: number;
    z: number;
}
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
export declare class CharacterManager {
    private characters;
    /**
     * Yeni karakter ekle
     */
    addCharacter(character: CharacterData): boolean;
    /**
     * Karakter getir
     */
    getCharacter(id: number): CharacterData | undefined;
    /**
     * Karakter güncelle
     */
    updateCharacter(id: number, updates: Partial<CharacterData>): boolean;
    /**
     * Karakter sil
     */
    removeCharacter(id: number): boolean;
    /**
     * Tüm karakterleri listele
     */
    getAllCharacters(): CharacterData[];
    /**
     * Karakter sayısını al
     */
    getCount(): number;
    /**
     * Karakterleri JSON olarak dışa aktar
     */
    exportToJSON(): string;
    /**
     * JSON'dan karakterleri içe aktar
     */
    importFromJSON(jsonString: string): void;
}
export declare class MapEditor {
    private gridSize;
    private terrainData;
    constructor(size?: number);
    private initializeTerrain;
    setHeight(x: number, y: number, height: number): void;
    getHeight(x: number, y: number): number;
    exportTerrainData(): string;
}
//# sourceMappingURL=index.d.ts.map