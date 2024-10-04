#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Enemy class representing an enemy with health points
class Enemy {
public:
    int health;
    // Constructor to initialize enemy health
    Enemy(int h) : health(h) {}
};

// Tower class representing a tower with attack power and range
class Tower {
public:
    int attackPower;
    int range;
    // Constructor to initialize tower attack power and range
    Tower(int power, int rng) : attackPower(power), range(rng) {}

    // Method to attack the enemies
    void attack(std::vector<Enemy>& enemies) {
        // Iterate over the enemies vector
        for (auto& enemy : enemies) {
            // If the enemy is still alive (health > 0)
            if (enemy.health > 0) {
                // Reduce enemy health by the tower's attack power
                enemy.health -= attackPower;
                std::cout << "Enemy is attacked. Health is now: " << enemy.health << "\n";
                // Attack only one enemy per iteration, so break after attacking
                break;
            }
        }
    }
};

int main() {
    // Vector to store multiple enemies
    std::vector<Enemy> enemies;
    // Adding enemies with different health points to the vector
    enemies.push_back(Enemy(10));
    enemies.push_back(Enemy(15));
    enemies.push_back(Enemy(20));

    // Create a tower with attack power of 5 and range of 2 (range not used in this simple example)
    Tower tower(5, 2);

    // Main game loop, continues until all enemies are defeated
    while (!enemies.empty()) {
        // Tower attacks the enemies
        tower.attack(enemies);

        // Remove dead enemies from the vector
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) { return e.health <= 0; }), enemies.end());

        // Pause for 1 second to simulate time between attacks
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Print message when all enemies are defeated
    std::cout << "All enemies have been defeated!\n";
    return 0;
}