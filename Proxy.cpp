#include <iostream>
using namespace std;

class Image {
    string fileName;
    void loadFromDisk() {
        cout << "Loading from disk " << fileName << endl;
    }
public:
    Image(string name) : fileName(name) {
        loadFromDisk();
    }
    void display() {
        cout << "Displaying image";
    }
};
class ImageProxy {
    string fileName;
    Image* realImage = nullptr;
    bool hasAccess;
public:
    ImageProxy(string name, bool access) : fileName(name), hasAccess(access){}
    ~ImageProxy()
    {
        delete realImage;
    }
    void display() {
        if (!hasAccess) {
            cout << "Access denied to image: " << fileName << endl;
            return;
        }
        if (realImage == nullptr) {
            cout << "Lazy loading image...\n";
            realImage = new Image(fileName);
        }
        realImage->display();   
    }
};
int main()
{
    ImageProxy img1("photo1.jpg", true);  // User has access
    ImageProxy img2("secret_photo.jpg", false);  // User denied

    cout << "Trying to display img1:\n";
    img1.display();  // Loads and displays

    cout << "\nTrying to display img1 again:\n";
    img1.display();  // Just displays, no reload

    cout << "\nTrying to display img2:\n";
    img2.display();  // Access denied
}

