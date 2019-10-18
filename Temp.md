### 1. const int*, const int * const, int const
> ref: https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const

### 2. regular expression
> ref: https://blog.csdn.net/zengxiantao1994/article/details/77816972

### 3. stack vs heap
* code segment
* data segment(数据段): 存放程序中已初始化且不为0的全局/静态变量的一块内存区域
* bss segment(BSS段): 存放程序中未初始化的全局/静态变量的一块内存区域
* stack: local variable, method parameter
* heap：new, malloc, calloc, realloc
> ref: https://blog.csdn.net/billcyj/article/details/78783741

### 4. process vs thread
* 一个程序至少有一个进程,一个进程至少有一个线程
* 一个进程崩溃后，在保护模式下不会对其它进程产生影响; 一个线程死掉就等于整个进程死掉
* 地址空间为每个进程所私有的; 线程有自己的堆栈和局部变量，但线程之间没有单独的地址空间(共享进程的地址空间)
* 进程切换时，耗费资源较大
* 总线程数 <= CPU数量: 并行运行; 总线程数 > CPU数量: 并发运行
> ref: https://blog.csdn.net/mxsgoden/article/details/8821936

### 5. 加密算法
对称密钥: DES、RC4,RC5, AES
非对称密钥: RSA
哈希算法: MD5, SHA-1，SHA-2(SHA-256，SHA-512)

### 6. 调用约定
* stdcall: 1) 参数从右向左压入堆栈; 2) 函数自身修改堆栈; 3) 函数名自动加前导的下划线，后面紧跟一个@符号，其后紧跟着参数的尺寸
* cdecl: 1) 参数从右向左压入堆栈; 2) 调用者负责清理堆栈
* fastcall: 1) 函数的第一个和第二个DWORD参数（或者尺寸更小的）通过ecx和edx传递，其他参数通过从右向左的顺序压栈; 2) 被调用函数清理堆栈; 3) 函数名修改规则同stdcall
* thiscall: 1) 参数从右向左入栈; 2) 如果参数个数确定，this指针通过ecx传递给被调用者; 如果参数个数不确定，this指针在所有参数压栈后被压入堆栈; 3) 对参数个数不定的，调用者清理堆栈，否则函数自己清理堆栈。
> ref: https://blog.csdn.net/u010852680/article/details/78316633
