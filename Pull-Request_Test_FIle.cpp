#include <chrono>
#include <iostream>

bool isTimerSet();

int main(){
    int input;

    std::cin >> input;
    isTimerSet(input);

    return 0;
}

bool isTimerSet(int indx){
    switch (indx)
    {
    case 1:
        std::cout << "Timer Set.";
        break;
    case 0:
        std::cout << "Timer Stopped";
    default:
        std::cout << "Invalid operation";
        break;
    }
}