#include <gtest/gtest.h>
#include "../src/task.h"
#include "../src/team.h"

// ============================================================
//  ТЕСТИ КЛАСУ Task
// ============================================================

// ---- Конструктор: EP (допустимі / недопустимі аргументи) ----

TEST(TaskConstructor, ValidArguments_EP_Positive) {
    // Arrange
    std::string id = "t1", title = "Fix bug", assignee = "user42";

    // Act
    Task task(id, title, assignee);

    // Assert
    EXPECT_EQ(task.taskId,     "t1");
    EXPECT_EQ(task.title,      "Fix bug");
    EXPECT_EQ(task.assigneeId, "user42");
    EXPECT_EQ(task.status,     TaskStatus::TODO);
    // Техніка: EP — допустимий клас (всі поля непорожні)
}

TEST(TaskConstructor, EmptyTaskId_EP_Negative) {
    // Arrange + Act + Assert
    // Техніка: EP — недопустимий клас (порожній taskId)
    EXPECT_THROW(Task("", "Fix bug"), std::invalid_argument);
}

TEST(TaskConstructor, EmptyTitle_EP_Negative) {
    // Техніка: EP — недопустимий клас (порожній title)
    EXPECT_THROW(Task("t1", ""), std::invalid_argument);
}

TEST(TaskConstructor, NoAssignee_EP_Positive) {
    // Техніка: EP — допустимий клас (assigneeId не обов'язковий)
    Task task("t2", "Write docs");
    EXPECT_TRUE(task.assigneeId.empty());
    EXPECT_EQ(task.status, TaskStatus::TODO);
}

// ---- updateProgress: EP (допустимі переходи) + BVA (межі стану) ----

TEST(TaskUpdateProgress, TodoToInProgress_EP_Positive) {
    // Arrange
    Task task("t1", "Do work");

    // Act
    task.updateProgress(TaskStatus::IN_PROGRESS);

    // Assert
    EXPECT_EQ(task.status, TaskStatus::IN_PROGRESS);
    // Техніка: EP — допустимий перехід TODO→IN_PROGRESS
}

TEST(TaskUpdateProgress, InProgressToDone_EP_Positive) {
    // Arrange
    Task task("t1", "Do work");
    task.updateProgress(TaskStatus::IN_PROGRESS);

    // Act
    task.updateProgress(TaskStatus::DONE);

    // Assert
    EXPECT_EQ(task.status, TaskStatus::DONE);
    // Техніка: EP — допустимий перехід IN_PROGRESS→DONE
}

TEST(TaskUpdateProgress, TodoToDone_EP_Negative) {
    // Техніка: EP — недопустимий перехід TODO→DONE (пропуск стану)
    Task task("t1", "Do work");
    EXPECT_THROW(task.updateProgress(TaskStatus::DONE), std::logic_error);
}

TEST(TaskUpdateProgress, DoneToInProgress_EP_Negative) {
    // Техніка: EP — недопустимий перехід (задача вже закрита)
    Task task("t1", "Do work");
    task.updateProgress(TaskStatus::IN_PROGRESS);
    task.updateProgress(TaskStatus::DONE);
    EXPECT_THROW(task.updateProgress(TaskStatus::IN_PROGRESS), std::logic_error);
}

TEST(TaskUpdateProgress, TodoToTodo_BVA_Negative) {
    // Техніка: BVA — повторний перехід у той самий стан (межа: однаковий статус)
    Task task("t1", "Do work");
    EXPECT_THROW(task.updateProgress(TaskStatus::TODO), std::logic_error);
}

// ---- getAssignee: EP (порожній / непорожній assigneeId) ----

TEST(TaskGetAssignee, WithAssignee_EP_Positive) {
    // Техніка: EP — assigneeId непорожній
    Task task("t1", "Task", "user99");
    EXPECT_EQ(task.getAssignee(), "user99");
}

TEST(TaskGetAssignee, WithoutAssignee_EP_Positive) {
    // Техніка: EP — assigneeId порожній → повертає "(unassigned)"
    Task task("t1", "Task");
    EXPECT_EQ(task.getAssignee(), "(unassigned)");
}

// ---- isCompleted: BVA (межі статусу) ----

