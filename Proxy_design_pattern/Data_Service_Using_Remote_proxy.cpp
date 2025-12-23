#include<iostream>  
using namespace std;

class IDataService {
    public:
        virtual void fetchData() = 0;
        virtual ~IDataService() {}
};

class RemoteDataService : public IDataService {
    public:
        void fetchData() override {
            cout << "Fetching data from remote server..." << endl;
        }
};

class DataServiceProxy : public IDataService {
    private:
        RemoteDataService* remoteService;
        bool isConnected;
    public:
        DataServiceProxy() : remoteService(nullptr), isConnected(false) {}
        
        void connectToServer() {
            cout << "Connecting to remote server..." << endl;
            isConnected = true;
            remoteService = new RemoteDataService();
        }
        
        void fetchData() override {
            if (!isConnected) {
                connectToServer();
            }
            remoteService->fetchData();
        }
        
        ~DataServiceProxy() {
            delete remoteService;
        }
};

int main() {
    cout << "Proxy Design Pattern - Data Service Using Remote Proxy" << endl <<endl;

    cout<< "Client: Requesting data through proxy..." << endl;
    IDataService* dataService = new DataServiceProxy();
    cout<< "\nFirst data fetch:" << endl;
    dataService->fetchData();
    cout<< "\nSecond data fetch:" << endl;
    dataService->fetchData();
    delete dataService;
    return 0;
}