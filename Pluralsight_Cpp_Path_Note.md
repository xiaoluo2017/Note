## Learn How to Program with C++

### 1. const of member function  
never change value of member variables  
> ref: 7.6 2:15

## C++ Fundamentals including C++ 17

### 1. default constructor
```
// only in header
Person() = default;
```
> ref: 5.6 2:08

### 2. namespace
never use namespace in header file  
> ref: 5.11 1:21

### 3. enum class
variable can repeat
```
enum class FileError
{
	notfound,
	ok
};

enum class NetworkError
{
	disconnected,
	ok
};
```
> ref: 5.14 1:59

### 4. pragma once
```
// include in header
#pragma once
```
> ref: 5.17 1:17

### 5. warning level
right-click on the project -> Properties -> C/C++ -> General -> Warning Level  
> ref: 8.5 2:29

### 6. null pointer
nullptr
> ref: 10.2 4:33

### 7. const
```
// can not change i through cri, but i is changeable
int i = 3;
int const & cri = i;
cri = 6; // not feasible
i = 6; // feasible
```
```
// can not assign a reference to a const variable
int const ci = 3;
int & ncri = ci; // not feasible
```
```
// can not past a const to a non-const reference function
int DoubleInt(int& x) { // int& x need to be const
  return x * 2;
}
int DoubleTen = DoubleInt(10); // not feasible 
```
```
// const object can not call a non-const member function
int GetNumber() {return arbitrarynumber;} // in header, function need to be const

Person const Kate("Kate", "Gregory", 234);
int KateNumber = cKate.GetNumber(); // not feasible
```
> ref: 10.6 0:00

```
// const reference: can't use the const to change the value
int const & ri = 7;
ri = 5; // not feasible
```

```
// const pointer: can't change it to point somewhere else
int * const cpi = &i;
cpi = &something; // not feasible
```

```
// pointer to a const: can't change the value of target
int const * cpi = &i;
*cpi = 2; // not feasible
```

```
// can't change it to point somewhere else or use it to change the value of target
int const * const crazy;
```
> ref: 10.7 0:09
