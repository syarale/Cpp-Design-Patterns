
#include <iostream>
#include <list>

class Observer;
class Message {};

class Subject {
 public:
  virtual void Register(Observer* observer) = 0;
  virtual void Unregister(Observer* observer) = 0;
  virtual void Notify(Message* message) = 0;
};

class Observer {
 public:
  virtual void Update(Message* message) = 0;
};

class ConcreteSubject : public Subject {
 public:
  void Register(Observer* observer) override {
    observers_.push_back(observer);
  }

  void Unregister(Observer* observer) override {
    observers_.remove(observer);
  }

  void Notify(Message* message) {
    for (auto observer : observers_) {
      observer->Update(message);
    }
  }

 private:
  std::list<Observer*> observers_;
};

class ConcreteObserverOne : public Observer {
 public:
  void Update(Message* message) override {
    std::cout << "Update concrete observer one" << std::endl;
  }
};

class ConcreteObserverTwo : public Observer {
 public:
  void Update(Message* mesage) override {
    std::cout << "Update concrete observer two" << std::endl;    
  }
};

int main() {
  ConcreteSubject* subject = new ConcreteSubject();
  subject->Register(new ConcreteObserverOne());
  subject->Register(new ConcreteObserverTwo());
  subject->Notify(new Message());
  return 0;
}
