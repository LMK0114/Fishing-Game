#include <iostream> //Console input/output
#include <vector>   //Dynamic array container
#include <cstdlib>  //Random number generator
#include <ctime>    //Time related functions for seeding random
#include <iomanip>  //Output formatting
#include <thread>   //Multi-threading support
#include <chrono>   //Time measure
#include <fstream>  //File functiom
#include <algorithm>//Sorting
#include <string>   //String class
#include <sstream>  //String stream operation

using namespace std;

// ENUMS
enum Rarity { COMMON, UNCOMMON, RARE, LEGENDARY };  // Fish rarity levels
enum Weather { SUNNY, RAINY, STORMY };              // Weather conditions

const int MAX_INVENTORY_SIZE = 10;                  // Define maximum inventory size

// FISH NAMES
const string fishNames[] = { "Cod", "Salmon", "Tropical Fish", "Pufferfish" };

// STRUCTS
struct Fish
{
    string name;
    float weight;
    float pricePerKg;
    Rarity rarity;
};

struct Player
{
    float money;
    vector<Fish> inventory;
    int fishingRodLevel;
    string fishingRodName;
    int inventoryCapacity;
};

// === HELPER FUNCTIONS ===

// Convert rarity enum to string
string getRarityName(Rarity r)
{
    switch (r)
    {
    case COMMON: return "Common";
    case UNCOMMON: return "Uncommon";
    case RARE: return "Rare";
    case LEGENDARY: return "Legendary";
    default: return "Unknown";
    }
}

// Convert weather enum to string
string getWeatherName(Weather w)
{
    switch (w)
    {
    case SUNNY: return "Sunny";
    case RAINY: return "Rainy";
    case STORMY: return "Stormy";
    default: return "Unknown";
    }
}

// Generate random fish weight
float getRandomWeight()
{
    return static_cast<float>(rand() % 300 + 100) / 100.0f;
}

// Generate random price
float getRandomPrice()
{
    return static_cast<float>(rand() % 1000 + 500) / 100.0f;
}

// Generate random weather
Weather getRandomWeather()
{
    int roll = rand() % 100;
    if (roll < 60) return SUNNY;
    else if (roll < 90) return RAINY;
    else return STORMY;
}

// Determine fish rarity based on weather
Rarity getWeatherAdjustedRarity(Weather weather)
{
    int roll = rand() % 100;
    if (weather == SUNNY)
    {
        if (roll < 50) return COMMON;
        else if (roll < 80) return UNCOMMON;
        else if (roll < 95) return RARE;
        else return LEGENDARY;
    }
    else if (weather == RAINY)
    {
        if (roll < 30) return COMMON;
        else if (roll < 60) return UNCOMMON;
        else if (roll < 90) return RARE;
        else return LEGENDARY;
    }
    else
    {
        if (roll < 20) return COMMON;
        else if (roll < 50) return UNCOMMON;
        else if (roll < 80) return RARE;
        else return LEGENDARY;
    }
}

// === CORE GAME FUNCTIONS ===

// Display player status and game information
void showStatus(const Player& player, int day, Weather weather)
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " Day " << day
        << " | Weather: " << getWeatherName(weather)
        << " | Money: RM " << fixed << setprecision(2) << player.money
        << " | Rod Level: " << player.fishingRodLevel
        << " | Rod Type: " << player.fishingRodName
        << " | Inventory: " << player.inventory.size() << "/" << player.inventoryCapacity << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

