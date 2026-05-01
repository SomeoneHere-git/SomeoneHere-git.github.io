#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class User {
public:
    std::string name;
    User(std::string n);
};

class Task {
public:
    std::string title;
    User* assignee;
    bool isDone;

    Task(std::string t);
    void assignTo(User* u);
};

class Team {
private:
    std::string teamName;
    std::vector<User*> members;
    std::vector<Task*> tasks;

public:
    Team(std::string name);
    // Деструктор для очищення пам'яті, бо ми використовуємо new
    ~Team();

    void addUser(User* u);
    void createTask(const std::string& title);
    void assignTask(const std::string& taskTitle, const std::string& userName);
    void showDashboard() const;
};
