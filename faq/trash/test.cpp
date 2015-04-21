#include <iostream>

using namespace std;

struct Foo {
  Foo() { pi = new int(123); count = new size_t(1); }

  Foo(int* pi_in) {
    pi = pi_in;
    count = new size_t(1);
  }

  Foo(const Foo& other) {
    pi = other.pi;
    count = other.count;
    (*count)++;
  }

  void print() const {
    cout << "data: " << *pi << endl;
    cout << "count: " << *count << endl;
    cout << endl;
  }

  ~Foo() {
    cout << "dtor: " << *count << endl;
    (*count)--;
    if ((*count) == 0) {
      delete pi;
      pi = 0;
      delete count;
      count = 0;
    }
  }
      
  int* pi;
  size_t* count;
};

void test(const Foo& obj) 
{
  //delete obj.pi;
  obj.pi = 0;
}

int main()
{
  Foo f1;
  cout << "f1: " << endl;
  f1.print();

  //int* p_in = new int(456);
  //Foo f3(p_in);

  Foo f2(f1);
  cout << "f2: " << endl;
  f2.print();

  cout << "f1 again: " << endl;
  f1.print();
}
