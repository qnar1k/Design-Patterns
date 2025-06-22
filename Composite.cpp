#include <iostream>
#include <vector>
using namespace std;

class FileSystemItem {
public:
	virtual void display(int indent = 0) = 0;
	virtual ~FileSystemItem() = default;
};

class File : public FileSystemItem {
	string fileName;
public:
	File(string name) :fileName(name) {}
	void display(int indent = 0) override {
		cout << string(indent, ' ') << "- File: " << fileName << endl;
	}
};

class Folder : public FileSystemItem {
	string folderName;
	vector<FileSystemItem*> children;
public:
	Folder(string name) : folderName(name) {}
	void display(int indent = 0) override {
		cout << string(indent, ' ') << "+ Folder: " << folderName << endl;
		for (auto child : children) {
			child->display(indent + 4);
		}
	}
	void add(FileSystemItem* item) {
		children.push_back(item);
	}
	~Folder() {
		for (auto child : children) {
			delete child;
		}
	}
};

int main()
{
	Folder* fold1 = new Folder("Subjects");
	fold1->add(new File("Languages.txt"));
	fold1->add(new File("Literature.txt"));
	Folder* fold2 = new Folder("Science");
	fold2->add(new File("Maths.txt"));
	fold2->add(new File("Physics.txt"));
	fold2->add(new File("Chemistry.txt"));
	fold1->add(fold2);

	fold1->display();
	delete fold1;
	return 0;
}
