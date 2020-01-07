### 1. const int*, const int * const, int const
> ref: https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const

### 2. regular expression
> ref: https://blog.csdn.net/zengxiantao1994/article/details/77816972

### 3. stack vs heap
* code segment
* 全局区(c里面才划分为data segment/bss segment)
    * data segment(数据段): 存放程序中已初始化且不为0的全局/静态变量的一块内存区域
    * bss segment(BSS段): 存放程序中未初始化的全局/静态变量的一块内存区域
* stack: local variable, method parameter
* heap：new, malloc, calloc, realloc
* 常量区
> ref: https://blog.csdn.net/billcyj/article/details/78783741
    
### 4. TCP UDP
> ref: https://www.quora.com/What-is-the-difference-between-HTTP-protocol-and-TCP-protocol

* TCP网络编程中connect()、listen()和accept()
> ref: https://blog.csdn.net/lianghe_work/article/details/46443691

* TCP建立连接／断开连接状态
    * Client: CLOSED->SYN_SENT->ESTABLISHED->FIN_WAIT_1->FIN_WAIT_2->TIME_WAIT->CLOSED
      * TIME_WAIT: 停留2MSL(Maximum Segment Lifetime, 报文最大生存时间)
    * Server: CLOSED->LISTEN->SYN_RCVD->ESTABLISHED->CLOSE_WAIT->LAST_ACK->CLOSED
> ref: https://blog.csdn.net/Mary19920410/article/details/63711522

* 应用层协议
    * DNS: 主要用UDP, 但是当请求字节过长超过512字节时用TCP协议, 将其分割成多个片段传输
    * 基于TCP的协议: FTP(文件传输协议), Telnet(远程登陆), SMTP(简单邮件传送协议), POP3(接收邮件)
    * 基于UDP的协议: SNMP(简单网络管理协议), OICQ(聊天)
* 传输层协议: TCP, UDP
* 网络层协议: IP, ICMP, RIP
* 数据链路层协议: ARP, RARP
> ref: https://blog.csdn.net/yingxunren/article/details/4726376

### 5. TCP的流量控制 拥塞控制
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

