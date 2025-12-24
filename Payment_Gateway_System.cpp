#include<iostream>
using namespace std;

enum PaymentMethod {
    PAYPAL,
    PAYTM
};

class paymentRequest {
    public:
        double amount;
        string currency;
        PaymentMethod paymentMethod;
        paymentRequest(double amt, string curr, PaymentMethod method) 
            : amount(amt), currency(curr), paymentMethod(method) {}
};

class BankingSystem {
    public:
        virtual bool processPayment(paymentRequest pr) = 0;
        virtual ~BankingSystem() {}
};

class PayPalBankingSystem : public BankingSystem {
    public:
        bool processPayment(paymentRequest pr) override {
            cout << "Processing PayPal payment of " <<pr.currency << pr.amount << endl;
            return true;
        }
};

class PaytmBankingSystem : public BankingSystem {
    public:
        bool processPayment(paymentRequest pr) override {
            cout << "Processing Paytm payment of INR " << pr.amount << endl;
            return true;
        }
};

class PaymentGateway {
    protected:
        BankingSystem* bankingSystem;
    public:
        virtual bool processPayment(paymentRequest pr) {
            return bankingSystem->processPayment(pr);
        }
        virtual bool initiatePayment(paymentRequest pr) = 0;
        virtual bool validatePayment(paymentRequest pr) = 0;
        virtual bool cancelPayment(paymentRequest pr) = 0;
        virtual bool confirmPayment(paymentRequest pr) = 0;
        BankingSystem* getBankingSystem() {
            return bankingSystem;
        }
        virtual ~PaymentGateway() {
            if(bankingSystem != nullptr)
                delete bankingSystem;
        }
};

class PaytmPaymentGateway : public PaymentGateway {
    public:
        PaytmPaymentGateway() {
            bankingSystem = new PaytmBankingSystem();
        }
        bool initiatePayment(paymentRequest pr) override {
            if(bankingSystem->processPayment(pr) == false) {
                cout << "Paytm Payment Gateway: Payment initiation failed." << endl;
                return false;
            }
            return true;
        }
        bool validatePayment(paymentRequest pr) override {
            if(pr.amount<0 || pr.currency != "INR") {
                cout << "Paytm only supports INR currency, Please Retry with Another Method." << endl;
                return false;
            }
            cout << "Paytm Payment Gateway: Validating payment of INR: " << pr.amount << endl;
            return true;
        }
        bool cancelPayment(paymentRequest pr) override {
            cout << "Paytm Payment Gateway: Cancelling payment of INR" << pr.amount << endl;
            return true;
        }
        bool confirmPayment(paymentRequest pr) override {
            cout << "Paytm Payment Gateway: Confirming payment of INR" << pr.amount << endl;
            return true;
        }
};

class PaypalPaymentGateway : public PaymentGateway {
    public:
        PaypalPaymentGateway() {
            bankingSystem = new PayPalBankingSystem();
        }
        bool initiatePayment(paymentRequest pr) override {
            if(bankingSystem->processPayment(pr) == false) {
                cout << "PayPal Payment Gateway: Payment initiation failed." << endl;
                return false;
            }
            return true;
        }
        bool validatePayment(paymentRequest pr) override {
            if(pr.amount<0) {
                cout << "PayPal Payment Gateway: Invalid payment amount." << endl;
                return false;
            }
            return true;
        }
        bool cancelPayment(paymentRequest pr) override {
            cout << "PayPal Payment Gateway: Cancelling payment of " <<pr.currency <<": " << pr.amount << endl;
            return true;
        }
        bool confirmPayment(paymentRequest pr) override {
            cout << "PayPal Payment Gateway: Confirming payment of " <<pr.currency <<": " << pr.amount << endl;
            return true;
        }
};

class PaymentGatewayProxy : public PaymentGateway {
    private:
        PaymentGateway* realGateway;
    public:
        PaymentGatewayProxy(PaymentGateway* pg) : realGateway(pg) {
            bankingSystem = nullptr;
        }
        bool processPayment(paymentRequest pr) override {
            cout << "Proxy: Logging payment request of " << pr.currency << pr.amount << endl;
            if(realGateway->validatePayment(pr) == false) {
                cout << "Proxy: Payment validation failed." << endl;
                return false;
            }
            if(realGateway->initiatePayment(pr) == false) {
                cout << "Proxy: Payment initiation failed." << endl;
                return false;
            }
            if(realGateway->confirmPayment(pr) == false) {
                cout << "Proxy: Payment confirmation failed." << endl;
                return false;
            }

            return true;
        }
        bool initiatePayment(paymentRequest pr) override {
            return realGateway->initiatePayment(pr);
        }
        bool validatePayment(paymentRequest pr) override {
            return realGateway->validatePayment(pr);
        }
        bool cancelPayment(paymentRequest pr) override {
            return realGateway->cancelPayment(pr);
        }
        bool confirmPayment(paymentRequest pr) override {
            return realGateway->confirmPayment(pr);
        }
        ~PaymentGatewayProxy() {
            delete realGateway;
        }
};

//singleton factory
class paymentGatewayFactory {
    private:
        paymentGatewayFactory() {}
        static paymentGatewayFactory* instance;
    public:
        static paymentGatewayFactory* getInstance() {
            if(instance == nullptr) {
                instance = new paymentGatewayFactory();
            }
            return instance;
        }
        PaymentGateway* createPaymentGateway(PaymentMethod method) {
            switch(method) {
                case PAYTM: {
                    return new PaymentGatewayProxy(new PaytmPaymentGateway());
                }
                case PAYPAL:
                    return new PaymentGatewayProxy(new PaypalPaymentGateway());
                default:
                    return nullptr;
            }
        }
};
paymentGatewayFactory* paymentGatewayFactory::instance = nullptr;

//singleton service
class PaymentService {
    private:
        PaymentGateway* paymentGateway;
        static PaymentService* instance;
        PaymentService() {}
    public:
        static PaymentService* getInstance() {
            if(instance == nullptr) {
                instance = new PaymentService();
            }
            return instance;
        }
        bool makePayment(paymentRequest pr) {
            paymentGateway = paymentGatewayFactory::getInstance()->createPaymentGateway(pr.paymentMethod);
            if(!paymentGateway->processPayment(pr)) {
                paymentGateway->cancelPayment(pr);
                return false;
            }
            return true;
        }
        ~PaymentService() {
            delete paymentGateway;
        }
};

PaymentService* PaymentService::instance = nullptr;

class PaymentClient {
    public:
        void executePayment(double amount, string currency, PaymentMethod method) {
            paymentRequest pr(amount, currency, method);
            PaymentService* service = PaymentService::getInstance();
            if(service->makePayment(pr)) {
                cout << "Payment of " << currency << amount << " successful!" << endl;
            } else {
                cout << "Payment of " << currency << amount << " failed!" << endl;
            }
        }
};

int main() {
    cout << "Payment Gateway System Module" << endl;
    PaymentClient client;
    cout<<"---Executing Payments---"<<endl;
    client.executePayment(100.0, "USD", PAYPAL);
    cout<<"------------------------"<<endl;
    client.executePayment(200.0, "INR", PAYTM);
    cout<<"------------------------"<<endl;
    client.executePayment(150.0, "USD", PAYTM);
    return 0;
}
