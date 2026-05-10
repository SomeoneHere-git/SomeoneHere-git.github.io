#pragma once
#include <string>
#include <stdexcept>

// Статус задачі (відповідає UML: TaskStatus)
enum class TaskStatus {
    TODO,
    IN_PROGRESS,
    DONE
};

// Клас Task — відповідає UML-моделі з ЛР 02
class Task {
public:
    std::string taskId;
    std::string title;
    TaskStatus  status;
    std::string assigneeId;

    // Конструктор: створює задачу зі статусом TODO
    // Кидає std::invalid_argument, якщо taskId або title порожні
    Task(const std::string& taskId,
         const std::string& title,
         const std::string& assigneeId = "");

    // updateProgress: змінює статус задачі
    // Допустимі переходи: TODO→IN_PROGRESS, IN_PROGRESS→DONE
    // Кидає std::logic_error при недопустимому переході
    void updateProgress(TaskStatus newStatus);

    // getAssignee: повертає assigneeId або "(unassigned)" якщо порожній
    std::string getAssignee() const;

    // isCompleted: повертає true, якщо статус DONE
    bool isCompleted() const;
};
