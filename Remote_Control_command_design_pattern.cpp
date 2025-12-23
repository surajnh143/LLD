#include<iostream>
using namespace std;
class Light {
    bool isOn;
    public:
        void turnOn() {
            isOn = true;
            cout<<"Light is ON"<<endl;
        }
        void turnOff() {
            isOn = false;
            cout<<"Light is OFF"<<endl;
        }
        bool getStatus() {
            return isOn;
        }
};
class Fan {
    bool isOn;
    public:
        void turnOn() {
            isOn = true;
            cout<<"Fan is ON"<<endl;
        }
        void turnOff() {
            isOn = false;
            cout<<"Fan is OFF"<<endl;
        }
        bool getStatus() {
            return isOn;
        }
};
class AC {
    bool isOn;
    public:
        void turnOn() {
            isOn = true;
            cout<<"AC is ON"<<endl;
        }
        void turnOff() {
            isOn = false;
            cout<<"AC is OFF"<<endl;
        }
        bool getStatus() {
            return isOn;
        }
};
// Command Interface
class ICommand {
    public:
        virtual void execute()=0;
};
class LightCommand : public ICommand {
    private:
        Light* light;
    public:
        LightCommand(Light* l) : light(l) {}
        void execute() override {
            if(light->getStatus())
                light->turnOff();
            else
                light->turnOn();
        }
};
class FanCommand : public ICommand {
    private:
        Fan* fan;
    public:
        FanCommand(Fan* f) : fan(f) {}
        void execute() override {
            if(fan->getStatus())
                fan->turnOff();
            else
                fan->turnOn();
        }
};
class ACCommand : public ICommand {
    private:
        AC* ac;
    public:
        ACCommand(AC* a) : ac(a) {}
        void execute() override {
            if(ac->getStatus())
                ac->turnOff();
            else
                ac->turnOn();
        }
};
//Singleton Class
class RemoteControl {
    private:
        vector<ICommand*> commands;
        static RemoteControl* instance;
        RemoteControl(vector<ICommand*> cmds) : commands(cmds) {}
    public:
        static RemoteControl* getInstance(vector<ICommand*> cmds) {
            if(instance == nullptr)
                instance = new RemoteControl(cmds);
            return instance;
        }
        void pressButton(int i) {
            commands[i]->execute();
        }
};
RemoteControl* RemoteControl::instance = nullptr;
RemoteControl* InitializeRemoteControl() {
    Light* light = new Light();
    Fan* fan = new Fan();
    AC* ac = new AC();
    vector<ICommand*> commands;
    commands.push_back(new LightCommand(light));
    commands.push_back(new FanCommand(fan));
    commands.push_back(new ACCommand(ac));
    return RemoteControl::getInstance(commands);
}
int main() {
    RemoteControl* remote = InitializeRemoteControl();
    remote->pressButton(0); // Toggle Light
    remote->pressButton(1); // Toggle Fan
    remote->pressButton(0); // Toggle Light
    remote->pressButton(2); // Toggle AC
    remote->pressButton(1); // Toggle Fan

    return 0;
}
