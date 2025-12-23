#include<iostream>
using namespace std;

class CashDispenser {
    private:
        CashDispenser* nextDispenser;
    public:
        CashDispenser() : nextDispenser(nullptr) {}
        virtual void dispenseCash(int amount) = 0;
        virtual ~CashDispenser() {}
        CashDispenser* getNextDispenser() {
            return nextDispenser;
        }
        void setNextDispenser(CashDispenser* next) {
            nextDispenser = next;
        }
};

class TwoThousandDispenser : public CashDispenser {
    private:
        int numNotes;
    public:
        TwoThousandDispenser() : numNotes(5) {}
        void dispenseCash(int amount) override {
            if (amount >= 2000 && numNotes > 0) {
                int num = amount / 2000;
                amount -= min(numNotes,num) * 2000;
                cout << "Dispensing " << min(numNotes,num) << " notes of 2000" << endl;
            }
            if (amount > 0 && getNextDispenser() != nullptr) {
                getNextDispenser()->dispenseCash(amount);
            }
        }
};

class FiveHundredDispenser : public CashDispenser {
    private:
        int numNotes;
    public:
        FiveHundredDispenser() : numNotes(10) {}
        void dispenseCash(int amount) override {
            if (amount >= 500 && numNotes > 0) {
                int num = amount / 500;
                amount -= min(numNotes,num) * 500;
                cout << "Dispensing " << min(numNotes,num) << " notes of 500" << endl;
            }
            if (amount > 0 && getNextDispenser() != nullptr) {
                getNextDispenser()->dispenseCash(amount);
            }
        }
};

class TwoHundredDispenser : public CashDispenser {
    private:
        int numNotes;
    public:
        TwoHundredDispenser() : numNotes(20) {}
        void dispenseCash(int amount) override {
            if (amount >= 200 && numNotes > 0) {
                int num = amount / 200;
                amount -= min(numNotes,num) * 200;
                cout << "Dispensing " << min(numNotes,num) << " notes of 200" << endl;
            }
            if (amount > 0 && getNextDispenser() != nullptr) {
                getNextDispenser()->dispenseCash(amount);
            }
        }
};

class HundredDispenser : public CashDispenser {
    private:
        int numNotes;
    public:
        HundredDispenser() : numNotes(50) {}
        void dispenseCash(int amount) override {
            if (amount >= 100 && numNotes > 0) {
                int num = amount / 100;
                amount -= min(numNotes,num) * 100;
                cout << "Dispensing " << min(numNotes,num) << " notes of 100" << endl;
            }
            if (amount > 0 && getNextDispenser() != nullptr) {
                getNextDispenser()->dispenseCash(amount);
            }
            else if (amount > 0) {
                cout << "Cannot dispense remaining amount: " << amount << endl;
            }
        }
};

int main() {
    cout << "Cash Dispenser - Chain of Responsibility Pattern" << endl << endl;

    CashDispenser* twoThousandDispenser = new TwoThousandDispenser();
    CashDispenser* fiveHundredDispenser = new FiveHundredDispenser();
    CashDispenser* twoHundredDispenser = new TwoHundredDispenser();
    CashDispenser* hundredDispenser = new HundredDispenser();
    twoThousandDispenser->setNextDispenser(fiveHundredDispenser);
    fiveHundredDispenser->setNextDispenser(twoHundredDispenser);
    twoHundredDispenser->setNextDispenser(hundredDispenser);

    int amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    twoThousandDispenser->dispenseCash(amount);

    return 0;
}
