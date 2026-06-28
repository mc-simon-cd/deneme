export interface Position {
    x: number;
    y: number;
    z: number;
}
export interface Character {
    id: number;
    name: string;
    type: string;
    position: Position;
    health: number;
    isActive: boolean;
}
export declare class CharacterManager {
    private characters;
    private nextId;
    constructor();
    addCharacter(name: string, type: string, position?: Position): Character;
    getCharacter(id: number): Character | undefined;
    getAllCharacters(): Character[];
    removeCharacter(id: number): boolean;
    updatePosition(id: number, newPos: Position): boolean;
}
export declare function runTests(): void;
//# sourceMappingURL=types.d.ts.map