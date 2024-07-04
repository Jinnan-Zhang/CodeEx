#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class tfile : public std::ofstream {
   public:
    stringstream data;
    string fileName;

   public:
    tfile(string fileName) : fileName(fileName) { ; }
    template <typename T>
    tfile &operator<<(const T a) override {
        data << a;
        return *this;
    }
};
int test(ofstream &f) {
    f << "a";
    return 0;
}
int testf() {
    tfile t0("a.txt");
    test(t0);
    cout << t0.data.str() << "\n";
    // t0.close();
    return 0;
}
int main() {
    testf();
    return 0;
}