// Fishing Mechanic
void fish(Player& player, int attempts, Weather weather)
{
    cout << "\n--- Fishing ---\n";
    int baseDelay = 3000;

    for (int i = 0; i < attempts; ++i)
    {
        // Check if inventory is full
        if (player.inventory.size() >= player.inventoryCapacity)
        {
            cout << "Your inventory is full! (" << player.inventory.size()
                << "/" << player.inventoryCapacity << ")\n";
            cout << "Sell some fish or upgrade your inventory to catch more.\n";
            return;
        }

        int delay = baseDelay - (player.fishingRodLevel * 500); // Better rod = Faster fishing
        if (weather == STORMY)                                  // Stormy make fishing slower
        {
            delay += 1000;
        }
        if (delay < 500)
        {
            delay = 500;
        }

        // Fishing Animation
        cout << "Fishing";
        for (int j = 0; j < 3; ++j)
        {
            cout << ".";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(delay / 3));
        }
        cout << endl;


        // Create New fish
        Fish f;
        f.name = fishNames[rand() % 4]; // Randomly pick 1 of the fish from 4
        f.weight = getRandomWeight();
        f.rarity = getWeatherAdjustedRarity(weather);

        float rarityMultiplier = 1.0f;
        switch (f.rarity)
        {
        case COMMON: rarityMultiplier = 1.0f; break;
        case UNCOMMON: rarityMultiplier = 1.3f; break;
        case RARE: rarityMultiplier = 1.7f; break;
        case LEGENDARY: rarityMultiplier = 2.5f; break;
        }

        // Calculate price of fish
        f.pricePerKg = getRandomPrice() * rarityMultiplier * (1 + player.fishingRodLevel * 0.1f);

        player.inventory.push_back(f); // Add to inventory

        // Display fish info
        cout << "You caught a " << getRarityName(f.rarity) << " " << f.name
            << " (" << fixed << setprecision(2) << f.weight << " kg)\n";
        cout << "Inventory: " << player.inventory.size() << "/" << endl << endl;
    }
}


