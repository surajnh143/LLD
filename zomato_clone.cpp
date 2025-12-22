#include<iostream>
using namespace std;
//<model_class>
class MenuItem {
    private:
        int id;
        string name;
        double price;
        string description;
    public:
        MenuItem(int id, const string& n, double p, const string& d) : 
        id(id), name(n), price(p), description(d) {}
        string getName() { return name; }
        double getPrice() { return price; }
        string getDescription() { return description; }
        int getId() { return id; }
};
//<model_class>
class Restraunt {
    private:
        int id;
        string name;
        string location;
        vector<MenuItem> menu;
    public:
        Restraunt(int id,const string& n, const string& loc) : 
        id(id),name(n), location(loc) {}
        void addMenuItem(MenuItem item) {
            menu.push_back(item);
        }
        vector<MenuItem> getMenu() {
            return menu;
        }
        int getId() { return id; }
        string getLocation() { return location; }
        string getName() { return name; }
};

//singleton class
class RestrauntService {
    private:
        static RestrauntService* instance;
        vector<Restraunt> restraunts;
        RestrauntService() {}
    public:
        static RestrauntService* getInstance() {
            if (!instance) {
                instance = new RestrauntService();
            }
            return instance;
        }
        void addRestraunt(Restraunt r) {
            restraunts.push_back(r);
        }
        vector<Restraunt> getRestraunts() {
            return restraunts;
        }
};
RestrauntService* RestrauntService::instance = nullptr;
class cart {
    private:
        vector<MenuItem> items;
        double totalPrice;
        Restraunt restraunt;
    public:
        cart(Restraunt rs) : restraunt(rs) {}
        void addItem(MenuItem item) {
            cout<<"adding item:" << item.getName()<<" to cart"<<endl;
            items.push_back(item);
        }
        vector<MenuItem> getItems() {
            return items;
        }
        void calculateTotalPrice() {
            totalPrice = 0;
            for (auto item : items) {
                totalPrice += item.getPrice();
            }
        }
        double getTotalPrice() {
            return totalPrice;
        }
        void setRestraunt(Restraunt r) {
            restraunt = r;
        }
        Restraunt getRestraunt() {
            return restraunt;
        }
};

class user {
    private:
        int id;
        string name;
        cart userCart;
        string address;
    public:
        user(int user_id, const string& n,const string& add,cart ct) : 
        id(user_id), name(n),address(add),userCart(ct) {}
        cart getCart() {
            return userCart;
        }
        int getId() { return id; }
        string getName() { return name; }
        void setAddress(string addr) {
            address = addr;
        }
        string getAddress() {
            return address;
        }
        void printDetails() {
            cout << "User ID: " << id << ", Name: " << name << ", Address: " << address << endl;
        }
};
class paymentservice {
    public:
        virtual bool processPayment(double amount) = 0;
};
class CreditCardPayment : public paymentservice {
    public:
        bool processPayment(double amount) override {
            cout << "Processing credit card payment of " << amount << endl;
            return true;
        }
};
class upiPayment : public paymentservice {
    public:
        bool processPayment(double amount) override {
            cout << "Processing UPI payment of " << amount << endl;
            return true;
        }
};
class netbankingPayment : public paymentservice {
    public:
        bool processPayment(double amount) override {
            cout << "Processing Netbanking payment of " << amount << endl;
            return true;
        }
};

//abstract class
class order {
    private:
        int id;
        user orderUser;
        cart orderCart;
        string status;
        paymentservice* paymentMethod;
    public:
        order(int order_id, user u, cart c, paymentservice* pmt) : 
        id(order_id), orderUser(u), orderCart(c), status("Placed"), paymentMethod(pmt) {}
        void setStatus(const string& s) {
            status = s;
        }
        string getStatus() {
            return status;
        }
        int getId() { return id; }
        user getUser() { return orderUser; }
        cart getCart() { return orderCart; }
        virtual void getType() = 0;
};
class DeliveryOrder : public order {
    public:
        DeliveryOrder(int order_id, user u, cart c,paymentservice* pmt): 
        order(order_id, u, c, pmt) {}
        void getType() override {
            cout << "Delivery Order to " << getUser().getAddress() << endl;
        }
};
class pickupOrder : public order {
public:
    pickupOrder(int order_id, user u, cart c, paymentservice* pmt): 
    order(order_id, u, c, pmt) {}
    void getType() override {
        cout << "Pickup Order Location: " << getCart().getRestraunt().getLocation()<< endl;
    }
};

