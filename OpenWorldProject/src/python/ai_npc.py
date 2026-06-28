#!/usr/bin/env python3
"""
Açık Dünya Projesi - Python NPC AI Sistemi
Basit durum makinesi ile NPC davranışları
"""

import random
import time
from enum import Enum
from dataclasses import dataclass
from typing import List, Optional

class NPCState(Enum):
    IDLE = "Dinleniyor"
    PATROL = "Devriye geziyor"
    FOLLOW = "Takip ediyor"
    FLEE = "Kaçıyor"
    TALK = "Konuşuyor"

@dataclass
class Vector3:
    x: float
    y: float
    z: float
    
    def distance_to(self, other: 'Vector3') -> float:
        return ((self.x - other.x)**2 + (self.y - other.y)**2 + (self.z - other.z)**2)**0.5

@dataclass
class NPC:
    id: str
    name: str
    position: Vector3
    state: NPCState = NPCState.IDLE
    health: int = 100
    dialogue: List[str] = None
    
    def __post_init__(self):
        if self.dialogue is None:
            self.dialogue = [
                "Merhaba gezgin!",
                "Hava bugün çok güzel.",
                "Dikkatli ol, ormanda kurtlar var.",
                "Ticaret yapmak ister misin?"
            ]
    
    def update(self, player_pos: Vector3, delta_time: float):
        """NPC durum güncellemesi"""
        distance = self.position.distance_to(player_pos)
        
        if self.state == NPCState.FLEE:
            # Kaçma davranışı - oyuncudan uzaklaş
            direction = self.position - player_pos
            # Basitleştirilmiş hareket
            print(f"[{self.name}] Kaçıyor! Oyuncu mesafesi: {distance:.2f}")
            if distance > 20:
                self.state = NPCState.IDLE
                print(f"[{self.name}] Güvenli mesafe, durdu.")
                
        elif self.state == NPCState.PATROL:
            # Devriye davranışı
            print(f"[{self.name}] Devriye geziyor... Pozisyon: ({self.position.x}, {self.position.z})")
            if random.random() < 0.1:
                self.state = NPCState.IDLE
                
        elif distance < 5:
            # Oyuncu yaklaştı
            self.state = NPCState.TALK
            self.talk()
            
        elif distance < 15 and random.random() < 0.05:
            # Bazen oyuncuyu takip et
            self.state = NPCState.FOLLOW
            print(f"[{self.name}] Oyuncuyu takip ediyor...")
            
        elif self.state == NPCState.IDLE and random.random() < 0.02:
            # Rastgele devriyeye başla
            self.state = NPCState.PATROL
            
    def talk(self):
        """Rastgele diyalog"""
        if self.dialogue:
            line = random.choice(self.dialogue)
            print(f"[{self.name}] diyor ki: \"{line}\"")
        time.sleep(0.5)
        self.state = NPCState.IDLE

def main():
    print("=== Python NPC AI Testi ===\n")
    
    # NPC oluştur
    villager = NPC(
        id="npc_001",
        name="Yaşlı Köylü",
        position=Vector3(10.0, 0.0, 10.0)
    )
    
    guard = NPC(
        id="npc_002",
        name="Koruma",
        position=Vector3(15.0, 0.0, 15.0),
        dialogue=[
            "Geçiş serbest.",
            "Şehre hoşgeldin.",
            "Sorun çıkarma."
        ]
    )
    
    npcs = [villager, guard]
    player_pos = Vector3(12.0, 0.0, 12.0)  # Oyuncu pozisyonu
    
    # Simülasyon döngüsü
    for tick in range(5):
        print(f"\n--- Tick {tick + 1} ---")
        for npc in npcs:
            npc.update(player_pos, 0.1)
        time.sleep(0.3)
    
    print("\n=== Test Tamamlandı ===")

if __name__ == "__main__":
    main()
