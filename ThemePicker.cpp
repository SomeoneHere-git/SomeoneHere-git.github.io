// Generate a function that allows to pick a color theme
#include <iostream>

void PickTheme() {
    int themeChoice;

    std::cout << "Please select a color theme:" << std::endl;
    std::cout << "1. Light Theme" << std::endl;
    std::cout << "2. Dark Theme" << std::endl;
    std::cout << "3. Blue Theme" << std::endl;
    std::cout << "4. Green Theme" << std::endl;
    std::cout << "Enter your choice (1-4): ";
    std::cin >> themeChoice;

    switch (themeChoice) {
        case 1:
            ApplyLightTheme();
            break;
        case 2:
            ApplyDarkTheme();
            break;
        case 3:
            ApplyBlueTheme();
            break;
        case 4:
            ApplyGreenTheme();
            break;
        default:
            std::cout << "Invalid choice. Please select a valid theme." << std::endl;
            break;
    }
}

void ApplyLightTheme() {
    std::cout << "Light Theme applied!" << std::endl;
    // Code to change the application's color scheme to light theme;
}

void ApplyDarkTheme() {
    std::cout << "Dark Theme applied!" << std::endl;
    // Code to change the application's color scheme to dark theme;
}

void ApplyBlueTheme() {
    std::cout << "Blue Theme applied!" << std::endl;
    // Code to change the application's color scheme to blue theme;
}

void ApplyGreenTheme() {
    std::cout << "Green Theme applied!" << std::endl;
    //Code to change the application's color scheme to green theme;
}