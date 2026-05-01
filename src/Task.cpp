#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class User {
public:
    std::string name;
    User(std::string n) : name(n) {}
};

class Task {
public:
    std::string title;
    User* assignee; // Виконавець
    bool isDone;

    Task(std::string t) : title(t), assignee(nullptr), isDone(false) {}

    void assignTo(User* u) {
        assignee = u;
    }
};

class Team {
private:
    std::string teamName;
    std::vector<User*> members;
    std::vector<Task*> tasks;

public:
    Team(std::string name) : teamName(name) {}

    void addUser(User* u) { members.push_back(u); }

    void createTask(std::string title) {
        tasks.push_back(new Task(title));
    }

    // Призначаємо задачу на юзера за іменами
    void assignTask(std::string taskTitle, std::string userName) {
        auto uIt = std::find_if(members.begin(), members.end(), [&](User* u) { return u->name == userName; });
        auto tIt = std::find_if(tasks.begin(), tasks.end(), [&](Task* t) { return t->title == taskTitle; });

        if (uIt != members.end() && tIt != tasks.end()) {
            (*tIt)->assignTo(*uIt);
            std::cout << "Задача '" << taskTitle << "' призначена на " << userName << "\n";
        }
    }

    void showDashboard() {
        std::cout << "\n--- " << teamName << " Dashboard ---\n";
        for (auto t : tasks) {
            std::cout << "- [" << (t->isDone ? "X" : " ") << "] " << t->title;
            if (t->assignee) std::cout << " (Виконавець: " << t->assignee->name << ")";
            std::cout << "\n";
        }
    }
};

