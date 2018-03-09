### some interview QA
* What is the point of an interface?
Separate the API (what to do) from the implementation (how to do it). Make your code flexible. 
It is Java's answer to multiple inheritance. It gives you some of the features of MI, without the nasty complications.
Ref: https://softwareengineering.stackexchange.com/questions/131332/what-is-the-point-of-an-interface

* Memory leak
```
#include <iostream>
using namespace std;
int main()
{ 
   int *a = new int(123);
   cout << *a << endl;
   // We should write "delete a;" here
   a = new int(456);
   cout << *a << endl;
   delete a;
   return 0;
}
```
Ref: https://zh.wikipedia.org/wiki/%E5%86%85%E5%AD%98%E6%B3%84%E6%BC%8F#%E7%B0%A1%E4%BE%8B
  
### Reference
* must be initialized in declarations
* Once associated with a variable, the reference is always loyal to it, close to the const pointer
```
// eg.Rodants play the same role as pr
int & Rodents = rats;
int * const pr = &rats;
```
