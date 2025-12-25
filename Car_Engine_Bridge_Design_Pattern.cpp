#include<iostream>
using namespace std;

//Implementer Hierarchy(LLP)
class Engine {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual ~Engine() {}
};

class PetrolEngine : public Engine {
    public:
        void start() override {
            cout << "Petrol engine started." << endl;
        }
        void stop() override {
            cout << "Petrol engine stopped." << endl;
        }
};

class DieselEngine : public Engine {
    public:
        void start() override {
            cout << "Diesel engine started." << endl;
        }
        void stop() override {
            cout << "Diesel engine stopped." << endl;
        }
};

class ElectricEngine : public Engine {
    public:
        void start() override {
            cout << "Electric engine started." << endl;
        }
        void stop() override {
            cout << "Electric engine stopped." << endl;
        }
};

//Abstraction Hierarchy(HLP)
class Car {
    protected:
        Engine* engine;
    public:
        Car(Engine* eng) : engine(eng) {}
        virtual void startCar() {
            engine->start();
        }
        virtual void stopCar() {
            engine->stop();
        }
        virtual ~Car() {
            delete engine;
        }
};

class SUV : public Car {
    public:
        SUV(Engine* eng) : Car(eng) {}
        void startCar() override {
            cout << "Starting SUV..." << endl;
            engine->start();
        }
        void stopCar() override {
            cout << "Stopping SUV..." << endl;
            engine->stop();
        }
};

class Sedan : public Car {
    public:
        Sedan(Engine* eng) : Car(eng) {}
        void startCar() override {
            cout << "Starting Sedan..." << endl;
            engine->start();
        }
        void stopCar() override {
            cout << "Stopping Sedan..." << endl;
            engine->stop();
        }
};

class Hatchback : public Car {
    public:
        Hatchback(Engine* eng) : Car(eng) {}
        void startCar() override {
            cout << "Starting Hatchback..." << endl;
            engine->start();
        }
        void stopCar() override {
            cout << "Stopping Hatchback..." << endl;
            engine->stop();
        }
};

enum EngineType {
    PETROL,
    DIESEL,
    ELECTRIC
};
//Singleton Factory for Engine Creation
class EngineFactory {
    private:
        static EngineFactory* instance;
        EngineFactory() {}
    public:
        static EngineFactory* getInstance() {
            if (instance == nullptr) {
                instance = new EngineFactory();
            }
            return instance;
        }
        Engine* createEngine(EngineType type) {
            switch (type) {
                case PETROL:
                    return new PetrolEngine();
                case DIESEL:
                    return new DieselEngine();
                case ELECTRIC:
                    return new ElectricEngine();
                default:
                    return nullptr;
            }
        }
};
EngineFactory* EngineFactory::instance = nullptr;

int main() {
    cout << "Bridge Design Pattern - Car Engine and Transmission System" << endl;
    EngineFactory* factory = EngineFactory::getInstance();
    Car* mySUV = new SUV(factory->createEngine(DIESEL));
    Car* mySedan = new Sedan(factory->createEngine(PETROL));
    Car* myHatchback = new Hatchback(factory->createEngine(ELECTRIC));
    Car* mySUV2 = new SUV(factory->createEngine(PETROL));
    Car* mySedan2 = new Sedan(factory->createEngine(ELECTRIC));
    cout<<"--- Starting Cars ---"<<endl;
    mySUV->startCar();
    cout<<"---------------------"<<endl;
    mySedan->startCar();
    cout<<"---------------------"<<endl;
    myHatchback->startCar();
    cout<<"---------------------"<<endl;
    mySUV2->startCar();
    cout<<"---------------------"<<endl;
    mySedan2->startCar();
    cout<<"--- Stopping Cars ---"<<endl;
    mySUV->stopCar();
    cout<<"---------------------"<<endl;
    mySedan->stopCar();
    cout<<"---------------------"<<endl;
    myHatchback->stopCar();
    cout<<"---------------------"<<endl;
    mySUV2->stopCar();
    cout<<"---------------------"<<endl;
    mySedan2->stopCar();
    delete mySUV;
    delete mySedan;
    delete myHatchback;
    delete mySUV2;
    delete mySedan2;
    return 0;
}
