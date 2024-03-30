#ifndef OBSERVER_P2P_COMMON_H_
#define OBSERVER_P2P_COMMON_H_

#include <iostream>
#include <string>

class UserService {
 public:
  size_t Register(std::string telephone, std::string password) {
    size_t user_id = std::hash<std::string>{}(telephone + password);
    return user_id;
  }
};

class PromotionService {
 public:
  void IssueNewUserExperienceCash(size_t user_id) {
    std::cout << "Issue New User Experience Cash to: " << user_id << std::endl;
  }
};

class NotificationService {
 public:
  void SendInboxMessage(size_t user_id) {
    std::cout << "Send Inbox Message to: " << user_id << std::endl;
  }
};

#endif