class orderFactory {
    public:
        virtual order* createOrder(int order_id, user u, cart c, 
        paymentservice* pmt,string orderType) = 0;
};
class orderNowFactory : public orderFactory {
    public:
        order* createOrder(int order_id, user u, cart c, paymentservice* pmt, string orderType) override {
            if(orderType == "Pickup") {
                return new pickupOrder(order_id, u, c, pmt);
            } else if(orderType == "Delivery")
                return new DeliveryOrder(order_id, u, c, pmt);
            return nullptr;
        }
};
class orderScheduledFactory : public orderFactory {
    private:
        string scheduledTime;
    public:
        order* createOrder(int order_id, user u, cart c, paymentservice* pmt, string orderType) override {
            if(orderType == "Pickup") {
                return new pickupOrder(order_id, u, c, pmt);
            } else if(orderType == "Delivery")
                return new DeliveryOrder(order_id, u, c, pmt);
            return nullptr;
        }
        void setScheduledTime(const string& time) {
            scheduledTime = time;
        }
        string getScheduledTime() {
            return scheduledTime;
        }
};

class notificationService {
    public:
        void sendNotification(user u, const string& message) {
            cout << "Notification to " << u.getName() << ": " << message << endl;
        }
};
class foodDeliveryClient
{
    private:
        RestrauntService* restrauntService;
        notificationService* notifyService;
    public:
        foodDeliveryClient() {
            restrauntService = RestrauntService::getInstance();
            notifyService = new notificationService();
        }
        void browseRestraunts() {
            vector<Restraunt> restraunts = restrauntService->getRestraunts();
            for (auto r : restraunts) {
                cout << "Restraunt: " << r.getName() << ", Location: " << r.getLocation() << endl;
            }
        }
        void placeOrder(order* ord) {
            cart c = ord->getCart();
            c.calculateTotalPrice();
            double amount = c.getTotalPrice();
            paymentservice* pmt = ord->getUser().getCart().getRestraunt().getMenu().empty() ? nullptr : new CreditCardPayment();
            if (pmt && pmt->processPayment(amount)) {
                ord->setStatus("Confirmed");
                notifyService->sendNotification(ord->getUser(), "Your order has been placed successfully!");
            } else {
                ord->setStatus("Payment Failed");
                notifyService->sendNotification(ord->getUser(), "Payment failed. Please try again.");
            }
        }
};

int main() {
    foodDeliveryClient* client= new foodDeliveryClient();
    Restraunt* r1= new Restraunt(1, "Biryani by Kilo", "ABC, sector-135");
    r1->addMenuItem(MenuItem(1, "Chicken Biryani", 250.0, "Delicious chicken biryani"));
    r1->addMenuItem(MenuItem(2, "Mutton Biryani", 300.0, "Delicious mutton biryani"));
    r1->addMenuItem(MenuItem(3, "Veg Biryani", 200.0, "Delicious veg biryani"));
    RestrauntService::getInstance()->addRestraunt(*r1);
    Restraunt* r2= new Restraunt(1, "Punjabi Grill", "Advant, sector-142");
    r2->addMenuItem(MenuItem(1, "Butter Chicken", 250.0, "Delicious butter chicken"));
    r2->addMenuItem(MenuItem(2, "Paneer Tikka", 200.0, "Delicious paneer tikka"));
    r2->addMenuItem(MenuItem(3, "Dal Makhani", 150.0, "Delicious dal makhani"));
    RestrauntService::getInstance()->addRestraunt(*r2);

    client->browseRestraunts();
    
    cart* userCart = new cart(*r1);
    userCart->addItem(r1->getMenu()[0]);
    userCart->addItem(r1->getMenu()[1]);
    user* u1 = new user(1, "Suraj Kumar", "Lotus Zing, sector-168", *userCart);
    u1->printDetails();
    orderFactory* factory = new orderNowFactory();
    paymentservice* paymentMethod = new CreditCardPayment();
    order* ord1 = factory->createOrder(1, *u1, *userCart, paymentMethod, "Delivery");
    client->placeOrder(ord1);
    return 0;
}
