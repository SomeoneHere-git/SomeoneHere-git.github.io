#include "task.h"

Task::Task(const std::string& taskId,
           const std::string& title,
           const std::string& assigneeId)
    : taskId(taskId), title(title), status(TaskStatus::TODO), assigneeId(assigneeId)
{
    if (taskId.empty()) {
        throw std::invalid_argument("taskId cannot be empty");
    }
    if (title.empty()) {
        throw std::invalid_argument("title cannot be empty");
    }
}

void Task::updateProgress(TaskStatus newStatus)
{
    // TODO → IN_PROGRESS: дозволено
    if (status == TaskStatus::TODO && newStatus == TaskStatus::IN_PROGRESS) {
        status = newStatus;
        return;
    }
    // IN_PROGRESS → DONE: дозволено
    if (status == TaskStatus::IN_PROGRESS && newStatus == TaskStatus::DONE) {
        status = newStatus;
        return;
    }
    // Всі інші переходи заборонені
    throw std::logic_error("Invalid status transition");
}

std::string Task::getAssignee() const
{
    if (assigneeId.empty()) {
        return "(unassigned)";
    }
    return assigneeId;
}

bool Task::isCompleted() const
{
    return status == TaskStatus::DONE;
}
