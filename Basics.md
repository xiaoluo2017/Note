# Basics

- [C](#c)
  * [1. const int*, const int * const, int const](#1-const-int---const-int---const--int-const)
  * [2. 函数参数入栈顺序](#2---------)
  * [3. sizeof struct/sizeof class](#3-sizeof-struct-sizeof-class)
  * [4. 一维 二维](#4------)
- [General](#general)
  * [1. regular expression](#1-regular-expression)
  * [2. 虚拟地址 分段 分页](#2-----------)
  * [3. 用户态 vs 内核态](#3-----vs----)
- [TCP UDP HTTP](#tcp-udp-http)
  * [1. OSI](#1-osi)
  * [2. TCP UDP](#2-tcp-udp)
  * [3. TCP的流量控制 拥塞控制](#3-tcp----------)
  * [4. HTTP](#4-http)
  * [5. HTTP GET POST PUT DELETE](#5-http-get-post-put-delete)
  * [6. Cookie vs Session](#6-cookie-vs-session)
  * [7. https加密 SSL/TLS协议](#7-https---ssl-tls--)
- [Thread Process Lock](#thread-process-lock)
  * [1. process vs thread](#1-process-vs-thread)
  * [2. 进程/线程状态](#2--------)
  * [3. 进程通信](#3-----)
  * [4. 线程同步](#4-----)
  * [5. 父子进程](#5-----)
  * [6. 锁](#6--)
  * [7. 死锁](#7---)
- [C++](#c--)
  * [1. Main concepts in OOP](#1-main-concepts-in-oop)
  * [2. C++ 编译过程](#2-c-------)
  * [3. 静态链接 动态链接](#3----------)
  * [4. stack vs heap](#4-stack-vs-heap)
  * [5. Forward declaration](#5-forward-declaration)
  * [6. new vs malloc](#6-new-vs-malloc)
  * [7. constructor/destructor throw exception](#7-constructor-destructor-throw-exception)
  * [8. constructor/destructor call virtual function](#8-constructor-destructor-call-virtual-function)
  * [9. polymorphism vtable](#9-polymorphism-vtable)
  * [10. volatile](#10-volatile)
  * [11. static](#11-static)
  * [12. 初始化列表](#12------)
  * [13. copy constructor](#13-copy-constructor)
  * [14. Copy constructor, Move constructor, Move assignment](#14-copy-constructor--move-constructor--move-assignment)
  * [15. Type conversion](#15-type-conversion)
  * [16. STL](#16-stl)
  * [17. 左值 右值](#17------)
  * [18. typeid decltype](#18-typeid-decltype)
  * [19. C++ equivalent of reflection](#19-c---equivalent-of-reflection)
  * [20. C++ vs Java](#20-c---vs-java)
- [Java](#java)
  * [1. Java GC](#1-java-gc)
  * [2. Abstract class vs interface in Java](#2-abstract-class-vs-interface-in-java)
  * [3. Java 引用传递 值传递](#3-java---------)
  * [4. Object class in Java](#4-object-class-in-java)
  * [5. == vs .equals() in Java](#5----vs-equals---in-java)
  * [6. synchronized in Java](#6-synchronized-in-java)
- [Database](#database)
  * [1. B vs B+](#1-b-vs-b-)
  * [2. ACID](#2-acid)
- [Algorithm](#algorithm)
  * [1. 位运算](#1----)

## C
### 1. const int*, const int * const, int const
> ref: https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const

### 2. 函数参数入栈顺序
* 参数入栈时顺序从右向左入栈
* 入栈前先把参数列表里的表达式算一遍得到表达式的结果, 最后再把这些运算结果统一入栈
* ++运算符直接从变量a所在的内存地址中取值

```
void f(int a, int b, int c, int d) {
    cout << a << endl; 
    cout << b << endl; 
    cout << c << endl; 
    cout << d << endl; 
}

int main(){
    int i = 0;
    f(i++, ++i, i, i++); // 2 3 3 0
}
```
> ref: https://blog.csdn.net/xidiancoder/article/details/49160317

### 3. sizeof struct/sizeof class
* 对字符串进行sizeof操作的时候, 会把字符串的结束符"\0"计算进去的; 进行strlen操作求字符串的长度的时候, 不计算\0
```
char str[] = "Hello";
printf("%d\n",sizeof(str)); // 6
printf("%d\n",strlen(str)); // 5
```
* 每个结构体成员的起始地址为该成员大小的整数倍, 即int型成员的起始地址只能为0、4、8等
> ref: https://blog.csdn.net/RadianceBlau/article/details/60867307

* 遵循结构体的对齐原则
* 类的大小与普通数据成员有关, 与成员函数和静态成员无关: 即普通成员函数, 静态成员函数, 静态数据成员, 静态常量数据成员均对类的大小无影响
* 虚函数对类的大小有影响, 是因为虚函数表指针带来的影响
    * 虚函数的类或实例最后的sizeof是实际的数据成员的sizeof加8(需要字节对齐)
    * 多继承: 每个基类都有自己的虚表; 子类的成员函数被放到了第一个基类的表中
* 虚继承对类的大小有影响, 是因为虚基表指针带来的影响
    * 子类有指向虚基类的指针
* 空类的大小为1
    * 当子类继承空类后, 子类如果有自己的数据成员, 则空基类的一个字节并不会加到子类中去
    * 一个类包含一个空类对象数据成员, 空类的1字节是会被计算进去(需要字节对齐)
> ref: https://blog.csdn.net/fengxinlinux/article/details/72836199

### 4. 一维 二维
```
int a[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 一个一维int数组的数组名实际上是一个int* const类型
int b[8];
int* c = new int[8];

cout << sizeof(a) << endl; // 32
cout << sizeof(b) << endl; // 32
cout << sizeof(c) << endl; // 8
cout << sizeof(*c) << endl; // 4
```

```
// 一个二维int数组的数组名实际上是一个int (*const p)[n];
int a[2][2]={1, 2, 3}; // true
int a[2][2]={{1}, {2}};
int a[2][2]={{1}, 2, 3};
int a[3][2]={{1}, 2, 3, {4}};
int a[3][2]={{1}, 2, {4}}; // false

int a[][2]={1, 2, 3}; // true
int a[][2]={{1}, {2}}; 
int a[][2]={{1}, 2, 3};
int a[][2]={{1}, 2, 3, {4}};
int a[][2]={{1}, 2, {4}}; // false

int a[2][]={{1,2},{3,4}} // false
// *(a[2] + 1) == *(*(a + 2) + 1) == a[2][1]
```

```
int a[][2]={{1}, 2, 3, {4}};
// 相当于int ** a

cout << &a[0][0] << endl;
cout << *a << endl; // address of a[0][0], 步长1
cout << a << endl; // address of a[0][0], 步长2
cout << &a << endl; // address of a[0][0], 步长6

cout << *a + 1 << endl; // address of a[0][1]
cout << &a[0][1] << endl;

cout << a + 1 << endl; // address of a[0][2]
cout << &a[0][2] << endl;

cout << &a + 1 << endl; // address of after a[2][1]
cout << &a[2][1] << endl; 

int* p = (int*)(&a + 1);
cout << *(p - 2) << endl; // 4
```

```
int* p[3]; // 指针数组

cout << p << endl;
cout << p + 1 << endl; // 步长: 1 size: 8

cout << &p << endl;
cout << &p + 1 << endl; // 步长: 3 size: 8

cout << *p << endl;
cout << *p + 1 << endl; // 步长: 1 size: 4

cout << **p << endl;
cout << **p + 1 << endl; // value

int (*p)[3]; // 数组指针 行指针
cout << p << endl;
cout << p + 1 << endl; // 步长: 3 size: 4

cout << *p << endl;
cout << *p + 1 << endl; // 步长: 1 size: 4

cout << **p << endl;
cout << **p + 1 << endl; // value
```
* 数组名做参数会退化为指针, 除了sizeof

## General
### 1. regular expression
> ref: https://blog.csdn.net/zengxiantao1994/article/details/77816972

### 2. 虚拟地址 分段 分页
* 程序运行是需要从内存中分配出足够多的连续的内存, 然后把整个程序装载进去
    * 地址空间不隔离
    * 程序运行时候的地址不确定
    * 内存使用率低下
* 虚拟地址空间: 虚拟的, 可以任意的大
* 物理地址空间: 真实存在的, 是有限的
* 分页 & 分段为了利用和管理好计算机的资源: 内存
* 分段: 虚拟地址空间映射到了物理地址空间(映射的是一片连续的物理内存), 程序操作的是虚拟地址
    * 隔离性: 误操作了不在所属程序地址空间的地址, 因为其是虚拟的, 而虚拟化的操作是在操作系统的掌控中的, 操作系统有能力判断, 这个虚拟地址是有问题的, 然后阻止后续的操作
    * 程序无需关注物理地址是多少, 只要虚拟地址没有改变, 那么, 程序就不会操作地址不当
* 分页: 一段虚拟地址空间组成的某一页映射到一段物理地址空间组成的某一页
    * 程序的换入换出就可以以页为单位了, 可以换出CPU还用不到的那些程序代码、数据
> ref: https://www.zhihu.com/question/50796850

### 3. 用户态 vs 内核态
* 最重要的差别就在于特权级的不同, 运行在用户态下的程序不能直接访问操作系统内核数据结构和程序
    * 用户态: 最低特权级
    * 内核态: 最高特权级
* 执行一个程序, 大部分时间是运行在用户态下的, 在其需要操作系统帮助完成某些它没有权力和能力完成的工作时就会切换到内核态. 最关键性的权力必须由高特权级的程序来执行，这样才可以做到集中管理，减少有限资源的访问和使用冲突, 限制不同的程序之间的访问能力, 防止他们获取别的程序的内存数据, 或者获取外围设备的数据, 并发送到网络

* 用户态切换到内核态
    * 系统调用: 主动方式 eg. fork(): 执行创建新进程的系统调用
    * 异常: CPU在执行运行在用户态下的程序时，发生异常, 则进程会切换到处理此异常的内核相关程序中
    * 外围设备的中断: 向CPU发出相应的中断信号, 执行与中断信号对应的处理程序 eg. 硬盘读写操作完成，系统会切换到硬盘读写的中断处理程序中执行后续操作
> ref: https://blog.csdn.net/youngyoungla/article/details/53106671

## TCP UDP HTTP
### 1. OSI

* 应用层协议
    * DNS: 主要用UDP, 但是当请求字节过长超过512字节时用TCP协议, 将其分割成多个片段传输
    * 基于TCP的协议: HTTP(需要可靠传输), FTP(文件传输协议), Telnet(远程登陆), SMTP(简单邮件传送协议), POP3(接收邮件)
    * 基于UDP的协议: SNMP(简单网络管理协议), OICQ(聊天)
* 传输层协议: TCP, UDP
* 网络层协议: IP, ICMP, RIP
* 数据链路层协议: ARP, RARP
> ref: https://blog.csdn.net/yingxunren/article/details/4726376

### 2. TCP UDP
* TCP vs UDP

* TCP 三次握手 四次挥手

* TCP建立连接／断开连接状态
    * Client: CLOSED->SYN_SENT->ESTABLISHED->FIN_WAIT_1->FIN_WAIT_2->TIME_WAIT->CLOSED
      * TIME_WAIT: 停留2MSL(Maximum Segment Lifetime, 报文最大生存时间)
    * Server: CLOSED->LISTEN->SYN_RCVD->ESTABLISHED->CLOSE_WAIT->LAST_ACK->CLOSED
> ref: https://blog.csdn.net/Mary19920410/article/details/63711522

* TCP网络编程中connect()、listen()和accept()
> ref: https://blog.csdn.net/lianghe_work/article/details/46443691

### 3. TCP的流量控制 拥塞控制
* 流量控制: 滑动窗口

* 拥塞控制: 慢开始、拥塞避免、快重传、快恢复
    * 增加缓存空间到一定程度时, 只会加重拥塞, 而不是减轻拥塞, 因为当数据包经过长期时间排队完成转发时, 他们可能早已经超时, 从而引起源端超时重发; 增加链路宽带及提高处理能力也不能解决拥塞问题
    * 缓存空间不足导致的丢包更多的是拥塞"症状"而非原因
    * 拥塞只是一个动态问题, 我们没有办法用一个静态方案去解决, 从这个意义上说, 拥塞时不可避免的; 拥塞是一个全局控制的过程, 他不像点对点的流控机制, 是一个局部的控制

* 慢开始: cwnd *= 2
    * 发送方维持着一个拥塞窗口cwnd(congestion window)
    * cwnd初始化为1个最大报文段(MSS)大小
    * cwnd的值就随着网络往返时间(Round trip time，RTT)呈指数级增长(cwnd *= 2)
    * 如果宽带为W, 那么经过RTT*log2W时间就可以占满带宽
* 拥塞避免: cwnd += 1
    * 慢启动门限（ssthresh）
    * 当cwnd < ssthresh时, 使用慢开始算法
    * 当cwnd > ssthresh时, 改用拥塞避免算法(cwnd += 1)
    * 当cwnd = ssthresh时, 慢开始与拥塞避免算法任意
* 快重传
    * 发送方只要一连收到三个重复确认就应当立即重传对方尚未收到的报文段, 而不必继续等待设置重传计时器时间到期。
* 快恢复
    * 当发送方连续收到三个重复确认时, 把ssthresh门限减半(ssthresh = cwnd / 2), 并直接进入拥塞避免算法(cwnd = ssthresh)
* 发生超时重传: 网络拥塞的主要依据是它重传了一个报文段
    * 把ssthresh降低为cwnd值的一半(ssthresh = cwnd / 2);
    * 把cwnd重新设置为1(cwnd = 1);
    * 重新进入慢启动过程;
> ref: http://www.voidcn.com/article/p-vrdkquop-ms.html

### 4. HTTP
* TCP vs HTTP
> ref: https://www.quora.com/What-is-the-difference-between-HTTP-protocol-and-TCP-protocol

* HTTP请求报文
    * 开始行: 要做些什么
      * 方法: eg. get, post
      * URL: <协议>://<主机>:<端口>/<路径>
        * <协议> eg. http https
        * <主机> eg. www.google.com
        * <端口> http默认端口号为80, 通常可省略
        * <路径> 可省略, 省略后即为主页(home page)
      * 版本: http 1.0 1.1 2.0
    * 首部行: 请求的属性, 冒号分隔的键值对 
      * Content-Length: 标记着body的长度
      * Cookie: 用于在客户端存储少量信息，通常用于实现会话（session）功能
    * 实体主行(body): 发送给Web服务器的数据

* HTTP响应报文
    * 开始行(状态行): 出现了什么情况
      * 版本: http 1.0 1.1 2.0
      * 状态码: 1xx, 2xx, 3xx, 4xx, 5xx
      * 短语: 解释状态码 
        * eg. 200: OK, 404: Not Found
    * 首部行: 请求的属性, 冒号分隔的键值对 
      * Content-Length: 标记着body的长度
      * Date: 表示报文发送的时间, 即生成响应的日期和时间
      * Last-Modified: 表示报文的最后修改时间
    * 实体主行(body): 返回给客户端的数据

> ref: https://blog.csdn.net/dangzhangjing97/article/details/80957898

### 5. HTTP GET POST PUT DELETE
* URL全称是资源描述符
* GET和POST本质上就是TCP链接, 并无差别; 但是由于HTTP的规定和浏览器/服务器的限制, 导致他们在应用过程中体现出一些不同 
* GET从服务器上获取资源，POST向服务器发送数据;
* GET为幂等, post为非幂等
* GET参数包含在URL中, POST通过request body传递参数
    * get传输数据是通过URL请求, 以field(字段) = value的形式, 置于URL后, 并用"?"连接, 多个请求数据间用"&"连接, eg. http://127.0.0.1/Test/login.action?name=admin&password=admin, 这个过程用户是可见的;
    * post传输数据通过Http的post机制, 将字段与对应值封存在请求实体(request body)中发送给服务器, 这个过程对用户是不可见的;
* GET请求在URL中传送的参数是有长度限制的(约2k), 而POST没有
* GET比POST更不安全, 因为参数直接暴露在URL上, 所以不能用来传递敏感信息
https://www.oschina.net/news/77354/http-get-post-different

### 6. Cookie vs Session
* cookie: 浏览器访问服务器后, 服务器传给浏览器的一段数据, 浏览器需要保存这段数据, 此后每次浏览器访问该服务器, 都必须带上这段数据
   * 识别用户身份(Session ID)
   * 记录历史(eg. 购物车)
* HTTP协议是无状态的协议, 服务端需要记录用户的状态时, 需要用某种机制来识具体的用户(Session)
    * Requests are separate and must contain enough information on their own to fulfill the request. Request is executed independently, without any knowledge of the requests that were executed before it, which means once the transaction ends, the connection between the browser and the server is also lost.
    * Session是在服务端保存的一个数据结构, 用来跟踪用户的状态, 这个数据可以保存在数据库/Cache中;
* 每次HTTP请求的时候, 客户端都会发送相应的Cookie信息(Session Id)/使用URL重写(如果客户端的浏览器禁用了Cookie)到服务端, cookie来实现Session跟踪
    * Cookie是客户端保存用户信息的一种机制, 用来记录用户的一些信息, 也是实现Session的一种方式
    
### 7. https加密 SSL/TLS协议
* 客户端向服务端发送请求, 服务端返回数字证书
    * 数字证书: CA(在浏览器中)用它的私钥对消息摘要(RSA公钥和个人信息通过Hash算法生成)加密, 形成签名, 并把原始信息和数据签名进行合并, 即所谓的'数字证书', 用于解决中间人问题;
* 客户端用自己的CA公钥去解密证书, 如果证书有问题会提示风险
* 如果证书没问题, 客户端会生成一个对称加密的秘钥, 用刚刚解密的服务器端的RSA公钥进行加密, 发送给服务器端
* 服务器端收到以后会用自己的RSA私钥对客户端发来的对称秘钥进行解密
* 之后双方就拿着这个对称加密秘钥(RSA太慢)来进行正常的通信

* A向B发送信息的整个签名和加密的过程如下：
    * A先用自己的私钥(PRI_A)对信息(一般是信息的摘要)进行签名
    * A接着使用B的公钥(PUB_B)对信息内容和签名信息进行加密
    * A对信息签名的作用是确认这个信息是A发出的，不是别人发出的
> ref: https://www.zhihu.com/question/27669212

## Thread Process Lock
### 1. process vs thread
* A process can be thought of as an instance of a program in execution, a thread is a paticular execution path of a process
* 地址空间为每个进程所私有的; 线程有自己的堆栈和局部变量, 但线程共享进程的地址空间(线程之间没有单独的地址空间)
    * 速度: 线程产生的速度快, 线程间的通讯快/切换快等, 因为他们在同一个地址空间内; process need to use inter-process communications(eg. pipes, files, socket, etc.)
    * 资源利用率: 线程的资源利用率比较好也是因为他们在同一个地址空间内
    * 同步问题: 线程使用公共变量/内存时需要使用同步机制还是因为他们在同一个地址空间内
* 一个程序至少有一个进程, 一个进程至少有一个线程
* 一个进程崩溃后, 在保护模式下不会对其它进程产生影响; 一个线程死掉就等于整个进程死掉
* 线程执行开销小, 但不利于资源管理和保护；而进程正相反, 进程切换时, 耗费资源较大
* 总线程数 <= CPU数量: 并行运行; 总线程数 > CPU数量: 并发运行 
> ref: https://blog.csdn.net/mxsgoden/article/details/8821936

### 2. 进程/线程状态
* 新生状态: new关键字创建后，进入到新生状态
* 就绪状态
    * 调用start后进入就绪状态
* 运行状态(调用该线程对象的run()方法) 
    * CPU调度到本线程后, 本线程开始执行, 进入到运行状态
* 阻塞状态(sleep()/wait()/join()/yield())
    * 运行中遇到join, yield, sleep造成阻塞, 进入阻塞状态, 阻塞完成后, 又回到就绪状态(不是运行状态)
    * sleep()/yield()不会释放锁资源
* 死亡状态: 线程正常执行完，或者遇到异常终止后，进入死亡状态

> ref: https://blog.csdn.net/huakai_sun/article/details/78287931
> ref: https://blog.csdn.net/qicheng777/article/details/77427157

### 3. 进程通信
* linux进程间通信方式:
    * 管道(pipe): 父子进程间使用
    * 有名管道(named pipe)
    * 信号量(semophore): 一种锁机制, 控制多个线程对共享资源的访问, 主要作为进程间以及同一个进程内不同线程之间的同步手段
    * 消息队列(message queue): 由系统调用函数来实现消息发送和接收之间的同步, 不需要考虑同步问题; 信息的复制需要额外消耗CPU的时间, 不适宜于信息量大或操作频繁的场合
    * 信号(signal)
    * 共享内存(shared memory): 最快的进程间通信方式, 信息量大; 必须由各进程利用其他同步工具解决
    * 套接字(socket)
> ref: https://www.cnblogs.com/lincappu/p/8536431.html    

* C++ windows进程间通信方式:
    * 全局变量, Message消息机制, CEvent对象
> ref: https://www.cnblogs.com/langqi250/archive/2012/11/06/2756329.html

全局变量(volatile), 消息(message)
* 线程间的同步方式
* 直接制约关系: 一个线程的处理结果, 为另一个线程的输入, 因此线程之间直接制约着, 这种关系可以称之为同步关系
* 间接制约关系: 两个线程需要访问同一资源, 该资源在同一时刻只能被一个线程访问, 这种关系称之为线程间对资源的互斥访问

### 4. 线程同步
* Java: synchronized, volatile, Lock(eg. ReentrantLock)
* C++:
    * std::thread: callable; eg. std::thread thread_object(callable) 
    * mutex: lock() unlock() try_lock()
      * lock_guard: lock_guard在构造时会自动锁定互斥量, 而在退出作用域后进行析构时就会自动解锁
      * unique_lock: 提供lock, unlock, try_lock; 对象是可以进行交换的
    * condition_variable: wait() notify_one() notify_all()
    * atomic: 不需要再定义互斥量了, 使用更简便 eg. std::atomic<int> value;
    * call_once/once_flag eg. std::once_flag flag;
	
```
// lock_guard
std::mutex g_lock;
lock_guard<std::mutex> locker(g_lock);
```

```
// call_once/once_flag
void do_once()
{
    std::call_once(flag,[]{
        // do sth.
    });
}
```
> ref: https://blog.csdn.net/qq_37233607/article/details/80159873

### 5. 父子进程
* 子进程从父进程继承了: 
    * 当前工作目录, 根目录
    * 环境, 堆栈, 共享内存
    * 打开文件的描述符
    * 信号掩码
    * nice值 (由nice函数设定，数值越小，优先级越高)>   
* 子进程与父进程不同的: 
    * 地址空间
    * 进程号PID, 各自的父进程号
    * 子进程不继承父进程的进程正文, 数据和其它锁定内存
    * 不继承异步输入和输出
> ref: https://blog.csdn.net/carl_wu_/article/details/77976020 https://blog.csdn.net/koudaidai/article/details/8014782

### 6. 锁
* mutex(互斥锁): 
    * 同一时间, 锁只有一把, 如果线程A加锁正在访问资源, 这时B尝试加锁, 就会阻塞;
    * 不加锁也可以访问数据 eg. 线程A加锁了正在访问资源, 这时B不加锁也可以直接访问数据
* 读写锁: 写独占, 读共享; 写锁优先级高; 读写锁特别适用于读的次数远大于写的情况
    * 当读写锁是读模式加锁时, 其它线程以读模式加锁都会成功, 但是线程以写模式加锁会阻塞;
    * 当读写锁是写模式加锁时, 直到解锁前，其它线程加锁都会被阻塞;
    * 当读写锁是读模式加锁时, 其它线程既有试图以写模式加锁的线程，也有试图以读模式加锁的线程, 这时读写锁会阻塞在写模式加锁请求之后的读模式加锁请求, 优先满足写模式
* condition_variable(条件变量)
* semophore(信号量): 
    * 互斥锁在同一时刻只能有一个线程访问加锁的数据, 但是信号量可以允许多个线程来访问
    * 互斥量的加锁和解锁必须由同一线程分别对应使用, 信号量可以由一个线程释放, 另一个线程得到
    * 基于上面的特点, 互斥锁一般用于控制一段临界代码，当然信号量也可以做到; 但是如果释放和获取不在一个函数中甚至不在一个线程中时就必须使用信号量了,
* 信号量 vs 互斥锁
    * 信号量: 对一个进程加锁, 可以不断加锁, 设置一个标记a == 0, a++; 解锁的时候a--, 当a == 0时可以继续进行; 应用场景: 生产者-消费者模型; 使用场景: 操作系统分配多个打印任务时
    * 互斥锁: 当一个进程把持资源时, 其他进程不能访问此资源, 此特性代表了此资源一次只能被一个进程利用, 使用场景: 文本的写入

### 7. 死锁
* 死锁的四个必要条件:
    * 互斥条件: 一个资源每次只能被一个进程使用
    * 请求和保持条件: 一个进程因请求资源而阻塞时, 对已获得的资源保持不放
    * 不可剥夺条件: 进程已获得的资源, 在末使用完之前, 不能强行剥夺
    * 循环等待条件: 若干进程之间形成一种头尾相接的循环等待资源关系
* 死锁预防(破坏死锁的四个条件中的一个或几个):   
    * 资源一次性分配(破坏请求和保持条件)
    * 可剥夺资源: 即当某进程新的资源未满足时, 释放已占有的资源(破坏不可剥夺条件)
    * 资源有序分配法: 系统给每类资源赋予一个编号, 每一个进程按编号递增的顺序请求资源, 释放则相反(破坏循环等待条件)
* 避免死锁(银行家算法)
    * 当进程首次申请资源时, 要测试该进程对资源的最大需求量, 如果系统现存的资源可以满足它的最大需求量则按当前的申请量分配资源, 否则就推迟分配
    * 当进程在执行中继续申请资源时, 先测试该进程已占用的资源数与本次申请的资源数之和是否超过了该进程对资源的最大需求量, 若超过则拒绝分配资源; 若没有超过则再测试系统现存的资源能否满足该进程尚需的最大资源量, 若能满足则按当前的申请量分配资源, 否则也要推迟分配
* 检测死锁
    * 每个进程、每个资源制定唯一编号, 设定一张资源分配表, 记录各进程与占用资源之间的关系, 出现环路即存在死锁
* 解除死锁
    * 剥夺资源: 从其它进程剥夺足够数量的资源给死锁进程, 以解除死锁状态;
    * 撤消进程: 可以直接撤消死锁进程或撤消代价最小的进程, 直至有足够的资源可用, 死锁状态消除为止; 代价是指优先级, 运行代价, 进程的重要性和价值等
    
> ref: https://blog.csdn.net/yyf_it/article/details/52412071
> ref: http://c.biancheng.net/cpp/html/2606.html

## C++
### 1. Main concepts in OOP
* encapsulation: hide data
    * eg. You can feed the cat, but you can’t directly change how hungry the cat is
* abstraction: hide implementation
    * eg. A coffee machine. It does a lot of stuff, but all you have to do is put in coffee and press a button.
* inheritance: inherit to re-use, extend and modify the behaviour
    * eg. Child class reuses all fields and methods of the parent class(common part) and can implement its own(unique part).
* Polymorphism: an object exhibits different behavior in different situation
    * eg. Triangles, circles & rectangles, the language takes care of evaluating the right implementation of the common method
    
> ref: https://stackoverflow.com/questions/23130282/best-way-to-explain-oop-principles

> ref: https://www.freecodecamp.org/news/object-oriented-programming-concepts-21bb035f7260/

* requirements for language to be object-oriented
    * a language that supports only encapsulation(objects) is not object-oriented, but it is modular
    * a language that supports just encapsulation(objects) & message-passing(polymorphism) is not object-oriented, but it is object-based
    * a language that supports encapsulation(objects), message-passing(polymorphism), and inheritance(abstraction), is object-oriented
    
> ref: https://stackoverflow.com/questions/402984/main-concepts-in-oop

### 2. C++ 编译过程
* .h, .cpp
* 预处理: 条件编译(#ifdef, #ifndef, #else, #elif, #endif), 头文件包含(#include), 宏替换的处理, 生成.i
* 编译: 将预处理后的文件转换成汇编语言, 代码优化, 生成.s
    * eg. inline
* 汇编: 汇编变为目标代码(机器代码), 生成.o/.obj
* 链接: 连接目标代码/其他目标代码/库文件, 生成可执行程序, 生成.exe

### 3. 静态链接 动态链接
* 静态链接和动态链接两者最大的区别就在于链接的时机不一样
    * 静态链接在形成可执行程序(.exe)前
    * 动态链接在程序执行时
* 静态链接: 每个源文件(.cpp)独立编译形成目标文件(.obj), 需要将这些源文件产生的目标文件进行链接, 从而形成可执行文件(.exe)
    * 浪费空间, 每个可执行程序中对所有需要的目标文件都要有一份副本, 同一个目标文件都在内存存在多个副本
    * 更新困难, 每当库函数的代码修改了, 这个时候就需要重新进行编译链接形成可执行程序
    * 在可执行程序中已经具备了所有执行程序所需要的任何东西, 在执行的时候运行速度快
* 动态链接: 把程序按照模块拆分成各个相对独立部分, 在程序运行时才将它们链接在一起形成一个完整的程序
    * 每个程序都依赖同一个库, 多个程序在执行时共享同一份副本(将内存中已经存在的.obj映射到虚拟地址空间中)
    * 更新方便, 只需要替换原来的目标文件, 而无需将所有的程序再重新链接一遍
    * 每次执行程序都需要进行链接, 性能会有一定损失(大约在5%以下)

> ref: https://blog.csdn.net/kang___xi/article/details/80210717

### 4. stack vs heap
* code segment
* 全局区(c里面才划分为data segment/bss segment)
    * data segment(数据段): 存放程序中已初始化且不为0的全局/静态变量的一块内存区域
    * bss segment(BSS段): 存放程序中未初始化的全局/静态变量的一块内存区域
* stack: local variable, method parameter
* heap：new, malloc, calloc, realloc
* 常量区
   * 有个简单的方法判断是常量还是常变量, 就是判断常量的使用者是否可以合法的取地址
      * 0.01是个常量而不是常变量, &0.01非法;
      * const int a = 0; 是个常变量, &a合法;
> ref: https://blog.csdn.net/billcyj/article/details/78783741
> ref: https://bbs.csdn.net/topics/390510503

### 5. Forward declaration
* 声明一个类而不定义它
* 在声明之后, 定义之前, 被声明类类是一个不完全类型(incompete type), 即已知该类是一个类型, 但不知道包含哪些成员
* incompete type: 不能定义该类型的对象(eg. A a; return new A();), 只能用于定义指向该类型的指针及引用, 或者用于声明(而不是定义)使用该类型作为形参类型或返回类型的函数

```
class B;

class A 
{ 
public:
    void sf(B* b); // ok, 'B b' is also ok
    B* gf(); // ok, 'B' is also ok
private: 
    B* _pb; // ok
    // B _b // invalid use of incomplete type
};

class B {};

void A::sf(B* b)
{
    _pb = b;
}

B* A::gf()
{
    return new B(); // must after class B
}
```

### 6. new vs malloc
* new分配的内存要用delete销毁, malloc要用free来销毁
* new不仅分配一段内存, 而且会调用构造函数, 但是malloc则不会; delete销毁的时候会调用对象的析构函数, 而free则不会
* new返回的是指定对象的指针, 而malloc返回的是void*, 因此malloc的返回值一般都需要进行类型转化;
* new分配内存按照数据类型进行分配, malloc分配内存按照大小分配;
* new是一个操作符可以重载, malloc是一个库函数;
    * 预编译指令(带#): eg. #pragma #define; 
    * 操作符: eg. new, delete, sizeof, +, -, *
    * 函数: eg. malloc, 参数为字节数, 返回一个void*指针; 
* new和new[]的区别, new[]一次分配所有内存, 多次调用构造函数, 分别搭配使用delete和delete[], 同理, delete[]多次调用析构函数, 销毁数组中的每个对象; 而malloc则只能sizeof(int) * n;
* new如果分配失败了会抛出bad_alloc的异常, 而malloc失败了会返回NULL; 因此对于new, 正确的姿势是采用try...catch语法, 而malloc则应该判断指针的返回值, 为了兼容很多c程序员的习惯, C++也可以采用new nothrow的方法禁止抛出异常而返回NULL;

```
int *p;
p = (int*)malloc(sizeof(int) * 128);
```

### 7. polymorphism vtable
* polymorphism: 静态多态和动态多态
    * 静态多态通过overload & template实现, 在compile的时候确定;
    * 动态多态通过virtual function & inheritance实现, 执行dynamic binding, 在runtime确定
* 动态多态实现条件:
    * virtual function
    * 父类指针 & 指向子类的对象
* 动态多态实现过程
    * 父类指针在调用虚函数时, 会去查找该对象的vtable, 每个对象的首地址存放vptr, 指向该类的vtable, vtable直接从父类继承, 如果覆盖了其中的某个virtual function, 那么vtable的指针就会被替换
    * C++ non-virtual functions calls resolved at compile time with static binding, while virtual function calls are resolved at runtime with dynamic binding

### 8. header/source file
* C++源文件具有.cpp后缀
* C++源文件可以包含带有#include伪指令的其他文件, 称为头文件, 头文件具有.h后缀

### 9. volatile
* informs the complier the value of variable it is applied to can change from the outside(operating system, hardware, or another thread)
compiler will therefore reload the value each time from memory
* volatile variables are not optimized
> ref: https://www.nowcoder.com/questionTerminal/3f6c5287a9fa4d0baa162e44970a343d

### 10. extern static
* 全局变量
    * 可以从任何源文件访问它(尽管在其他源文件中, 通常需要extern声明)
    * 将变量声明为extern int global_var, 并将相应的初始化放在单个源文件中
* static全局变量
    * 只能在定义它的源文件中访问它
    * 除非需要从其他.cpp模块引用该对象, 否则请始终在文件中使用static
* extern: 生命周期: 程序结束后释放, 作用域: 外部(整个程序)
    * 源文件(.h)里的所有文件级变量对应的默认存储类是extern
* static: 生命周期: 程序结束后释放, 作用域: 内部(仅翻译单元, 一般指单个源文件)
    * 对于静态全局变量来说，针对某一源文件的以static声明的文件级变量与函数的作用域只限于文件内（只在文件内可见）
```
// A.cpp
int global_var;
static int local_var; // local_var is local to the module(.cpp) only

// B.cpp
// int global_var; // error: name conflict on 'global_var', linker doesn't know which global variable to use
extern int global_var; // use the global_var in A.cpp
```
> ref: https://stackoverflow.com/questions/1856599/when-to-use-static-keyword-before-global-variables

> ref: https://en.wikipedia.org/wiki/Static_variable

### 11. static
* static Variable
    * 在程序执行前系统就为之静态分配(也即在运行时中不再改变分配情况)存储空间的一类变量
    * 与程序有着相同生命周期
* 全局变量/函数 static全局变量/函数 方法中的static变量
    * 全局变量/函数的作用域是整个源程序, 当一个源程序由多个源文件(.cpp)组成时, 全局变量/函数在各个源文件(.cpp)中都有效; 全局变量在.h中用extern声明, .cpp中定义
    * static全局变量/函数限制了其作用域, 即只在定义该变量/函数的源文件(.cpp)内有效, 在同一源程序的其它源文件(.cpp)中不能使用; 对其它源文件(.cpp)隐藏, 利用这一特性可以在不同的文件中定义同名函数和同名变量
    * 方法中的static变量, 会在程序刚开始运行时就完成初始化, 也是唯一的一次初始化; 保持变量内容的持久
    * static变量可用const标识, 其值在编译时设定, 并且无法在运行时改变
* static成员变量
    * 不可在.h文件内, 类初始化列表进行初始化; .h类内声明,.cpp类外定义, 默认初始值为0
    * 调用方法: A::si; a.si;
* static成员方法
    * 只能使用static变量
    * 调用方法: A::sf(); a.sf();
```
// .h
class A
{
public:
    A();
    static void sf_setA(int i);
    static int sf_getA();
private:
    int mi;
    static int si;
};

// .cpp
int A::si;

A::A() //: si(7) // error: static data member can only be initialized at its definition
{
    si = 7;
}

void A::sf_setA(int i) 
{
    // mi = 18; // error: 如果要改变i的值, 需传入A类型对象
    si = i;
}

int A::sf_getA() 
{
    return si;
}

int main() {
    std::cout << A::sf_getA() << endl; // 0
    A a;
    std::cout << A::sf_getA() << endl; // 7
    A::sf_setA(18);
    std::cout << A::sf_getA() << endl; // 18
}
```
    
> ref: https://www.cnblogs.com/stoneJin/archive/2011/09/21/2183313.html

### 12. 初始化列表
* 必须在constructor initializer list里进行初始化的数据成员
    * const成员
    * 引用类型
    * 调用父类构造函数

```
class A
{
public:
    A() {cout<<"A"<<endl;}
    ~A() {cout<<"~A"<<endl;}
    
    A(const A& a) // 拷贝构造函数
    {
        cout << "Copy constructor for A" << endl ;
    }

    A& operator = (const A& a) // 赋值运算符
    {
        cout << "assignment for A" << endl ;
        return *this;
    }
};

class C
{
public:
    C() {cout<<"C"<<endl;}
    ~C() {cout<<"~C"<<endl;}
};

class D
{
public:
    D() {cout<<"D"<<endl;}
    ~D() {cout<<"~D"<<endl;}
    
    D(const D& d) // 拷贝构造函数
    {
        cout << "Copy constructor for D" << endl ;
    }

    D& operator = (const D& d) // 赋值运算符
    {
        cout << "assignment for D" << endl ;
        return *this;
    }
};

class B : public A
{
public:
    B(D& d, A& a, C& c) : _c(c),  _a(a)
    { 
        _d = d;
        cout<<"B"<<endl; 
    }
    ~B() { cout<<"~B"<<endl; }
private:
    D _d;
    A _a;
    C _c;
};

int main()
{
    A a;
    C c;
    D d;
    B b(d, a, c);
    return 0;
}
```
> ref: https://www.cnblogs.com/graphics/archive/2010/07/04/1770900.html

### 13. copy constructor
```
class A 
{
private:
    int i;
};

class B 
{
A *p;
public:

    /*
    B(const B& b){
        p = b.p;
    }*/ 
    // 编译器在生成default copy constructor的时候使用的bitwise copy语义，也就是只是简单的浅拷贝
    
    B(const B& b) // 拷贝构造函数
    {
        p = new A;
        *p = *(b.p);
	// p->i = b.p->i; // error, can't access i in this scope
        // memcpy(p, b.p, sizeof(A));
        cout << "Copy constructor for B" << endl ;
    }
    B(){
        cout << "B" << endl ;
        p = new A;
    }
    ~B(){
        cout << "~B" << endl ;
        delete p;
    }
};

void f(B b){
}

int main(){
   B b;
   f(b);
}
```

### 13. copy constructor, assignment
* copy constructor
    * 当类的对象按值返回时
    * 当类的对象通过值作为参数传递(传递给函数)时
    * 根据同一类的另一个对象构造一个对象时
    * 编译器生成临时对象时
```
A f(A a) // copy constructor
{
    return a; // copy constructor
}
```

```
Person p1("Anonymous"); // constructor
Person p2(p1); // copy constructor
Person p3 = p1; // copy constructor
p3 = p1; // Assignment
```

* Copy elision
    * An optimization implemented by most compilers to prevent extra (potentially expensive) copies in certain situations
```
// in C++ 17
A f() 
{
  return A(); // definitely performs copy elision
}

A f2()
{
    A a;
    return a; // maybe performs copy elision
}

void f3(A a) {}

int main()
{
    A a = f(); // Copy constructor isn't called
    f3(A()); // Copy constructor isn't called
}
```
> ref: https://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization

* explicit/implicit
    * C++ default copy constructor: Make a shallow copy. If the object has no pointers to dynamically allocated memory, a shallow copy is probably sufficient
    * Rule of three: If you need a copy constructor, you also need a destructor and operator=

* const &
    * const: Guarantee that the copy constructor doesn't change it
    * reference: A value parameter would require making a copy, which would invoke the copy constructor, becomes a non-terminating chain of calls

* assignment: 
    * Need to test to see if it is being initialized from itself
    * Need to clean up (eg, delete) an existing value
    * Need to return a reference to itself
> ref: http://www.fredosaurus.com/notes-cpp/oop-condestructors/copyconstructors.html

> ref: https://www.geeksforgeeks.org/copy-constructor-in-cpp/

### 14. Copy constructor, Move constructor, Move assignment
* 移动构造函数和移动赋值运算符重载函数不会隐式声明, 必须自己定义
* 如果用户自定义了拷贝构造函数或者移动构造函数, 那么默认的构造函数将不会隐式定义, 如果用户需要, 也需要显式的定义
* 移动构造函数不会覆盖隐式的拷贝构造函数
* 移动赋值运算符重载函数不会覆盖隐式的赋值运算符重载函数
* A move constructor is called:
    * when an object initializer is std::move(something)
    * when an object initializer is a temporary 当对象初始化程序是临时的
    * when returning a function-local class object by value 当按值返回函数局部类对象时
```
class A
{ 
public:
    A(){
        cout << "A" << endl ;
    }
    
    virtual ~A(){
        cout << "~A" << endl ;
    }
    
    A& operator=(const A& a) // 赋值运算符
    {
        cout << "assignment for A" << endl ;
        return *this;
    }
    
    A(const A& a) // 拷贝构造函数
    {
        cout << "Copy constructor for A" << endl ;
    }
    
    A(A&& a)
    {
        cout << "Move constructor for A" << endl;
    }
    
    A& operator=(A&& a) {
        cout << "Move assignment for A" << endl;
        return *this;
    }
};

/* A f(A a) // copy //
{  
    A a2(a); // copy // copy
    A a3 = a2; // copy // copy 
    return a3; // //
    // ~A for a, a2 // ~A for a, a2
}

int main(){
    A a; // A
    A a2 = f(f(a)); // 
    // ~A for a, a2
} */

A RetByValue() {
    A a;
    return a; // Might call move ctor, or no ctor.
}

void TakeByValue(A a){};

int main() {
    A a1;
    A a2 = a1; // copy ctor
    A a3 = std::move(a1); // move ctor
    TakeByValue(std::move(a2)); // Might call move ctor, or no ctor.
    A a4 = RetByValue(); // Might call move ctor, or no ctor.
    a1 = RetByValue(); // Calls move assignment, a::operator=(a&&)
}
```
> ref: https://stackoverflow.com/questions/13125632/when-does-move-constructor-get-called

### 15. Type conversion
```
#include <iostream>

using namespace std;

class Animal
{
public:
    virtual void f()
    {
        cout << "Animal" << endl;
    }
};
  
class Cat : public Animal
{
public:
    int mNum = 1;
    void f() override
    {
        cout << "Cat" << endl;
    }
};
  
int main()
{
    Animal* a = new Animal(); 
    cout << sizeof(*a) << endl; // 8
    a->f(); // Animal
    
    Cat* c = (Cat*)(a);
    cout << sizeof(*c) << endl; // 16
    cout << c->mNum << endl; // not 1
    c->f(); // Animal
    delete a;
  
    c = new Cat();
    cout << sizeof(*c) << endl; // 16
    a = c;
    cout << sizeof(*a) << endl; // 8
    a->f(); // Cat
    // cout << a->mNum << endl; // error
    cout << c->mNum << endl; // 1
    delete c;
    
    return 0;
}

```

### 16. STL
* stack, queue是基于deque来实现的
* priority-queue是基于heap来实现的
> ref: https://stackoverflow.com/questions/6292332/what-really-is-a-deque-in-stl

### 17. 左值 右值
* 左值: 可以取地址的, 有名字的
    * eg. int a = b + c; 
      * a是左值, 其有变量名为a, 通过&a可以获取该变量的地址
      * 表达式b + c, 函数int func()的返回值是右值, 在其被赋值给某一变量前, 我们不能通过变量名找到它, &(b+c)这样的操作则不会通过编译
* 右值: 不能取地址的, 没有名字的
    * 纯右值(prvalue，Pure Rvalue): 临时变量值, 不跟对象关联的字面量值
      * 临时变量: 非引用返回的函数返回值/表达式, eg. int func()的返回值, 表达式a + b
      * 不跟对象关联的字面量值: eg. true, 2, "C"
    * 将亡值(xvalue，eXpiring Value): 通常是将要被移动的对象
      * eg. T&&的函数返回值, std::move的返回值, 或者转换为T&&的类型转换函数的返回值
      
* lvalue
* rvalue
    * An xvalue: an "eXpiring" value
    * A prvalue: "pure" rvalue
* glvalue("generalized" lvalue): an lvalue or an xvalue.
```
int prvalue();
int& lvalue();
int&& xvalue();
```
> ref: https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues

### 18. typeid decltype
* dynamic_cast(C++ equivalent of instanceof)
```
if (NewType* v = dynamic_cast<NewType*>(old)) 
{
   // old was safely casted to NewType
   v->doSomething();
}
```
> ref: https://stackoverflow.com/questions/500493/c-equivalent-of-instanceof

* decltype(C++ equivalent of typeof)
```
auto i = 1; 
decltype(i) i2;
cout << typeid(i2).name() << endl; // i
```
> ref: https://www.geeksforgeeks.org/type-inference-in-c-auto-and-decltype/

* typeid: returns a type_info object, which is equality-comparable with other type_info objects
```
char c1;
char c2;
cout << typeid(c1).name() << endl; // c
cout << (typeid(c1) == typeid(c2)) << endl; // true
```
> ref: https://stackoverflow.com/questions/1986418/typeid-versus-typeof-in-c

### 19. C++ equivalent of reflection
```
class Animal {};

class Factory
{
public:
    Animal* getAnimalByName(std::string name)
    {
        std::map<std::string, Animal*>::iterator it = m.find(name);
        if (it == m.end()) { return NULL; }

        return it->second;
    }   

    void registClass(std::string name, Animal* a)
    {
        m[name] = a;
    }   

    static Factory& getInstance()
    {
        static Factory factory;
        return factory;
    }   

private:
    Factory() {};
    ~Factory() {};
    std::map<std::string, Animal*> m;
}; 

class Dog : public Animal
{
public:
    Dog(){ std::cout << "Dog()" << std::endl; }
    ~Dog(){ std::cout << "~Dog()" << std::endl; }
};

class Cat : public Animal
{
public:
    Cat(){ std::cout << "Cat()" << std::endl; }
    ~Cat(){ std::cout << "~Cat()" << std::endl; }
};

int main() 
{
    Factory::getInstance().registClass("Dog", new Dog());
    Factory::getInstance().registClass("Cat", new Cat());
    
    Dog* d = static_cast<Dog*>(Factory::getInstance().getAnimalByName("Dog"));
    Cat* c = static_cast<Cat*>(Factory::getInstance().getAnimalByName("Cat"));
    
    delete d;
    delete c;
}
```
> ref: https://www.cnblogs.com/xudong-bupt/p/6643721.html

### 20. C++ vs Java
* Only in C++:
    * pointer
    * reference(In Java, objects can only be passed by reference. In C ++ objects can be passed by value or by reference)
    * Memory management(In Java, no destructor, no delete, ~A() -> finalize())
    * operator overloading
    * struct, union & typedef(Compatible with C)
    * Preprocessing
    * default parameter
    * Multiple inheritance
    * inline
    * unsigned int
    * Scope operator::
    * virtual keyword(in Java, programmers don't have to decide for themselves whether to use dynamic binding, all non-static methods will definitely use dynamic binding)

* Only in Java:
    * Multithreading(a concurrency mechanism supported at the language level)
    * Garbage collection
    * '>>>' (unsigned right shift)

* Both have but different aspects:
    * Java is less efficient than C++
    * Java abstract class/interface vs C++ virtual class(include at least one pure virtual function)
    * Templates vs Generics
      * Java Generics
        * implementation: type erasure
        * just made things a bit prettier
        * static variables are shared across instances of MyClass, regardless of the different type parameters
      * C++ Templates
        * glorified macro set
        * create a new copy of the template code for each type
        * An instance of MyClass<Foo> will not share a static variable with MyClass<Bar>
    * C++ class need both declaration & definition; Java no class declaration, only class definition
> ref: https://www.zhihu.com/question/22928284

## Java
### 1. Java GC
* 根搜索算法
   * 通过一系列名为"GC Roots"的对象作为起始点, 寻找对应的引用节点
   * 找到这些引用节点后, 从这些节点开始向下继续寻找它们的引用节点
   * 搜索所走过的路径称为引用链, 当一个对象到GC Roots没有任何引用链相连时, 就证明此对象是不可用的
   * GC根对象包括：
     * 虚拟机栈中引用的对象(栈帧中的本地变量表);
     * 方法区中的常量引用的对象;
     * 方法区中的类静态属性引用的对象;
     * 本地方法栈中JNI（Native方法）的引用对象;
     * 活跃线程
* 分配区域
   * Young Generation: 新生代内存按照8:1:1的比例分为一个Eden区和两个Survivor(Survivor0,Survivor1)区
   * Old Generation: 内存比新生代也大很多(大概比例是1:2)
   * Permanent Generation(永久代)/MetaSpace(元空间): 用于存放静态文件（class类、方法）和常量等; 对永久代的回收主要回收两部分内容：废弃常量和无用的类。
* GC过程
    * 对象优先在Eden分配
    * 当新对象生成, Eden Space申请失败(因为空间不足等): 发起一次GC(Minor GC/Scavenge GC) eg.复制算法; 回收时将Eden区存活对象复制到Survivor0区，然后清空Eden区
    * Survivor0区也存放满了时: 将Eden区和Survivor0区存活对象复制到另一个Survivor1区, 然后清空Eden和这个Survivor0区, 此时Survivor0区是空的, 然后将Survivor0区和Survivor1区交换, 即保持Survivor1区为空, 如此往复
    * Survivor1区不足以存放Eden和Survivor0的存活对象时: 将存活对象直接存放到老年代
    * 老年代满了: 触发一次Major GC/Full GC(速度一般会比Minor GC慢10倍以上) eg.标记—清除算法/标记—整理算法, 新生代、老年代都进行回收
    * 长期存活的对象将进入老年代: 对象年龄达到15岁, 移动到老年代中(当对象在Survivor区躲过一次GC的话, 其对象年龄便会加1)
    * 大对象直接进入老年代, 大对象是指需要大量连续存储空间的对象 eg.大数组
* GC
    * Serial New收集器: 针对新生代的收集器, 采用的是复制算法
    * Parallel New(并行)收集器: 新生代采用复制算法, 老年代采用标记整理
    * Parallel Scavenge(并行)收集器: 针对新生代, 采用复制收集算法
    * Serial Old(串行)收集器: 新生代采用复制, 老年代采用标记整理
    * Parallel Old(并行): 收集器, 针对老年代, 标记整理
    * CMS收集器: 基于标记清理
    * G1收集器: 整体上是基于标记整理, 局部采用复制
> ref: https://www.jianshu.com/p/5261a62e4d29

### 2. Abstract class vs interface in Java
* abstract function(in Java) == pure virtual function(in C++)
* abstract class: has abstract function(in Java)
* virtual class: has pure virtual function(in C++)
* interface(in Java)
    * Functions can only be of type public abstract, member variables can only be of type public static final
    * Cannot contain static code blocks and static methods(abstract classes can have static code blocks and static methods)
    * A class can inherit only one abstract class, but a class can implement multiple interfaces(in Java)

> ref: https://www.cnblogs.com/dolphin0520/p/3811437.html

### 3. Java 引用传递 值传递
值传递: 原始类型
引用传递: 对象
immutable类型: 没有提供自身修改的函数, 每次操作都是新生成一个对象, 所以要特殊对待, 可以认为是传值 eg. String, Integer, Double. 
```
public class Main {
    public static void f(String str, char ch[], int i1, Integer i2, Obj o1, Obj o2){
        str="change";
        ch[0]='c';
        i1 = 18;
        i2 = 18;

        Obj o = new Obj();
        o.setA(18);
        o1 = o;

        o2.setA(18);
    }
    
    public static void main(String[] args) {
        String str = new String("str");
        char[] ch={'a', 'b', 'c'};
        Integer i1 = 0;
        int i2 = 0;
        Obj o1 = new Obj();
        Obj o2 = new Obj();
        f(str, ch, i1, i2, o1, o2);
        
        System.out.println(str); // str
        System.out.println(String.valueOf(ch)); // cbc
        System.out.println(i1); // 0
        System.out.println(i2); // 0
        System.out.println(o1.getA()); // 0
        System.out.println(o2.getA()); // 18
    }
	

}

class Obj {
    private int a = 0;

    public void setA(int a){
        this.a = a;
    }

    public int getA(){
        return a;
    }
}
```

### 4. Object class in Java
* toString(): print class name, then @, then unsigned hexadecimal representation of the hash code of the object
    * getClass().getName() + "@" + Integer.toHexString(hashCode());
* hashCode(): JVM generates a unique number, by converting the internal address of object to an integer using an algorithm
* equals(Object obj): It is necessary to override the hashCode() method whenever this method is overridden
* getClass(): widely used in Reflection
```
Object o = new String("str"); 
Class c = o.getClass();
System.out.println(c.getName()); // java.lang.String
```
* finalize(): called by the Garbage Collector on an object
* clone(): returns a new object that is exactly the same as this object

> ref: https://www.geeksforgeeks.org/object-class-in-java/

* wait(), notify() & notifyAll() must be used within a synchronized block only
* wait(): The calling thread give up the lock and go to sleep, until some other thread(on the same object) calls notify()
* notify()：Wake up one single thread that called wait() on the same object, not give up a lock on a resource
* notifyAll(): Wake up all threads that called wait() on the same object

> ref: https://www.geeksforgeeks.org/inter-thread-communication-java/

### 5. == vs .equals() in Java
* ==: It returns true only if both variables refer to the same object(object equality)
* .equals(): override to compare if "value" is the same(functional equality)
    * If a class does not override the equals method, then it defaults to the equals(Object o) method of the closest parent class that has overridden this method
    * If no parent classes have provided an override, then it defaults to the method from the ultimate parent class: Object. In the Object API this is the same as ==
* hashcode
    * 对象相等则hashCode一定相等, hashCode相等对象未必相等
    * String.hashCode() = str.charAt(0) * 31 ^ (n - 1) + str.charAt(1) * 31 ^ (n - 2) + ... + str.charAt(n - 1)

> ref: https://stackoverflow.com/questions/7520432/what-is-the-difference-between-and-equals-in-java
> ref: https://www.cnblogs.com/duanxz/p/3724275.html

### 6. synchronized in Java
* 修饰代码块
    * synchronized(this|object) {}: 对象锁
    * synchronized(类.class) {}: 类锁
* 修饰方法
    * 修饰非静态方法: 对象锁
    * 修饰静态方法: 类锁
* synchronized关键字不能继承, 对于父类中的synchronized修饰方法, 子类在覆盖该方法时, 默认情况下不是同步的, 必须显式使用synchronized关键字修饰才行
* 接口方法时不能使用synchronized关键字
* 构造方法不能使用synchronized关键字, 但可以使用synchronized代码块来进行同步

> ref: https://juejin.im/post/594a24defe88c2006aa01f1c

* 在java中每个类对应一把锁, 每个对象对应一把锁
    * 类锁实际上是通过对象锁实现的, 即类的Class对象锁, 每个类只有一个 Class 对象, 所以每个类只有一个类锁
    * 每个对象都会有一个monitor对象, 称为内置锁/对象锁
* 一个线程在访问一个对象的同步方法(对象锁)时, 另一个线程可以同时访问这个对象的非同步方法
* 一个线程在访问一个对象的同步方法(对象锁)时, 另一个线程不能同时访问这个同步方法/这个对象的另一个同步方法
* 如果其他方法是static, 它用的同步锁是当前类的字节码, 与非静态的方法不能同步, 因为非静态的方法用的是this
    * eg.线程1调用非静态的synchronized方法, 线程2调用静态的synchronized方法, 两者互不影响
    
> ref: https://blog.csdn.net/lynn_Kun/article/details/73850223

```
// synchronized in c++
mutex _mutex;
void f()
{
     unique_lock<mutex> lock(_mutex);
     // access your resource here.
}
```
> ref: https://stackoverflow.com/questions/5429653/what-is-correspoding-feature-for-synchronized-in-java

## Database
### 1. B vs B+
* b+树的中间节点不保存数据, 所以磁盘页能容纳更多节点元素, 更"矮胖";
* b+树查询必须查找到叶子节点, b树只要匹配到即可不用管元素位置, 因此b+树查找更稳定(并不慢);
* 对于范围查找来说, b+树只需遍历叶子节点链表即可, b树却需要重复地中序遍历
> ref: https://blog.csdn.net/login_sonata/article/details/75268075

### 2. ACID
* Atomic: All or nothing transactions 
* Consistent: Any given database transaction must change affected data only in allowed ways. Any data written to the database must be valid according to all defined rules, including constraints, cascades, triggers, and any combination thereof. 
    * eg. A database tracking a checking account may only allow unique check numbers to exist for each transaction
* Isolation: Transcations occur independently
    * Isolation ensures that other banking transactions don’t affect the outcome of your transfer.  Other transaction to alter your checking balance must wait until your transaction completes.
    * eg. A teller looking up a balance must be isolated from a concurrent transaction involving a withdrawal from the same account. Only when the withdrawal transaction commits successfully and the teller looks at the balance again will the new balance be reported.
* Durable: Commited data is never lost
    * eg. A system crash or any other failure must not be allowed to lose the results of a transaction or the contents of the database. Durability is often achieved through separate transaction logs that can "re-create" all transactions from some picked point in time(like a backup).
> ref: https://stackoverflow.com/questions/999394/whats-a-real-world-example-of-acid

> ref: https://blog.sqlauthority.com/2007/12/09/sql-server-acid-atomicity-consistency-isolation-durability/

> ref: https://www.essentialsql.com/what-is-meant-by-acid/

## Algorithm
### 1. 位运算
* Judge: if ((num > n) & 1 == 0) {}
* Update: num = num | (1 < n); num = num & (~(1 < n));
* int le = (1 < n) - 1, ri = (~0) < n;
* Remove rightmost 0: num = num & (num - 1);
