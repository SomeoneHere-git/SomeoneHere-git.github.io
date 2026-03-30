#include <chrono>
#include <iostream>

void IsTimerSet();
void StartTimer();
void StopTimer();

std::chrono::time_point<std::chrono::steady_clock> start_time;

int main(){
    int inputOperation;

    std::cout << "Start or Stop timer?(1 or 0)";
    std::cin >> inputOperation;
    IsTimerSet(inputOperation);

    std::cout << "Input 0 to stop timer: ";
    std::cin >> inputOperation;
    IsTimerSet(inputOperation);

    return 0;
}

void IsTimerSet(int indx){
    bool isTimerStarted = false;
    
    if(indx == 1 && isTimerStarted == false){
        std::cout << "Timer Started.";
        StartTimer();
        isTimerStarted = true;
    }
    else if(indx == 0 && isTimerStarted == true){
        std::cout << "Timer Stopped.";
        StopTimer();
        isTimerStarted = false;
    }
    else
        std::cout << "Invalid operation.";
}

void StartTimer() {
    start_time = std::chrono::steady_clock::now();
    std::cout << "Timer Started!" << std::endl;
}

void StopTimer() {
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Time passed: " << elapsed.count() << " seconds." << std::endl;
}