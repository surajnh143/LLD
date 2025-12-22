#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

// Notification Interface
class INotification {
    public:
        virtual string getContent()=0;
};
class SimpleNotification : public INotification {
    protected:
        string text;
    public:
        SimpleNotification( string t) : text(t) {}
        string getContent() override {
            return text;
        }
};

class INotificationDecorator : public INotification {
    protected:
        INotification* notification;
    public:
        INotificationDecorator(INotification* n) : notification(n) {}
};

class decoratorWithSignature : public INotificationDecorator {
    public:
        decoratorWithSignature(INotification* n) : INotificationDecorator(n) {}
        string getContent() override {
            return notification->getContent() + "\n-- Regards, John Doe";
        }
};

class decoratorWithTimeStamp : public INotificationDecorator {
    public:
        decoratorWithTimeStamp(INotification* n) : INotificationDecorator(n) {}
        string getContent() override {
            std::time_t now = std::time(nullptr);
            return notification->getContent() + "\nSent at: " + std::ctime(&now);
        }
};
class INotificationObserver {
    public:
        virtual void update(INotification* n)=0;
};

class LoggerNotificationObserver : public INotificationObserver {
    public:
        void update(INotification* n) override {
            cout<<"Logging Notification: "<<n->getContent()<<endl;
        }
};

class INotificationStrategy {
    public:
        virtual void send(INotification* n)=0;
};

class EmailNotificationStrategy : public INotificationStrategy {
    public:
        void send(INotification* n) override {
            cout<<"Sending Email Notification: "<<n->getContent()<<endl;
        }
};

class SMSNotificationStrategy : public INotificationStrategy {
    public:
        void send(INotification* n) override {
            cout<<"Sending SMS Notification: "<<n->getContent()<<endl;
        }
};

class PushNotificationStrategy : public INotificationStrategy {
    public:
        void send(INotification* n) override {
            cout<<"Sending Push Notification: "<<n->getContent()<<endl;
        }
};


class INotificationEngine : public INotificationObserver {
    protected:
        vector<INotificationStrategy*> strategies;
    public:
        INotificationEngine() {
            strategies.push_back(new EmailNotificationStrategy());
            strategies.push_back(new SMSNotificationStrategy());
            strategies.push_back(new PushNotificationStrategy());
        }
        void addStrategy(INotificationStrategy* strategy) {
            strategies.push_back(strategy);
        }
        void update(INotification* n) override {
            //cout<<"Sending Notification: "<<n->getContent()<<endl;
            for(auto strategy : strategies) {
                strategy->send(n);
            }
        }
};

class INotificationObservable {
    protected:
        vector<INotificationObserver*> observers;
    public:
        virtual void notify(INotification* n)=0;
        void addObserver(INotificationObserver* observer) {
            observers.push_back(observer);
        }
};
class NotificationObservable : public INotificationObservable {
    public:
        void notify(INotification* n) override {
            for(auto observer : observers) {
                observer->update(n);
            }
        }
};

// singleton Notification Service
class NotificationService {
    private:
        vector<INotification* > notifications;
        NotificationObservable* observable;
        static NotificationService* instance;
        NotificationService(NotificationObservable* observable) : observable(observable) {
            observable->addObserver(new LoggerNotificationObserver());
            observable->addObserver(new INotificationEngine());
        }
    public:
        static NotificationService* getInstance(NotificationObservable* observable) {
            if(instance == nullptr)
                instance = new NotificationService(observable);
            return instance;
        }

        void addNotification(INotification* n) {
            notifications.push_back(n);
        }

        void printNotifications() {
            cout<<"Printing All Notifications: \n";
            for(auto n : notifications) {
                cout<<n->getContent()<<endl;
            }
        }

        void createNotification(string text) {
            INotification* n = new SimpleNotification(text);
            n = new decoratorWithSignature(n);
            n = new decoratorWithTimeStamp(n);
            addNotification(n);
            observable->notify(n);
        }
};

NotificationService* NotificationService::instance = nullptr;

int main() {
    NotificationObservable* observable = new NotificationObservable();
    NotificationService* service = NotificationService::getInstance(observable);

    service->createNotification("Your order has been shipped.");
    service->createNotification("Your password has been changed.");
    service->createNotification("New login from unrecognized device.");

    service->printNotifications();

    return 0;
}
