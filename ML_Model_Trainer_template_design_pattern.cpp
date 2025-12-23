#include<iostream>
using namespace std;

class MLModelTrainer {
    public:
        void trainModel(string path) {
            load(path);
            preprocessData();
            selectModel();
            train();
            evaluate();
            deploy();
        }

    protected:
        virtual void load(string path) {
            cout << "[Common Method] Loading data from " << path <<"..."<< endl;
        }
        virtual void preprocessData() {
            cout << "[Common Method] Preprocessing data..." << endl;
        }

        virtual void selectModel() {
            cout << "[Common Method] Selecting model..." << endl;
        }

        virtual void train() {
            cout << "[Common Method] Training model..." << endl;
        }

        virtual void evaluate() {
            cout << "[Common Method] Evaluating model..." << endl;
        }

        virtual void deploy() {
            cout << "[Common Method] Deploying model..." << endl;
        }
};

class NeuralNetTrainer : public MLModelTrainer {
    protected:
        void deploy() override {
            cout << "[NeuralNetTrainer] Deploying Neural Network model..." << endl;
        }

        void selectModel() override {
            cout << "[NeuralNetTrainer] Selecting Neural Network model..." << endl;
        }

        void train() override {
            cout << "[NeuralNetTrainer] Training Neural Network model..." << endl;
        }

        void evaluate() override {
            cout << "[NeuralNetTrainer] Evaluating Neural Network model..." << endl;
        }
};

class DecisionTreeTrainer : public MLModelTrainer {
    protected:
        void evaluate() override {
            cout << "[DecisionTreeTrainer] Evaluating Decision Tree model..." << endl;
        }

        void selectModel() override {
            cout << "[DecisionTreeTrainer] Selecting Decision Tree model..." << endl;
        }

        void train() override {
            cout << "[DecisionTreeTrainer] Training Decision Tree model..." << endl;
        }

        void deploy() override {
            cout << "[DecisionTreeTrainer] Deploying Decision Tree model..." << endl;
        }
};

class SVMTrainer : public MLModelTrainer {
    protected:
        void selectModel() override {
            cout << "[SVMTrainer] Selecting SVM model..." << endl;
        }

        void train() override {
            cout << "[SVMTrainer] Training SVM model..." << endl;
        }

        void deploy() override {
            cout << "[SVMTrainer] Deploying SVM model..." << endl;
        }
};

class RandomForestTrainer : public MLModelTrainer {
    protected:
        void selectModel() override {
            cout << "[RandomForestTrainer] Selecting Random Forest model..." << endl;
        }

        void train() override {
            cout << "[RandomForestTrainer] Training Random Forest model..." << endl;
        }

        void evaluate() override {
            cout << "[RandomForestTrainer] Evaluating Random Forest model..." << endl;
        }

        void deploy() override {
            cout << "[RandomForestTrainer] Deploying Random Forest model..." << endl;
        }
};

int main() {
    cout << "This is a template for ML Model Trainer using Template Design Pattern." << endl;

    MLModelTrainer* trainer;
    trainer = new NeuralNetTrainer();
    trainer->trainModel("data/neural_net_dataset.csv");
    cout << "----------------------------------------" << endl;
    trainer = new DecisionTreeTrainer();
    trainer->trainModel("data/decision_tree_dataset.csv");
    cout << "----------------------------------------" << endl;
    trainer = new SVMTrainer();
    trainer->trainModel("data/svm_dataset.csv");
    cout << "----------------------------------------" << endl;
    trainer = new RandomForestTrainer();
    trainer->trainModel("data/random_forest_dataset.csv");
    cout << "----------------------------------------" << endl;

    return 0;
}
