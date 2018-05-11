### 1. auto
ignore the top layer const, keep the bottom layer const
```
int a = 0;
const int x = a; 
const int& y = x; 
auto x1 = x; // int
auto y1 = y; // int
auto a1 = &a; // int *
auto x2 = &x; // int const *
auto y2 = &y; // int const *

const auto &x3 = 18; // int const
// auto &x3 = 18; can not bind literals for non-constant references
```
> ref: p62

### 2. decltype
```
const int ci = 0, &cj = ci;
decltype(ci) x = 0; // const int
decltype(cj) y = x; // const int &
```
> ref: p64

### 3. long long
```
cout << sizeof(bool) << endl; // 1
cout << sizeof(char) << endl; // 1
cout << sizeof(int) << endl; // 4
cout << sizeof(long) << endl; // 4
cout << sizeof(long long) << endl; // 8

cout << sizeof(float) << endl; // 4
cout << sizeof(double) << endl; // 8
```
> ref: p30

### 4. constexpr
```
// preprocessor
#define X 42

// constants
const int X = 42;

// constexpr-function
constexpr int X() { return 42; }
```
> ref: p59

### 5. range-based for loop
```
// use refenrence to change value
string s = "hello world";
for (auto& c : s) {
  c += 'A' - 'a';
}
cout << s << endl;
```
> ref: p82

### 6. std begin & end
```
// begin point to the first element, end point to after the last element
int array[] = { 18, 7, 22, 10, 690, 2 };
int* p = begin(array);
while (p != end(array)) {
  if (*p > 20) {
    cout << *p << endl;
  }
  p++;
}
```
> ref: p106

### 7. auto for 2d array
```
int array[3][2] = { {18, 7}, {22, 10}, {690, 2} };
for (auto p = array; p < array + 3; p++) { // p is int (*)[2]
  for (auto q = *p; q < *p + 2; q++) { // q is int *
    cout << *q << " ";  
  }
  cout << endl;
}
```
> ref: p115

### 8. initializer_list

```
void test(string s, initializer_list<int> ist);

int main()
{
	test("test", { 18, 7, 22, 10, 690, 2 });
    return 0;
}

void test(string s, initializer_list<int> ist) {
	cout << s << endl;
	for (auto i = ist.begin(); i != ist.end(); i++) {
		cout << *i << " ";
	}
} 
```
> ref: p197


### 9. cbegin, cend
If not use write operation, use cbegin & cend instead if beign & end
> ref: p299

### 10. bind
C++ adapter
```
#include <functional>
using namespace std::placeholders;

auto check6 = bind(checkSize, _1, 6); // _1 is a placeholder
bool b = check6("orange"); // b is true

bool checkSize(const string & s, int sz) {
  return s.length() >= sz;
} 
```

### 11. shared_ptr
// 
```
auto s = make_shared<string>("hello");
```
