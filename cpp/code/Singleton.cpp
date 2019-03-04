#include <iostream>

using namespace std;

class Singleton {
public:
	static Singleton* Instance();
<<<<<<< HEAD
	
protected:
	Singleton();

=======
	static Singleton* Instance(int a);
	static Singleton* Instance(int a, int b);
	
protected:
	Singleton();
	
>>>>>>> 69c92132bbc30dec2546cb6ed240c3d1c97e6ba4
private:
	static Singleton* _instance;
	
};

<<<<<<< HEAD
Singleton* Singleton::_instance = 0;

Singleton* Singleton::Instance() {
	if (_instance == 0) {
		_instance = new Singleton;
	}
=======
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
>>>>>>> 69c92132bbc30dec2546cb6ed240c3d1c97e6ba4
	return _instance;
}

int main()
<<<<<<< HEAD
{}
=======
{
	int a = 1;
	int b = 2;
	//static Singleton* ssina = Singleton::Instance();
	static Singleton* ssinb = Singleton::Instance(a);
	static Singleton* ssinc = Singleton::Instance(a, b);
}
>>>>>>> 69c92132bbc30dec2546cb6ed240c3d1c97e6ba4
