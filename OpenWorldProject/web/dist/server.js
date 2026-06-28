"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const types_js_1 = require("./types.js");
const app = (0, express_1.default)();
const PORT = 3000;
app.use(express_1.default.json());
// Basit bir karakter yöneticisi (In-memory)
const charManager = new types_js_1.CharacterManager();
// API: Tüm karakterleri listele
app.get('/api/characters', (req, res) => {
    const characters = charManager.getAllCharacters();
    res.json({ success: true, count: characters.length, data: characters });
});
// API: Yeni karakter ekle
app.post('/api/characters', (req, res) => {
    const { name, type, position } = req.body;
    if (!name || !type) {
        return res.status(400).json({ success: false, error: 'İsim ve tip gereklidir.' });
    }
    const newChar = charManager.addCharacter(name, type, position);
    res.status(201).json({ success: true, data: newChar });
});
// API: Karakter sil
app.delete('/api/characters/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const removed = charManager.removeCharacter(id);
    if (removed) {
        res.json({ success: true, message: 'Karakter silindi.' });
    }
    else {
        res.status(404).json({ success: false, error: 'Karakter bulunamadı.' });
    }
});
// API: Harita verisi (Basit grid)
app.get('/api/map/height', (req, res) => {
    const x = parseFloat(req.query.x) || 0;
    const z = parseFloat(req.query.z) || 0;
    // Basit matematiksel yükseklik fonksiyonu
    const height = Math.sin(x * 0.1) * Math.cos(z * 0.1) * 10 + 5;
    res.json({
        success: true,
        coordinates: { x, z },
        height: parseFloat(height.toFixed(2))
    });
});
// Statik dosyalar için (Frontend editörü varsa)
app.use(express_1.default.static('public'));
app.listen(PORT, () => {
    console.log(`🌍 Açık Dünya Yönetim Sunucusu çalışıyor: http://localhost:${PORT}`);
    console.log(`API Endpointleri:`);
    console.log(`  GET  /api/characters`);
    console.log(`  POST /api/characters`);
    console.log(`  DELETE /api/characters/:id`);
    console.log(`  GET  /api/map/height?x=10&z=10`);
});
//# sourceMappingURL=server.js.map