### 6. 一维 二维
```
int a[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 一个一维int数组的数组名实际上是一个int* const类型
int b[8];
int* c = new int[8];

cout << sizeof(a)/sizeof(a[0]) << endl; // 8
cout << sizeof(b)/sizeof(b[0]) << endl; // 8
cout << sizeof(c)/sizeof(c[0]) << endl; // 2
cout << sizeof(*c)/sizeof(c[0]) << endl; // 1
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
* 数组名做参数会退化为指针，除了sizeof

### 7. process vs thread
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

### 8. 进程状态
> ref: https://blog.csdn.net/qicheng777/article/details/77427157

### 9. 父子进程
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

### 10. 函数参数入栈顺序
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

### 11. sizeof struct/sizeof class
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

### 12. 初始化列表
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
        cout<<"Animal"<<endl;
    }
};
  
class Cat : public Animal
{
public:
    int mNum = 1;
    void f() override
    {
        cout<<"Cat"<<endl;
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
### 16. Java 引用传递 值传递
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

### 17. static
* 全局变量/函数 static全局变量/函数 方法中的static变量
    * 全局变量/函数的作用域是整个源程序(.h), 当一个源程序(.h)由多个源文件组成时, 全局变量/函数在各个源文件中都有效; 全局变量在.h中用extern声明, .cpp中定义
    * static全局变量/函数限制了其作用域, 即只在定义该变量/函数的源文件内有效, 在同一源程序的其它源文件中不能使用; 对其它源文件(.h)隐藏, 利用这一特性可以在不同的文件中定义同名函数和同名变量
    * 方法中的static变量, 会在程序刚开始运行时就完成初始化, 也是唯一的一次初始化; 保持变量内容的持久
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

### 18. Java GC
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

### 19. HTTP GET POST PUT DELETE
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

### 20. 锁
* mutex（互斥锁): 
    * 同一时间, 锁只有一把, 如果线程A加锁正在访问资源, 这时B尝试加锁, 就会阻塞;
    * 不加锁也可以访问数据 eg. 线程A加锁了正在访问资源, 这时B不加锁也可以直接访问数据
* 读写锁: 写独占, 读共享; 写锁优先级高; 读写锁特别适用于读的次数远大于写的情况
    * 当读写锁是读模式加锁时, 其它线程以读模式加锁都会成功, 但是线程以写模式加锁会阻塞;
    * 当读写锁是写模式加锁时, 直到解锁前，其它线程加锁都会被阻塞;
    * 当读写锁是读模式加锁时, 其它线程既有试图以写模式加锁的线程，也有试图以读模式加锁的线程, 这时读写锁会阻塞在写模式加锁请求之后的读模式加锁请求, 优先满足写模式
* 条件变量
* 信号量: 
    * 互斥锁在同一时刻只能有一个线程访问加锁的数据, 但是信号量可以允许多个线程来访问
    * 互斥量的加锁和解锁必须由同一线程分别对应使用, 信号量可以由一个线程释放, 另一个线程得到
    * 基于上面的特点, 互斥锁一般用于控制一段临界代码，当然信号量也可以做到; 但是如果释放和获取不在一个函数中甚至不在一个线程中时就必须使用信号量了,
* 信号量vs互斥锁
    * 信号量: 对一个进程加锁, 可以不断加锁, 设置一个标记a == 0, a++; 解锁的时候a--, 当a == 0时可以继续进行; 应用场景: 生产者-消费者模型; 使用场景: 操作系统分配多个打印任务时
    * 互斥锁: 当一个进程把持资源时, 其他进程不能访问此资源, 此特性代表了此资源一次只能被一个进程利用, 使用场景: 文本的写入

### 21. 死锁
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

### 22. Cookie vs Session
* HTTP协议是无状态的协议, 服务端需要记录用户的状态时, 需要用某种机制来识具体的用户(Session)
    * Session是在服务端保存的一个数据结构, 用来跟踪用户的状态, 这个数据可以保存在数据库/Cache中;
* 每次HTTP请求的时候, 客户端都会发送相应的Cookie信息(Session Id)/使用URL重写(如果客户端的浏览器禁用了Cookie)到服务端, cookie来实现Session跟踪
    * Cookie是客户端保存用户信息的一种机制, 用来记录用户的一些信息, 也是实现Session的一种方式
    
### 23. https加密 SSL/TLS协议
* 客户端向服务端发送请求, 服务端返回数字证书
    * 数字证书: CA(在浏览器中)用它的私钥对消息摘要(RSA公钥和个人信息通过Hash算法生成)加密, 形成签名, 并把原始信息和数据签名进行合并, 即所谓的'数字证书', 用于解决中间人问题;
* 客户端用自己的CA公钥去解密证书, 如果证书有问题会提示风险
* 如果证书没问题, 客户端会生成一个对称加密的秘钥, 用刚刚解密的服务器端的RSA公钥进行加密, 发送给服务器端
* 服务器端收到以后会用自己的RSA私钥对客户端发来的对称秘钥进行解密
* 之后双方就拿着这个对称加密秘钥(RSA太慢)来进行正常的通信

### 24. typeid decltype
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

### 25. C++ equivalent of reflection
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

### 26. 用户态 vs 内核态
* 最重要的差别就在于特权级的不同, 运行在用户态下的程序不能直接访问操作系统内核数据结构和程序
    * 用户态: 最低特权级
    * 内核态: 最高特权级
* 执行一个程序, 大部分时间是运行在用户态下的, 在其需要操作系统帮助完成某些它没有权力和能力完成的工作时就会切换到内核态. 最关键性的权力必须由高特权级的程序来执行，这样才可以做到集中管理，减少有限资源的访问和使用冲突, 限制不同的程序之间的访问能力, 防止他们获取别的程序的内存数据, 或者获取外围设备的数据, 并发送到网络

* 用户态切换到内核态
    * 系统调用: 主动方式 eg. fork(): 执行创建新进程的系统调用
    * 异常: CPU在执行运行在用户态下的程序时，发生异常, 则进程会切换到处理此异常的内核相关程序中
    * 外围设备的中断: 向CPU发出相应的中断信号, 执行与中断信号对应的处理程序 eg. 硬盘读写操作完成，系统会切换到硬盘读写的中断处理程序中执行后续操作

> ref: https://blog.csdn.net/youngyoungla/article/details/53106671

### 27. C++ vs Java
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
    * C++ class need both declaration & definition; Java no class declaration, only class definition

> ref: https://www.zhihu.com/question/22928284

### 28. == vs .equals() in Java
* ==: It returns true only if both variables refer to the same object(object equality)
* .equals(): override to compare if "value" is the same(functional equality)
    * If a class does not override the equals method, then it defaults to the equals(Object o) method of the closest parent class that has overridden this method
    * If no parent classes have provided an override, then it defaults to the method from the ultimate parent class: Object. In the Object API this is the same as ==

> ref: https://stackoverflow.com/questions/7520432/what-is-the-difference-between-and-equals-in-java

### 29. Abstract class vs interface in Java
* abstract function(in Java) == pure virtual function(in C++)
* abstract class: has abstract function(in Java)
* virtual class: has pure virtual function(in C++)
* interface(in Java)
    * Functions can only be of type public abstract, member variables can only be of type public static final
    * Cannot contain static code blocks and static methods(abstract classes can have static code blocks and static methods)
    * A class can inherit only one abstract class, but a class can implement multiple interfaces(in Java)

> ref: https://www.cnblogs.com/dolphin0520/p/3811437.html
