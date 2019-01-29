#include <iostream>

using namespace std;

class Singleton {
public:
	static Singleton* Instance();
	static Singleton* Instance(int a);
	static Singleton* Instance(int a, int b);
	
protected:
	Singleton();
	
private:
	static Singleton* _instance;
	
};

Singleton::Singleton()
{
	cout << "Singleton construct" << endl;
}

Singleton* Singleton::_instance = nullptr;

Singleton* Singleton::Instance() {
	if (_instance == nullptr) {
		cout << "Instance return void 1"<< endl;
		_instance = new Singleton;
	}
	cout << "Instance return void 2"<< endl;
	return _instance;
}

Singleton* Singleton::Instance(int a) {
	if (_instance == nullptr) {
		cout << "Instance return int a 1"<< endl;
		_instance = new Singleton;
	}
	cout << "Instance return int a 2"<< endl;
	return _instance;
}

Singleton* Singleton::Instance(int a, int b) {
	if (_instance == nullptr) {
		cout << "Instance return int a int b 1"<< endl;
		_instance = new Singleton;
	}
	cout << "Instance return int a int b 2"<< endl;
	return _instance;
}

int main()
{
	int a = 1;
	int b = 2;
	//static Singleton* ssina = Singleton::Instance();
	static Singleton* ssinb = Singleton::Instance(a);
	static Singleton* ssinc = Singleton::Instance(a, b);
}
