#  Fishing Game
A fishing simulation game you can play on your computer, created using C++. It includes changing weather conditions, options to upgrade your fishing rod, manage your inventory, and save or load your game. Players can catch various types of fish, sell them for money, and improve their gear to become expert fishermen.
## Overview
This Fishing Game is a video game made in C++ where you play as a fisherman trying to get rich. The game includes changing weather that impacts how many fish you can catch, different types of fish with varying rarity, options to upgrade your fishing rods, and ways to expand your inventory. You can also save and load your game. Players need to carefully manage their resources, choose the best times to fish based on the weather, and spend wisely on upgrades to earn more money.
## Features
* Dynamic Weather System
  * Three weather conditions: Sunny, Rainy, and Stormy
  * Weather affects fish rarity probabilities
  * Stormy weather slows fishing but increases rare catch chances
  * Random weather changes each day
* Fish Rarity System
  * Four rarity levels: Common, Uncommon, Rare, Legendary
  * Rarity multipliers affect fish prices (1.0x to 2.5x)
  * Weather-adjusted rarity probabilities
  * Unique fish types including Cod, Salmon, Tropical Fish, and Pufferfish
* Fishing Mechanic
  * Realistic fishing animation with progress indicators
  * Fishing speed affected by rod level and weather
  * Random fish weights (1.00kg to 4.00kg)
  * Dynamic price calculation based on weight, rarity, and rod level
* Inventory Management
  * Maximum inventory size of 10 fish (upgradable)
  * Sorted inventory display by rarity, name, weight, and price
  * Individual fish selling or bulk sell all option
  * Inventory expansion upgrades (+5 slots)
* Upgrade System
  * Fishing rod levels (0-25+)
  * Progressive rod names: Wood → Stone → Copper → Silver → Gold → Diamond
  * Each rod level increases fishing speed by 500ms
  * Rod level also provides price multiplier bonus (1 + level × 0.1)
* Save & Load System
## Technologies Used
* C++
* Standard Template Library (STL)
* cstdlib & ctime (Random number generation)
* iomanip (Output formatting)
* Thread & chrono (Timing and animations)
* Object-Oriented Programming (OOP)
## Gameplay Mechanics
### Fishing System
Players can fish multiple times per day, with each fishing attempt taking time based on their rod level. Better rods fish faster. Weather conditions affect both fishing speed and the rarity of fish that can be caught. Stormy weather slows fishing but yields rarer fish, while sunny weather is faster but produces more common catches.
### Rarity System
* Fish rarity determines their base value multiplier:
  * Common: 1.0x multiplier
  * Uncommon: 1.3x multiplier
  * Rare: 1.7x multiplier
  * Legendary: 2.5x multiplier
* Rarity chances are affected by weather:
  * Sunny: Favors Common fish (50%)
  * Rainy: Balanced distribution
  * Stormy: Favors Rare and Legendary fish

## Control
| Key | Action |
|-----|--------|
| S | Start Fishing |
| V | 	View & Sell Fish |
| B | Buy Accessories |
| N | Next Day |
| W | Save Game |
| L | Load Game |
| Q | Quit Game |
## Project Structure

```bash
├── Fishing Game.cpp
├── savegame.txt
└── README.md
```

## Installation
1. Create a new Console Application project
2. Copy the source code into the main.cpp file
3. Build and run the project.
4. Ensure the sounds folder remains in the project directory.
## Screenshots
### Main Menu
<img width="1472" height="747" alt="image" src="https://github.com/user-attachments/assets/44e524a6-e155-4778-b59c-de9292020cf1" />

### Gameplay
<img width="1451" height="746" alt="image" src="https://github.com/user-attachments/assets/ba444d84-14c8-4378-8899-c26b3304122f" />
<img width="1464" height="746" alt="image" src="https://github.com/user-attachments/assets/5e7ffac2-e495-4b24-8a76-40858306a8a3" />
<img width="1458" height="723" alt="image" src="https://github.com/user-attachments/assets/97bb475e-d704-41b6-b78e-6ad89ea45d8e" />

## Authors
* LAM MING KANG
## License
This project is developed for educational purposes.
