#include <iostream>
#include <string>
#include <unordered_map>

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

class UserController {
 public:
  size_t Register(std::string telephone, std::string password) {
    // Omit the verification code of input parameters
    // Omit the try-catch code for userService.register() exceptions
    size_t user_id = user_service_.Register(telephone, password);
    promotion_service_.IssueNewUserExperienceCash(user_id);
    return user_id;
  }

 private:
  UserService user_service_;            // Dependency Injection
  PromotionService promotion_service_;  // Dependency Injection
};

int main() {
  UserController user_controller;
  user_controller.Register("12345678901", "abcabc");
  return 0;
}