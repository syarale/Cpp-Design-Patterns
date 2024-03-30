/*
 * Simple implementation of asynchronous non-blocking observer pattern 
 * for p2p example.
 */

#include <list>
#include <memory>
#include <thread>
#include "p2p_common.h"

class RegObserver {
 public:
  virtual void HandleRegSuccess(UserIdType user_id) = 0;
 protected:
  std::thread executor_;
};

class RegPromotionObserver : public RegObserver {
 public:
  RegPromotionObserver() {}
  RegPromotionObserver(const RegPromotionObserver&) = default;

  ~RegPromotionObserver() {
    if (executor_.joinable()) {
      executor_.join();
    }
  }
  
  void HandleRegSuccess(UserIdType user_id) override {
    executor_ = std::thread(&RegPromotionObserver::Run, this, user_id);
  }

 private:
  void Run(UserIdType user_id) {
    promotion_service_.IssueNewUserExperienceCash(user_id);
  }

  PromotionService promotion_service_; // Dependency Injection
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
  
  user_controller.SetRegObservers(observers);
  user_controller.Register("12345678901", "abcabc");
  return 0;
}