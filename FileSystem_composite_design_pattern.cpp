#include<iostream>
using namespace std;

class IFileSystem {
    private:
        IFileSystem* parent;
    public:
        IFileSystem* getParent() {
            return parent;
        }
        void setParent(IFileSystem* p) {
            parent = p;
        }
        virtual void ls() = 0;
        virtual void openAll() = 0;
        virtual int getSize() = 0;
        virtual void getName() = 0; 
        virtual void add(IFileSystem* fs) = 0;
        virtual IFileSystem* cd(string folderName) {
            return nullptr; 
        }   
        virtual ~IFileSystem() {}
};
class File : public IFileSystem {
    private:
        string name;
        int size;
    public:
        File(string n, int s) : name(n), size(s) {}
        void add(IFileSystem* fs) override {
            fs->setParent(this);
        }
        void ls() override {
            cout << "File: " << name << " (Size: " << size << " bytes)" << endl;
        }
        void openAll() override {
            cout << "Opening file: " << name << endl;
        }
        int getSize() override {
            return size;
        }
        void getName() override {
            cout << "File name: " << name << endl;
        }
};

class Folder : public IFileSystem {
    private:
        string name;
        vector<IFileSystem*> children;
    public:
        Folder(string n) : name(n) {}
        void add(IFileSystem* fs) override{
            cout<<"Added to folder " << name << ": ";
            fs->setParent(this);
            children.push_back(fs);
        }
        IFileSystem* cd(string folderName) override {
            if(folderName == "..") {
                cout << "Changed directory to parent folder." << endl;
                return getParent();
            }
            for (auto child : children) {
                Folder* folder = dynamic_cast<Folder*>(child);
                if (folder && folder->name == folderName) {
                    cout << "Changed directory to: " << folderName << endl;
                    return folder;
                }
            }
            cout << "Folder " << folderName << " not found in " << name << endl;
            return nullptr;
        }
        void ls() override {
            cout << "Folder: " << name << endl;
            for (auto child : children) {
                child->ls();
            }
        }
        void openAll() override {
            cout << "Opening folder: " << name << endl;
            for (auto child : children) {
                child->openAll();
            }
        }
        int getSize() override {
            int totalSize = 0;
            for (auto child : children) {
                totalSize += child->getSize();
            }
            return totalSize;
        }
        void getName() override {
            cout << "Folder name: " << name << endl;
        }
};

int main() {
    cout << "File System Composite Design Pattern Example" << endl;
    IFileSystem* file1 = new File("file1.txt", 100);
    IFileSystem* file2 = new File("file2.txt", 200);
    IFileSystem* folder1 = new Folder("Documents");
    IFileSystem* folder2 = new Folder("Pictures");
    IFileSystem* rootFolder = new Folder("Root");
    IFileSystem* file3 = new File("image1.png", 500);
    IFileSystem* file4 = new File("image2.png", 700);
    IFileSystem* file5 = new File("notes.txt", 150);
    IFileSystem* folder3 = new Folder("Work");
    IFileSystem* file6 = new File("report.docx", 300);
    IFileSystem* file7 = new File("summary.pdf", 400);
    IFileSystem* folder4 = new Folder("Personal");
    rootFolder->add(folder1);
    rootFolder->add(folder4);
    rootFolder->add(file1);
    folder4->add(file2);
    folder4->add(folder2);
    folder1->add(file7);
    folder1->add(folder3);
    folder2->add(file3);
    folder2->add(file4);
    folder3->add(file5);
    folder3->add(file6);
    rootFolder->ls();
    cout << "----------------------------------------" << endl;
    rootFolder->openAll();
    cout << "----------------------------------------" << endl; 
    rootFolder->getSize();
    cout << "----------------------------------------" << endl;
    IFileSystem* currentFolder = rootFolder->cd("Documents");
    if (currentFolder) {
        currentFolder->ls();
        cout << "----------------------------------------" << endl;
        currentFolder->getSize();
        cout << "----------------------------------------" << endl;
        currentFolder->openAll();
        cout << "----------------------------------------" << endl;
        currentFolder = currentFolder->cd("Work");
        if(currentFolder) {
            currentFolder->ls();
            cout << "----------------------------------------" << endl;
            currentFolder->getSize();
            cout << "----------------------------------------" << endl;
            currentFolder->openAll();
            cout << "----------------------------------------" << endl;
            currentFolder = currentFolder->cd("..");
            if(currentFolder) {
                currentFolder = currentFolder->cd("..");
                if(currentFolder) {
                    currentFolder = currentFolder->cd("Personal");
                    if(currentFolder) {
                        currentFolder->ls();
                        cout << "----------------------------------------" << endl;
                        currentFolder->getSize();
                        cout << "----------------------------------------" << endl;
                        currentFolder->openAll();
                        cout << "----------------------------------------" << endl;
                        currentFolder = currentFolder->cd("Pictures");
                        if(currentFolder) {
                            currentFolder->ls();
                            cout << "----------------------------------------" << endl;
                            currentFolder->getSize();
                            cout << "----------------------------------------" << endl;
                            currentFolder->openAll();
                            cout << "----------------------------------------" << endl;
                            currentFolder = currentFolder->cd("..");
                            if(currentFolder)
                                currentFolder = currentFolder->cd("..");
                        }
                }
            }
        }
    }
    }
    if(currentFolder) {
        cout<<"Final Folder: ";
        currentFolder->getName();
        cout<<endl;
    }

    delete file1;
    delete file2;
    delete file3;
    delete file4;
    delete file5;
    delete file6;
    delete file7;
    delete folder1;
    delete folder2;
    delete folder3;
    delete folder4;
    delete rootFolder;

    return 0;
}
