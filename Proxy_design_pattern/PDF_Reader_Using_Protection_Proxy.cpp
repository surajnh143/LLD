#include<iostream>
using namespace std;

class User {
    private:
        string username;
        bool isPremium;
    public:
        User(string uname, bool p = false) : username(uname), isPremium(p) {}
        bool hasPremium() {
            return isPremium;
        }
        string getUsername() {
            return username;
        }
};

class IPDFReader {
    public:
        virtual void displayPDF() = 0;
        virtual ~IPDFReader() {}
};

class RealPDFReader : public IPDFReader {
    private:
        string filename;
        void loadFromDisk() {
            cout << "Loading PDF from disk: " << filename << endl;
        }
    public:
        RealPDFReader(string fname) : filename(fname) {
            loadFromDisk();
        }
        void displayPDF() override {
            cout << "Displaying PDF: " << filename << endl;
        }
};

class ProxyPDFReader : public IPDFReader {
    private:
        string filename;
        RealPDFReader* realPDFReader;
        User* user;
    public:
        ProxyPDFReader(string fname, User* u) : filename(fname), realPDFReader(nullptr), user(u) {}
        void displayPDF() override {
            if (user->hasPremium()) {
                cout<<"Congrats, Access Granted: Welcome " << user->getUsername() << "!" << endl;
                if (realPDFReader == nullptr) {
                    realPDFReader = new RealPDFReader(filename);
                }
                realPDFReader->displayPDF();
            } else {
                cout << "ohh!! Access Denied " <<user->getUsername() <<", Upgrade to premium to view this PDF." << endl;
            }
        }
        ~ProxyPDFReader() {
            delete realPDFReader;
        }
};


int main() {
    cout << "Proxy Design Pattern - PDF Reader Using Protection Proxy" << endl;

    User* rachiel = new User("Rachiel");
    User* joe = new User("Joe", true);
    User* ross = new User("Ross");
    User* monica = new User("Monica", true);
    User* chandler = new User("Chandler");
    User* phoebe = new User("Phoebe", true);

    IPDFReader* pdfForRachiel = new ProxyPDFReader("premium_content.pdf", rachiel);
    IPDFReader* pdfForJoe = new ProxyPDFReader("premium_content.pdf", joe);
    IPDFReader* pdfForRoss = new ProxyPDFReader("premium_content.pdf", ross);
    IPDFReader* pdfForMonica = new ProxyPDFReader("premium_content.pdf", monica);
    IPDFReader* pdfForChandler = new ProxyPDFReader("premium_content.pdf", chandler);
    IPDFReader* pdfForPhoebe = new ProxyPDFReader("premium_content.pdf", phoebe);

    pdfForRachiel->displayPDF();
    cout<<"-----------------------------"<<endl;
    pdfForJoe->displayPDF();
    cout<<"-----------------------------"<<endl;
    pdfForRoss->displayPDF();
    cout<<"-----------------------------"<<endl;
    pdfForMonica->displayPDF();
    cout<<"-----------------------------"<<endl;
    pdfForChandler->displayPDF();
    cout<<"-----------------------------"<<endl;
    pdfForPhoebe->displayPDF();

    return 0;
}