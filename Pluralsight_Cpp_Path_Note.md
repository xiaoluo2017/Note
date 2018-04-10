## Learn How to Program with C++

1. const of member function  
never change value of member variables  
ref: 7.6 2:15

## C++ Fundamentals including C++ 17

### default constructor
```
// only in header
Person() = default;
```
ref: 5.6 2:08

### namespace
never use namespace in header file  
ref: 5.11 1:21

### enum class
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
ref: 5.14 1:59

### pragma once
```
// include in header
#pragma once
```
ref: 5.17 1:17
