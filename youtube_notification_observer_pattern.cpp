#include<iostream>
#include<unordered_set>

using namespace std;

class Isubscriber;

class IchannelObserver {
    private:
        unordered_set<Isubscriber*> subscribers;
    public:
        virtual void notify(string title)=0;
        void subscribe(Isubscriber* subscriber) {
            subscribers.insert(subscriber);
        }
        void unsubscribe(Isubscriber* subscriber) {
            subscribers.erase(subscriber);
        }
        unordered_set<Isubscriber*> getSubscribers() {
            return subscribers;
        }
};

class Isubscriber {
    public:
        virtual void update(string title)=0;
};
class YoutubeChannel : public IchannelObserver {
    private:
        string channelName;
    public:
        YoutubeChannel(const string& name) : channelName(name) {}
        void notify(string title) override {
            for (auto subscriber : getSubscribers()) {
                subscriber->update(title);
            }
            cout<<endl;
        }
        void uploadVideo(const string& title) {
            cout << "Video titled '" << title << "' uploaded to channel '" << channelName << "'\n";
            notify(title);
        }
};

class User : public Isubscriber {
    private:
        string userName;
    public:
        User(const string& name) : userName(name) {}
        void update(string title) override {
            cout << "User '" << userName << "' notified of new video: " << title << "\n";
        }
};

int main() {
    YoutubeChannel* techChannel = new YoutubeChannel("Tech Reviews");
    YoutubeChannel* travelChannel = new YoutubeChannel("Travel Vlogs");
    User* alice = new User("Alice");
    User* bob = new User("Bob");
    User* charlie = new User("Charlie");

    techChannel->subscribe(alice);
    techChannel->subscribe(charlie);
    travelChannel->subscribe(bob);
    travelChannel->subscribe(charlie);

    techChannel->uploadVideo("Top 10 Gadgets of 2025");
    techChannel->uploadVideo("Best Laptops for Programming");
    travelChannel->uploadVideo("Exploring the Alps");
    travelChannel->unsubscribe(charlie);
    travelChannel->uploadVideo("A Week in Bali");

    return 0;
}
