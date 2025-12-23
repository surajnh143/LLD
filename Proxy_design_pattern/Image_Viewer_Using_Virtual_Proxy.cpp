#include<iostream>
using namespace std;

class IImage {
    public:
        virtual void display() = 0;
        virtual ~IImage() {}
};

class RealImage : public IImage {
    private:
        string filename;
        void loadFromDisk() {
            cout << "Loading image from disk: " << filename << endl;
        }
    public:
        RealImage(string fname) : filename(fname) {
            loadFromDisk();
        }
        void display() override {
            cout << "Displaying image: " << filename << endl;
        }
};

class ProxyImage : public IImage {
    private:
        string filename;
        RealImage* realImage;
    public:
        ProxyImage(string fname) : filename(fname), realImage(nullptr) {}
        void display() override {
            if (realImage == nullptr) {
                realImage = new RealImage(filename);
            }
            realImage->display();
        }
        ~ProxyImage() {
            delete realImage;
        }
};

class ImageViewer {
    private:
        IImage* image;
    public:
        ImageViewer(IImage* img) : image(img) {}
        void showImage() {
            image->display();
        }
        ~ImageViewer() {
            delete image;
        }
};


int main() {
    cout << "Proxy Design Pattern - Image Viewer Using Virtual Proxy" << endl;
    IImage* img = new ProxyImage("test_image.jpg");
    cout << "ImageViewer created." << endl;
    ImageViewer viewer(img);
    cout << "First call to showImage():" << endl;
    viewer.showImage();  // Image will be loaded from disk here
    cout << "Second call to showImage():" << endl;
    viewer.showImage();  // Image will be displayed without loading from disk
    return 0;
}