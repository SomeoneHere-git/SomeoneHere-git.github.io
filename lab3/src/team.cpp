#include "team.h"
#include <algorithm>

Team::Team(const std::string& teamId,
           const std::string& name,
           const std::string& leaderId)
{
    if (name.empty()) {
        throw std::invalid_argument("Team name cannot be empty");
    }
    if (leaderId.empty()) {
        throw std::invalid_argument("leaderId cannot be empty");
    }
    this->teamId   = teamId;
    this->name     = name;
    this->leaderId = leaderId;
}

void Team::join(const std::string& userId)
{
    if (userId.empty()) {
        throw std::invalid_argument("userId cannot be empty");
    }
    if (hasMember(userId)) {
        throw std::runtime_error("User already in team");
    }
    memberIds.push_back(userId);
}

std::vector<std::string> Team::getMembers() const
{
    return memberIds;
}

size_t Team::getMemberCount() const
{
    return memberIds.size();
}

bool Team::hasMember(const std::string& userId) const
{
    return std::find(memberIds.begin(), memberIds.end(), userId) != memberIds.end();
}
