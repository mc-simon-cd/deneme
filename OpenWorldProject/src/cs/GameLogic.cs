using System;
using System.Collections.Generic;

namespace OpenWorld.GameLogic
{
    // Görev Türleri
    public enum QuestType { Main, Side, Daily, Exploration }
    
    // Görev Durumu
    public enum QuestState { NotStarted, InProgress, Completed, Failed }

    // Görev Nesnesi
    public class Quest
    {
        public string Id { get; set; }
        public string Title { get; set; }
        public string Description { get; set; }
        public QuestType Type { get; set; }
        public QuestState State { get; set; }
        public int RewardGold { get; set; }
        public int RewardExp { get; set; }
        public List<string> RequiredItems { get; set; }
        public List<string> TargetEnemies { get; set; }

        public Quest(string id, string title, QuestType type)
        {
            Id = id;
            Title = title;
            Type = type;
            State = QuestState.NotStarted;
            RequiredItems = new List<string>();
            TargetEnemies = new List<string>();
        }

        public void Start()
        {
            if (State == QuestState.NotStarted)
            {
                State = QuestState.InProgress;
                Console.WriteLine($"Görev Başlatıldı: {Title}");
            }
        }

        public void Complete()
        {
            if (State == QuestState.InProgress)
            {
                State = QuestState.Completed;
                Console.WriteLine($"Görev Tamamlandı: {Title} - Ödül: {RewardGold} Altın, {RewardExp} XP");
            }
        }
    }

    // Envanter Sistemi
    public class Inventory
    {
        private Dictionary<string, int> items;
        public int MaxSlots { get; set; }

        public Inventory(int maxSlots = 20)
        {
            items = new Dictionary<string, int>();
            MaxSlots = maxSlots;
        }

        public bool AddItem(string itemName, int quantity = 1)
        {
            int currentCount = GetTotalItemCount();
            if (currentCount + quantity > MaxSlots)
            {
                Console.WriteLine("Envanter dolu!");
                return false;
            }

            if (items.ContainsKey(itemName))
            {
                items[itemName] += quantity;
            }
            else
            {
                items[itemName] = quantity;
            }
            
            Console.WriteLine($"Eklendi: {itemName} x{quantity}");
            return true;
        }

        public bool RemoveItem(string itemName, int quantity = 1)
        {
            if (items.ContainsKey(itemName) && items[itemName] >= quantity)
            {
                items[itemName] -= quantity;
                if (items[itemName] <= 0)
                {
                    items.Remove(itemName);
                }
                Console.WriteLine($"Çıkarıldı: {itemName} x{quantity}");
                return true;
            }
            Console.WriteLine($"Yetersiz miktar veya bulunamadı: {itemName}");
            return false;
        }

        public int GetTotalItemCount()
        {
            int total = 0;
            foreach (var item in items)
            {
                total += item.Value;
            }
            return total;
        }

        public void Display()
        {
            Console.WriteLine("\n--- ENVANTER ---");
            if (items.Count == 0)
            {
                Console.WriteLine("Boş");
            }
            else
            {
                foreach (var item in items)
                {
                    Console.WriteLine($"{item.Key}: {item.Value}");
                }
            }
            Console.WriteLine($"Toplam Slot: {GetTotalItemCount()}/{MaxSlots}\n");
        }
    }

    // Oyuncu Sınıfı
    public class Player
    {
        public string Name { get; set; }
        public int Level { get; set; }
        public int Experience { get; set; }
        public int Gold { get; set; }
        public Inventory Inventory { get; set; }
        public List<Quest> ActiveQuests { get; set; }

        public Player(string name)
        {
            Name = name;
            Level = 1;
            Experience = 0;
            Gold = 0;
            Inventory = new Inventory();
            ActiveQuests = new List<Quest>();
        }

        public void AcceptQuest(Quest quest)
        {
            if (quest.State == QuestState.NotStarted)
            {
                ActiveQuests.Add(quest);
                quest.Start();
                Console.WriteLine($"{Name}, '{quest.Title}' görevini kabul etti.");
            }
        }

        public void GainExperience(int amount)
        {
            Experience += amount;
            Console.WriteLine($"{amount} XP kazanıldı. Toplam XP: {Experience}");
            
            // Basit seviye atlama mantığı
            int requiredXP = Level * 100;
            if (Experience >= requiredXP)
            {
                Level++;
                Experience -= requiredXP;
                Console.WriteLine($"TEBRİKLER! Seviye {Level} oldunuz!");
            }
        }

        public void GainGold(int amount)
        {
            Gold += amount;
            Console.WriteLine($"{amount} Altın kazanıldı. Toplam: {Gold}");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("--- C# Oyun Mantığı Testi ---");

            // Oyuncu oluştur
            Player player = new Player("Gezgin");

            // Envanter testi
            player.Inventory.AddItem("Kılıç", 1);
            player.Inventory.AddItem("İksir", 5);
            player.Inventory.AddItem("Harita", 1);
            player.Inventory.Display();

            // Görev oluştur
            Quest mainQuest = new Quest("q001", "Kayıp Kılıç", QuestType.Main);
            mainQuest.Description = "Köyün yakınında kaybolan kılıcı bul.";
            mainQuest.RewardGold = 50;
            mainQuest.RewardExp = 100;
            mainQuest.RequiredItems.Add("Kayıp Kılıç");

            Quest sideQuest = new Quest("q002", "Canavar Avı", QuestType.Side);
            sideQuest.Description = "Ormandaki 3 kurdu yok et.";
            sideQuest.RewardGold = 30;
            sideQuest.RewardExp = 75;
            sideQuest.TargetEnemies.Add("Kurt");

            // Görevleri kabul et
            player.AcceptQuest(mainQuest);
            player.AcceptQuest(sideQuest);

            // Simülasyon: Görev tamamlandı
            Console.WriteLine("\n... Görev yapılıyor ...");
            player.Inventory.AddItem("Kayıp Kılıç", 1); // Eşya bulundu
            mainQuest.Complete();
            
            // Ödülleri dağıt
            player.GainGold(mainQuest.RewardGold);
            player.GainExperience(mainQuest.RewardExp);

            // Düşman yenildi simülasyonu
            player.GainExperience(20); // Kurt yendi
            
            player.Inventory.Display();
            
            Console.WriteLine("Test tamamlandı.");
        }
    }
}
