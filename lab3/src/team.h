#pragma once
#include <string>
#include <vector>
#include <stdexcept>

// Клас Team — відповідає UML-моделі з ЛР 02
class Team {
public:
    std::string teamId;
    std::string name;
    std::string leaderId;

private:
    std::vector<std::string> memberIds;  // список userId учасників

public:
    // Конструктор: кидає std::invalid_argument якщо name або leaderId порожні
    Team(const std::string& teamId,
         const std::string& name,
         const std::string& leaderId);

    [[nodiscard]] std::string getTeamId() const { return teamId; }
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] std::string getLeaderId() const { return leaderId; }

    // join: додає userId до команди
    // Кидає std::invalid_argument якщо userId порожній
    // Кидає std::runtime_error якщо userId вже є в команді
    void join(const std::string& userId);

    // getMembers: повертає копію списку учасників
    [[nodiscard]] std::vector<std::string> getMembers() const;

    // getMemberCount: повертає кількість учасників
    [[nodiscard]] size_t getMemberCount() const;

    // hasMember: перевіряє наявність userId у команді
    [[nodiscard]] bool hasMember(const std::string& userId) const;
};
