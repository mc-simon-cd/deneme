using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace OpenWorld.Logic
{
    /// <summary>
    /// C++ oyun motoru ile iletişim için P/Invoke tanımlamaları
    /// </summary>
    public static class NativeMethods
    {
        private const string EngineLib = "open_world_engine";

        [DllImport(EngineLib, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateWorldManager();

        [DllImport(EngineLib, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DestroyWorldManager(IntPtr manager);

        [DllImport(EngineLib, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool AddCharacter(IntPtr manager, uint id, string name, int type);

        [DllImport(EngineLib, CallingConvention = CallingConvention.Cdecl)]
        public static extern void UpdateWorld(IntPtr manager, float deltaTime);
    }

    /// <summary>
    /// Karakter tipleri (C enum ile eşleşmeli)
    /// </summary>
    public enum CharacterType
    {
        Human = 0,
        Animal = 1,
        Monster = 2,
        NPC = 3
    }

    /// <summary>
    /// Açık dünya oyun mantığı sınıfı
    /// Görevler, envanter, diyalog sistemleri vb.
    /// </summary>
    public class OpenWorldGameLogic : IDisposable
    {
        private IntPtr _worldManager;
        private readonly List<Character> _characters;
        private readonly QuestSystem _questSystem;
        private readonly InventorySystem _inventorySystem;

        public OpenWorldGameLogic()
        {
            _worldManager = NativeMethods.CreateWorldManager();
            _characters = new List<Character>();
            _questSystem = new QuestSystem();
            _inventorySystem = new InventorySystem();
        }

        public void AddCharacter(uint id, string name, CharacterType type)
        {
            var character = new Character(id, name, type);
            _characters.Add(character);

            // C++ motoruna ekle
            NativeMethods.AddCharacter(_worldManager, id, name, (int)type);
            
            Console.WriteLine($"Karakter eklendi: {name} (ID: {id}, Tip: {type})");
        }

        public void Update(float deltaTime)
        {
            // Oyun mantığı güncellemeleri
            _questSystem.Update(deltaTime);
            _inventorySystem.Update(deltaTime);

            // C++ motorunu güncelle
            NativeMethods.UpdateWorld(_worldManager, deltaTime);
        }

        public void StartQuest(string questName, Character player)
        {
            _questSystem.StartQuest(questName, player);
        }

        public void AddItemToInventory(Character character, string itemName, int quantity)
        {
            _inventorySystem.AddItem(character, itemName, quantity);
        }

        public void Dispose()
        {
            if (_worldManager != IntPtr.Zero)
            {
                NativeMethods.DestroyWorldManager(_worldManager);
                _worldManager = IntPtr.Zero;
            }
        }
    }

    /// <summary>
    /// Karakter sınıfı - C# tarafında oyun mantığı için
    /// </summary>
    public class Character
    {
        public uint Id { get; }
        public string Name { get; }
        public CharacterType Type { get; }
        public float Health { get; set; } = 100f;
        public Dictionary<string, int> Inventory { get; } = new();

        public Character(uint id, string name, CharacterType type)
        {
            Id = id;
            Name = name;
            Type = type;
        }
    }

    /// <summary>
    /// Görev sistemi
    /// </summary>
    public class QuestSystem
    {
        private readonly List<Quest> _activeQuests = new();

        public void StartQuest(string questName, Character player)
        {
            var quest = new Quest(questName, player);
            _activeQuests.Add(quest);
            Console.WriteLine($"Görev başlatıldı: {questName}");
        }

        public void Update(float deltaTime)
        {
            // Görev ilerlemesi kontrolü
            foreach (var quest in _activeQuests)
            {
                quest.Update(deltaTime);
            }
        }
    }

    /// <summary>
    /// Tekil görev sınıfı
    /// </summary>
    public class Quest
    {
        public string Name { get; }
        public Character Player { get; }
        public bool IsCompleted { get; private set; }

        public Quest(string name, Character player)
        {
            Name = name;
            Player = player;
        }

        public void Update(float deltaTime)
        {
            // Görev mantığı güncellemesi
        }
    }

    /// <summary>
    /// Envanter sistemi
    /// </summary>
    public class InventorySystem
    {
        public void AddItem(Character character, string itemName, int quantity)
        {
            if (character.Inventory.ContainsKey(itemName))
            {
                character.Inventory[itemName] += quantity;
            }
            else
            {
                character.Inventory[itemName] = quantity;
            }
            Console.WriteLine($"{itemName} x{quantity} envantere eklendi.");
        }

        public void Update(float deltaTime)
        {
            // Envanter güncellemeleri
        }
    }
}
