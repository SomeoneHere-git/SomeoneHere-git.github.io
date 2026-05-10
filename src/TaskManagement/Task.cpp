#include <chrono>
#include <string>
#include <uuid.h>
#include <vector>

namespace TaskM {
class User;
enum class TaskStatus { TODO, IN_PROGRESS, DONE };

class Task {
private:
  std::string description;
  uuids::uuid id;
  TaskStatus status;

  std::chrono::system_clock::time_point deadline;

  std::vector<User *> assignedUsers;

public:
  Task(std::string desc, auto deadline)
      : description(std::move(desc)), deadline(deadline) {};
  ~Task() = default;
  void updateStatus(TaskStatus newStatus) { status = newStatus; }

  void subscribeUser(User *user) { assignedUsers.push_back(user); }
};
} // namespace TaskM