TEST(TaskIsCompleted, StatusTodo_BVA) {
    // Техніка: BVA — стан TODO (нижня межа)
    Task task("t1", "Task");
    EXPECT_FALSE(task.isCompleted());
}

TEST(TaskIsCompleted, StatusInProgress_BVA) {
    // Техніка: BVA — стан IN_PROGRESS (проміжна межа)
    Task task("t1", "Task");
    task.updateProgress(TaskStatus::IN_PROGRESS);
    EXPECT_FALSE(task.isCompleted());
}

TEST(TaskIsCompleted, StatusDone_BVA) {
    // Техніка: BVA — стан DONE (верхня межа)
    Task task("t1", "Task");
    task.updateProgress(TaskStatus::IN_PROGRESS);
    task.updateProgress(TaskStatus::DONE);
    EXPECT_TRUE(task.isCompleted());
}

// ============================================================
//  ТЕСТИ КЛАСУ Team
// ============================================================

// ---- Конструктор: EP ----

TEST(TeamConstructor, ValidArguments_EP_Positive) {
    // Техніка: EP — допустимий клас
    Team team("team1", "Alpha", "leader1");
    EXPECT_EQ(team.name,     "Alpha");
    EXPECT_EQ(team.leaderId, "leader1");
    EXPECT_EQ(team.getMemberCount(), 0u);
}

TEST(TeamConstructor, EmptyName_EP_Negative) {
    // Техніка: EP — недопустимий клас (порожня назва)
    EXPECT_THROW(Team("team1", "", "leader1"), std::invalid_argument);
}

TEST(TeamConstructor, EmptyLeaderId_EP_Negative) {
    // Техніка: EP — недопустимий клас (порожній leaderId)
    EXPECT_THROW(Team("team1", "Alpha", ""), std::invalid_argument);
}

// ---- join: EP + BVA (межа: 0 учасників / 1 / дублікат) ----

TEST(TeamJoin, AddFirstMember_BVA) {
    // Техніка: BVA — перший учасник (межа: розмір 0→1)
    Team team("team1", "Alpha", "leader1");
    team.join("user1");
    EXPECT_EQ(team.getMemberCount(), 1u);
    EXPECT_TRUE(team.hasMember("user1"));
}

TEST(TeamJoin, AddMultipleMembers_EP_Positive) {
    // Техніка: EP — допустимий клас (кілька різних userId)
    Team team("team1", "Alpha", "leader1");
    team.join("user1");
    team.join("user2");
    team.join("user3");
    EXPECT_EQ(team.getMemberCount(), 3u);
}

TEST(TeamJoin, DuplicateMember_EP_Negative) {
    // Техніка: EP — недопустимий клас (дублікат userId)
    Team team("team1", "Alpha", "leader1");
    team.join("user1");
    EXPECT_THROW(team.join("user1"), std::runtime_error);
}

TEST(TeamJoin, EmptyUserId_EP_Negative) {
    // Техніка: EP — недопустимий клас (порожній userId)
    Team team("team1", "Alpha", "leader1");
    EXPECT_THROW(team.join(""), std::invalid_argument);
}

// ---- hasMember: BVA (порожня команда / є учасник / нема) ----

TEST(TeamHasMember, EmptyTeam_BVA) {
    // Техніка: BVA — порожня команда (нижня межа)
    Team team("team1", "Alpha", "leader1");
    EXPECT_FALSE(team.hasMember("user1"));
}

TEST(TeamHasMember, MemberExists_EP_Positive) {
    // Техніка: EP — учасник є у команді
    Team team("team1", "Alpha", "leader1");
    team.join("user1");
    EXPECT_TRUE(team.hasMember("user1"));
}

TEST(TeamHasMember, MemberNotExists_EP_Positive) {
    // Техніка: EP — учасника немає у команді
    Team team("team1", "Alpha", "leader1");
    team.join("user1");
    EXPECT_FALSE(team.hasMember("user999"));
}

// ---- getMembers: повертає правильний список ----

TEST(TeamGetMembers, ReturnsCorrectList_EP_Positive) {
    // Техніка: EP — позитивний сценарій
    Team team("team1", "Alpha", "leader1");
    team.join("userA");
    team.join("userB");
    auto members = team.getMembers();
    ASSERT_EQ(members.size(), 2u);
    EXPECT_EQ(members[0], "userA");
    EXPECT_EQ(members[1], "userB");
}
