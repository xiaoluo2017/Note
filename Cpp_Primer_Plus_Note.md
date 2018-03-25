### Interview QA
* What is the point of an interface?<br>
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

### 9.2
auto: 存于堆栈，无链接性<br>
register：存于寄存器，无链接性<br>
static：静态，代码块无链接性/在函数外内部链接性（全局变量，不使用static在函数外部，外部链接性）<br>
extern：引用外部变量<br>
volatile：不进行缓存到寄存器的优化，eg.将指针指向某个硬件位置时使用<br>
mutable：声明为const，其成员也可被修改<br>
const：const修饰全局变量，链接性转为内部<br>
