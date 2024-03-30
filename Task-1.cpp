#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

// Function to generate a random number within a given range
int generateRandomNumber(int minRange, int maxRange) {
    return rand() % (maxRange - minRange + 1) + minRange;
}

int main() {
    std::cout << "Welcome to the Number Guessing Game!\n";

    do {
        int minRange, maxRange;
        std::cout << "Enter the range for the number (minimum and maximum): ";
        std::cin >> minRange >> maxRange;

        if (minRange >= maxRange || minRange < 1) {
            std::cout << "Invalid range. Please enter a valid range.\n";
            return 1;
        }

        std::cout << "Select difficulty level:\n";
        std::cout << "1. Easy\n";
        std::cout << "2. Medium\n";
        std::cout << "3. Hard\n";
        int difficulty;
        std::cin >> difficulty;

        int maxAttempts;
        switch (difficulty) {
            case 1:
                maxAttempts = 10;
                break;
            case 2:
                maxAttempts = 7;
                break;
            case 3:
                maxAttempts = 5;
                break;
            default:
                std::cout << "Invalid difficulty level. Defaulting to Medium.\n";
                maxAttempts = 7;
                break;
        }

        std::cout << "I have selected a number between " << minRange << " and " << maxRange << ". Try to guess it!\n";

        srand(time(NULL)); // Seed the random number generator
        int secretNumber = generateRandomNumber(minRange, maxRange);
        int attempts = 0;
        int guess;

        while (attempts < maxAttempts) {
            std::cout << "Enter your guess: ";
            if (!(std::cin >> guess)) {
                std::cout << "Invalid input. Please enter a valid number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            attempts++;

            if (guess < secretNumber) {
                std::cout << "Too low! ";
            } else if (guess > secretNumber) {
                std::cout << "Too high! ";
            } else {
                std::cout << "Congratulations! You guessed the number.\n";
                break;
            }
            std::cout << "Attempts left: " << maxAttempts - attempts << std::endl;
        }

        if (attempts == maxAttempts) {
            std::cout << "Sorry, you've run out of attempts. The correct number was " << secretNumber << std::endl;
        }

        // Calculate score based on difficulty and remaining attempts
        int score = (attempts > 0) ? (maxAttempts * difficulty * (maxAttempts - attempts + 1) / maxAttempts) : 0;

        std::cout << "Your score: " << score << std::endl;

        // Ask if the player wants to play again
        char choice;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            std::cout << "Thank you !" << std::endl;
            break;
        }

    } while (true);

    return 0;
}
