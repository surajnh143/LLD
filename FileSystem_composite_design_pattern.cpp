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
    IFileSystem* rootFolder = new Folder("Root");
    IFileSystem* documents = new Folder("Documents");
    IFileSystem* picture_dir = new Folder("Pictures");
    IFileSystem* work_dir = new Folder("Work");
    IFileSystem* personal_dir = new Folder("Personal");
    rootFolder->add(documents);
    rootFolder->add(personal_dir);
    rootFolder->add(new File("file1.txt", 100));
    personal_dir->add(new File("file2.txt", 200));
    personal_dir->add(picture_dir);
    documents->add(new File("summary.pdf", 400));
    documents->add(work_dir);
    picture_dir->add(new File("image1.png", 500));
    picture_dir->add(new File("image2.png", 700));
    work_dir->add(new File("notes.txt", 150));
    work_dir->add(new File("report.docx", 300));
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

    delete documents;
    delete picture_dir;
    delete work_dir;
    delete personal_dir;
    delete rootFolder;

    return 0;
}
