export interface Position {
    x: number;
    y: number;
    z: number;
}

export interface Character {
    id: number;
    name: string;
    type: string; // 'Hero', 'Villager', 'Enemy' vb.
    position: Position;
    health: number;
    isActive: boolean;
}

export class CharacterManager {
    private characters: Map<number, Character>;
    private nextId: number = 1;

    constructor() {
        this.characters = new Map();
    }

    addCharacter(name: string, type: string, position: Position = { x: 0, y: 0, z: 0 }): Character {
        const newChar: Character = {
            id: this.nextId++,
            name,
            type,
            position,
            health: 100,
            isActive: true
        };
        this.characters.set(newChar.id, newChar);
        console.log(`Karakter eklendi: ${name} (ID: ${newChar.id})`);
        return newChar;
    }

    getCharacter(id: number): Character | undefined {
        return this.characters.get(id);
    }

    getAllCharacters(): Character[] {
        return Array.from(this.characters.values());
    }

    removeCharacter(id: number): boolean {
        return this.characters.delete(id);
    }

    updatePosition(id: number, newPos: Position): boolean {
        const char = this.characters.get(id);
        if (char) {
            char.position = newPos;
            return true;
        }
        return false;
    }
}

// Test fonksiyonu
export function runTests() {
    console.log("--- TypeScript Tip Güvenliği ve Mantık Testi ---");
    
    const manager = new CharacterManager();
    
    // Karakter ekleme
    const hero = manager.addCharacter("Kahraman", "Hero", { x: 10, y: 0, z: 5 });
    const villager = manager.addCharacter("Köylü", "Villager", { x: -5, y: 0, z: 10 });
    
    console.log(`Toplam karakter sayısı: ${manager.getAllCharacters().length}`);
    
    // Pozisyon güncelleme
    manager.updatePosition(hero.id, { x: 15, y: 2, z: 8 });
    const updatedHero = manager.getCharacter(hero.id);
    console.log(`${updatedHero?.name} yeni konum: (${updatedHero?.position.x}, ${updatedHero?.position.y}, ${updatedHero?.position.z})`);
    
    // Listeleme
    console.log("\nTüm Karakterler:");
    manager.getAllCharacters().forEach(c => {
        console.log(`- [${c.type}] ${c.name} @ (${c.position.x}, ${c.position.z})`);
    });
    
    console.log("\nTest tamamlandı.");
}

// Eğer doğrudan çalıştırılıyorsa testleri yap
if (require.main === module) {
    runTests();
}
