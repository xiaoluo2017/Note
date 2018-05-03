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