// Sell fish mechanic
void sellFish(Player& player)
{
    cout << "\n--- Sell Fish ---\n";
    if (player.inventory.empty())
    {
        cout << "You have no fish to sell.\n";
        return;
    }

    // Sort inventory by rarity, name, weight, price
    sort(player.inventory.begin(), player.inventory.end(), [](const Fish& a, const Fish& b)
        {
            if (a.rarity != b.rarity) return a.rarity > b.rarity;
            if (a.name != b.name) return a.name < b.name;
            if (a.weight != b.weight) return a.weight > b.weight;
            return a.pricePerKg > b.pricePerKg;
        });

    while (!player.inventory.empty())
    {
        cout << "\nYour Fish Inventory (Sorted):\n";
        for (size_t i = 0; i < player.inventory.size(); ++i)
        {
            const Fish& f = player.inventory[i];
            float value = f.weight * f.pricePerKg;
            cout << i + 1 << ". " << getRarityName(f.rarity) << " " << f.name
                << " (" << fixed << setprecision(2) << f.weight
                << " kg) - RM " << fixed << setprecision(2) << value << endl;
        }

        cout << "\nEnter fish number to sell\n";
        cout << "(0 to stop, -1 to sell ALL): ";
        int choice;
        cin >> choice;

        if (choice == 0)
            break;
        else if (choice == -1)
        {
            float totalEarnings = 0;
            for (const Fish& f : player.inventory)
            {
                totalEarnings += f.weight * f.pricePerKg;
            }
            player.money += totalEarnings;
            cout << "Sold ALL fish for RM " << fixed << setprecision(2) << totalEarnings << endl;
            player.inventory.clear();
            break;
        }
        else if (choice >= 1 && choice <= static_cast<int>(player.inventory.size()))
        {
            Fish sold = player.inventory[choice - 1];
            float earnings = sold.weight * sold.pricePerKg;
            player.money += earnings;

            cout << "Sold " << sold.name << " for RM "
                << fixed << setprecision(2) << earnings << endl;

            player.inventory.erase(player.inventory.begin() + (choice - 1));
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
}


// Upgrade Rod or expand inventory mechanic
void buyAccessories(Player& player)
{
    cout << "\n--- Buy Accessories ---\n";
    cout << "1. Upgrade Fishing Rod (Level " << player.fishingRodLevel
        << " -> " << player.fishingRodLevel + 1 << ") - RM "
        << 50 * (player.fishingRodLevel + 1) << endl;
    cout << "2. Expand Inventory (+5 slots) - RM 100\n";  // New option
    cout << "3. Back\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        int cost = 50 * (player.fishingRodLevel + 1);

        if (player.money >= cost)
        {
            player.money -= cost;
            player.fishingRodLevel++;

            // Upgrade rod name based on level
            if (player.fishingRodLevel >= 0 && player.fishingRodLevel < 5)
            {
                player.fishingRodName = "Wood Rod";
            }
            else if (player.fishingRodLevel >= 6 && player.fishingRodLevel < 10)
            {
                player.fishingRodName = "Stone Rod";
            }
            else if (player.fishingRodLevel >= 11 && player.fishingRodLevel < 15)
            {
                player.fishingRodName = "Copper Rod";
            }
            else if (player.fishingRodLevel >= 16 && player.fishingRodLevel < 20)
            {
                player.fishingRodName = "Silver Rod";
            }
            else if (player.fishingRodLevel >= 21 && player.fishingRodLevel < 25)
            {
                player.fishingRodName = "Gold Rod";
            }
            else if (player.fishingRodLevel >= 26)
            {
                player.fishingRodName = "Diamond Rod";
            }
        }
        else {
            cout << "Not enough money!\n";
        }
    }

    else if (choice == 2)
    {  // New inventory expansion option
        if (player.money >= 100)
        {
            player.money -= 100;
            player.inventoryCapacity += 5;
            cout << "Inventory expanded! Now holds " << player.inventoryCapacity << " fish.\n";
        }
        else
        {
            cout << "Not enough money!\n";
        }
    }
}

// === SAVE & LOAD ===

void saveGame(const Player& player, int day)
{
    ofstream file("savegame.txt");
    if (!file.is_open())
    {
        cout << "Failed to save game." << endl;
        return;
    }

    // Save player info
    file << "Player Information:" << endl;
    file << "Day: " << day << endl;
    file << "Money: " << fixed << setprecision(2) << player.money << endl;
    file << "RodLevel: " << player.fishingRodLevel << endl;
    file << "RodName: " << player.fishingRodName << endl;
    file << "InventoryCapacity: " << player.inventoryCapacity << endl;
    file << "FishCount: " << player.inventory.size() << endl;
    file << "---------------------------------------------" << endl;

    // Save fish info
    file << "Fish Information:" << endl;
    for (const Fish& f : player.inventory)
    {
        file << "Name: " << f.name << endl;
        file << "Weight: " << fixed << setprecision(2) << f.weight << endl;
        file << "PricePerKg: " << fixed << setprecision(2) << f.pricePerKg << endl;
        file << "Rarity: " << f.rarity << endl;
        file << "---" << endl; // Fish separator
    }
    file.close();
    cout << "Game saved successfully." << endl;
}

void loadGame(Player& player, int& day)
{
    ifstream file("savegame.txt");
    if (!file.is_open())
    {
        cout << "No save file found." << endl;
        return;
    }

    string line;
    bool inFishSection = false;
    Fish currentFish;
    int expectedFishCount = 0;
    int loadedFishCount = 0;

    player.inventory.clear(); // Clear existing inventory

    while (getline(file, line))
    {
        if (line.find("Player Information:") != string::npos)
        {
            inFishSection = false;
            continue;
        }
        else if (line.find("Fish Information:") != string::npos)
        {
            inFishSection = true;
            continue;
        }
        else if (line.find("---") != string::npos && inFishSection)
        {
            // End of fish entry
            if (!currentFish.name.empty())
            {
                player.inventory.push_back(currentFish);
                loadedFishCount++;
                currentFish = Fish(); // Reset for next fish
            }
            continue;
        }

        if (!inFishSection)
        {
            // Parse player info
            if (line.find("Day: ") != string::npos)
            {
                day = stoi(line.substr(5));
            }
            else if (line.find("Money: ") != string::npos)
            {
                player.money = stof(line.substr(7));
            }
            else if (line.find("RodLevel: ") != string::npos)
            {
                player.fishingRodLevel = stoi(line.substr(10));
            }
            else if (line.find("RodName: ") != string::npos)
            {
                player.fishingRodName = line.substr(9);
            }
            else if (line.find("InventoryCapacity: ") != string::npos)
            {
                player.inventoryCapacity = stoi(line.substr(18));
            }
            else if (line.find("FishCount: ") != string::npos)
            {
                expectedFishCount = stoi(line.substr(10));
            }
        }
        else
        {
            // Parse fish info
            if (line.find("Name: ") != string::npos)
            {
                currentFish.name = line.substr(6);
            }
            else if (line.find("Weight: ") != string::npos)
            {
                currentFish.weight = stof(line.substr(8));
            }
            else if (line.find("PricePerKg: ") != string::npos)
            {
                currentFish.pricePerKg = stof(line.substr(12));
            }
            else if (line.find("Rarity: ") != string::npos)
            {
                int rarityValue = stoi(line.substr(8));
                currentFish.rarity = static_cast<Rarity>(rarityValue);
            }
        }
    }

    // Add the last fish if it wasn't added yet
    if (!currentFish.name.empty())
    {
        player.inventory.push_back(currentFish);
        loadedFishCount++;
    }

    file.close();

    if (loadedFishCount != expectedFishCount)
    {
        cout << "Warning: Loaded " << loadedFishCount << " fish but expected " << expectedFishCount << endl;
    }
    else
    {
        cout << "Game loaded successfully. Loaded " << loadedFishCount << " fish." << endl;
    }
}

// === MAIN ===
int main()
{
    srand(static_cast<unsigned int>(time(0)));              // Seed random number

    // Initialize player
    Player player = { 0.0f, {}, 0,{},MAX_INVENTORY_SIZE };
    int day = 1;
    Weather todayWeather = getRandomWeather();
    char choice;

    // User Interface
    cout << "-----------------------------------------------------------------" << endl;
    cout << "\tWelcome to the Minecraft-Inspired Fishing Game!" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    while (true)
    {
        showStatus(player, day, todayWeather);

        cout << "\n-------------------------" << endl;
        cout << "| S - Start Fishing\t|" << endl;
        cout << "| V - View & Sell Fish\t|" << endl;
        cout << "| B - Buy Accessories\t|" << endl;
        cout << "| N - Next Day\t\t|" << endl;
        cout << "| W - Save Game\t\t|" << endl;
        cout << "| L - Load Game\t\t|" << endl;
        cout << "| Q - Quit Game\t\t|" << endl;
        cout << "-------------------------" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 's' || choice == 'S')
        {
            int times;
            cout << "How many times do you want to fish?: ";
            cin >> times;
            if (times > 0)
            {
                fish(player, times, todayWeather);
            }
            else
            {
                cout << "Invalid number.\n";
            }
        }
        else if (choice == 'v' || choice == 'V')
        {
            sellFish(player);
        }
        else if (choice == 'b' || choice == 'B')
        {
            buyAccessories(player);
        }
        else if (choice == 'n' || choice == 'N')
        {
            day++;
            todayWeather = getRandomWeather();
            cout << "A new day begins. Weather: " << getWeatherName(todayWeather) << "\n";
        }
        else if (choice == 'w' || choice == 'W')
        {
            saveGame(player, day);
        }
        else if (choice == 'l' || choice == 'L')
        {
            loadGame(player, day);
        }
        else if (choice == 'q' || choice == 'Q')
        {
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    cout << "\nThanks for playing! Final Money: RM "
        << fixed << setprecision(2) << player.money << endl;

    return 0;
}