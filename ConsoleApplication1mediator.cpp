#include <iostream>
#include <string>

class Colleague;

// Посередник
class Mediator {
public:
    virtual void sendMessage(const Colleague& colleague, const std::string& message) const = 0;
};

// Конкретний посередник
class ConcreteMediator : public Mediator {
public:
    void setColleague1(Colleague* colleague);
    void setColleague2(Colleague* colleague);
    void sendMessage(const Colleague& colleague, const std::string& message) const override;

private:
    Colleague* colleague1;
    Colleague* colleague2;
};

// Учасник
class Colleague {
public:
    explicit Colleague(Mediator* mediator, const std::string& name) : mediator(mediator), name(name) {}

    virtual void sendMessage(const std::string& message) const {
        mediator->sendMessage(*this, message);
    }

    virtual void receiveMessage(const std::string& message) const {
        std::cout << name << " отримав(ла) повідомлення: " << message << std::endl;
    }
protected:
    Mediator* mediator;
    std::string name;
};

// Конкретний учасник
class ConcreteColleague : public Colleague {
public:
    using Colleague::Colleague;  // конструктор базового класу

    void doSomething();
};

void ConcreteMediator::setColleague1(Colleague* colleague) {
    colleague1 = colleague;
}

void ConcreteMediator::setColleague2(Colleague* colleague) {
    colleague2 = colleague;
}

void ConcreteMediator::sendMessage(const Colleague& colleague, const std::string& message) const {
    if (&colleague == colleague1) {
        colleague2->receiveMessage(message);
    }
    else {
        colleague1->receiveMessage(message);
    }
}

void ConcreteColleague::doSomething() {
    std::cout << name << " робить щось важливе." << std::endl;
    sendMessage("Важлива інформація");
}

int main() {
    system("chcp 1251>nul");
    ConcreteMediator mediator;

    ConcreteColleague colleague1(&mediator, "Колега 1");
    ConcreteColleague colleague2(&mediator, "Колега 2");

    mediator.setColleague1(&colleague1);
    mediator.setColleague2(&colleague2);

    colleague1.doSomething();

    return 0;
}
