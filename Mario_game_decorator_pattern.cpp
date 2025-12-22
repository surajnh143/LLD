#include<iostream>
using namespace std;

class ICharacter {
    public:
        virtual string getAbility()=0;
};
class Mario : public ICharacter {
    public:
        string getAbility() override {
            return "Mario Charecter ";
        }
};
class IDecorator : public ICharacter {
    protected:
        ICharacter* character;
    public:
        IDecorator(ICharacter* c) : character(c) {}
};

class decorateWithHeightUp : public IDecorator {
    public:
        decorateWithHeightUp(ICharacter* c) : IDecorator(c) {}
        string getAbility() override {
            return character->getAbility() + "with Height Up ";
        }
};

class decorateWithFireFlower : public IDecorator {
    public:
        decorateWithFireFlower(ICharacter* c) : IDecorator(c) {}
        string getAbility() override {
            return character->getAbility() + "with Fire Flower ";
        }
};

class decorateWithStarPower : public IDecorator {
    public:
        decorateWithStarPower(ICharacter* c) : IDecorator(c) {}
        string getAbility() override {
            return character->getAbility() + "with Star Power ";
        }
};

int main() {
    ICharacter* mario1 = new decorateWithFireFlower(new decorateWithHeightUp(new Mario()));
    cout<<mario1->getAbility()<<endl;
    ICharacter* mario2 = new decorateWithStarPower(new decorateWithFireFlower(new Mario()));
    cout<<mario2->getAbility()<<endl;
    ICharacter* mario3 = new decorateWithHeightUp(new decorateWithStarPower(new decorateWithFireFlower(new Mario())));
    cout<<mario3->getAbility()<<endl;
    return 0;
}
