#include <iostream>
#include <list>
#include <memory>
#include "p2p_common.h"

class RegObserver {
 public:
  virtual void HandleRegSuccess(UserIdType user_id) = 0;
};

class RegPromotionObserver : public RegObserver {
 public:
  RegPromotionObserver() {}
  RegPromotionObserver(const RegPromotionObserver&) = default;
  void HandleRegSuccess(UserIdType user_id) override {
    promotion_service_.IssueNewUserExperienceCash(user_id);
  }
 private:
  PromotionService promotion_service_; // Dependency Injection
};

class RegNotificationObserver : public RegObserver {
 public:
  RegNotificationObserver() {}
  void HandleRegSuccess(UserIdType user_id) override {
    notification_service_.SendInboxMessage(user_id);
  }
 private:
  NotificationService notification_service_; // Dependency Injection
};

class UserController {
 public:
  void SetRegObservers(std::list<std::shared_ptr<RegObserver>> observers) {
    observers_ = observers;
  }

  UserIdType Register(std::string telephone, std::string password) {
    // Omit the verification code of input parameters
    // Omit the try-catch code for userService.register() exceptions
    UserIdType user_id = user_service_.Register(telephone, password);
    for (auto reg : observers_) {
      reg->HandleRegSuccess(user_id);
    }
    return user_id;
  }

 private:
  std::list<std::shared_ptr<RegObserver>> observers_;
  UserService user_service_;
};

int main() {
  UserController user_controller;
  
  std::list<std::shared_ptr<RegObserver>> observers;
  observers.push_back(std::make_shared<RegPromotionObserver>());
  observers.push_back(std::make_shared<RegNotificationObserver>());

  user_controller.SetRegObservers(observers);
  user_controller.Register("12345678901", "abcabc");
  return 0;
}