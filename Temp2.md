### 1. 右移操作 >>
* 对于有符号整数, 每一次右移操作, 高位补充的是1;
* 对于无符号整数, 每一次右移操作, 高位补充的则是0

### 2. #define typedef
```
#define INT_PTR int*
typedef int* int_ptr;
INT_PTR a1, a2;
int_ptr b1 ,b2;
int *c1, c2;

cout << sizeof(a1) << endl;
cout << sizeof(a2) << endl;
cout << sizeof(b1) << endl;
cout << sizeof(b2) << endl;
cout << sizeof(c1) << endl;
cout << sizeof(c2) << endl;
```
> ref: https://stackoverflow.com/questions/3263252/is-typedef-just-a-string-replacement-in-code-or-somethings-else

### 3. KMP
> ref: http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html

### 4. 子网掩码 
> ref: https://baike.baidu.com/item/%E5%AD%90%E7%BD%91%E6%8E%A9%E7%A0%81

### 5. 霍夫曼编码
> ref: https://zh.wikipedia.org/wiki/%E9%9C%8D%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81

### 6. 加密算法
* 对称密钥: DES、RC4,RC5, AES
* 非对称密钥: RSA
* 哈希算法: MD5, SHA-1，SHA-2(SHA-256，SHA-512)
> ref: https://www.jianshu.com/p/bf1d7eee28d0

### 7. HTTP 1.0 vs HTTP 1.1
HTTP 1.1支持长连接; 流水线; host字段; 100(Continue) Status; Chunked transfer-coding; cache
> ref: https://www.jianshu.com/p/95a521b006a8

### 8. 调用约定
* stdcall: 1) 参数从右向左压入堆栈; 2) 函数自身修改堆栈; 3) 函数名自动加前导的下划线, 后面紧跟一个@符号, 其后紧跟着参数的尺寸
* cdecl: 1) 参数从右向左压入堆栈; 2) 调用者负责清理堆栈
* fastcall: 1) 函数的第一个和第二个DWORD参数（或者尺寸更小的）通过ecx和edx传递, 其他参数通过从右向左的顺序压栈; 2) 被调用函数清理堆栈; 3) 函数名修改规则同stdcall
* thiscall: 1) 参数从右向左入栈; 2) 如果参数个数确定, this指针通过ecx传递给被调用者; 如果参数个数不确定, this指针在所有参数压栈后被压入堆栈; 3) 对参数个数不定的, 调用者清理堆栈, 否则函数自己清理堆栈
> ref: https://blog.csdn.net/u010852680/article/details/78316633

### 9. 贪心算法
贪心算法与动态规划的不同在于它对每个子问题的解决方案都做出选择，不能回退。动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。

Dijkstra
> ref: https://blog.csdn.net/qq_35644234/article/details/60870719

Kruskal
> ref: https://zh.wikipedia.org/wiki/%E5%85%8B%E9%B2%81%E6%96%AF%E5%85%8B%E5%B0%94%E6%BC%94%E7%AE%97%E6%B3%95

Prim
> ref: https://zh.wikipedia.org/wiki/%E6%99%AE%E6%9E%97%E5%A7%86%E7%AE%97%E6%B3%95

### 10. 扇区 簇 块 页
* 扇区: 扇区是磁盘最小的物理存储单元, 硬盘不是一次读写一个字节而是一次读写一个扇区（512个字节）
* 簇: 系统读读写文件的基本单位, 一般为2的n次方个扇区(由文件系统决定), 每个簇或者块可以包括2、4、8、16、32、64…2的n次方个扇区; 操作系统规定一个簇中只能放置一个文件的内容
* 原因: 读取方便, 由于扇区的数量比较小, 数目众多在寻址时比较困难, 所以操作系统就将相邻的扇区组合在一起, 形成一个块, 再对块进行整体的操作
* 块/页: 与内存操作, 是虚拟一个页的概念来作为最小单位; 与硬盘打交道, 就是以块为最小单位
> ref: https://blog.csdn.net/qq_34228570/article/details/80209748

### 11. InterruptedException异常
当一个方法后面声明可能会抛出InterruptedException 异常时, 说明该方法是可能会花一点时间, 但是可以取消的方法: wait sleep join
> ref: https://blog.csdn.net/derekjiang/article/details/4845757

### 12. 悲观锁与乐观锁
* 乐观锁: 版本号机制, CAS算法
* 乐观锁的缺点: ABA问题; 自旋CAS(不成功就一直循环执行直到成功)
> ref: https://zhuanlan.zhihu.com/p/40211594

### 13. java包
* java.lang 该包提供了Java编程的基础类，例如 Object、Math、String、StringBuffer、System、Thread等，不使用该包就很难编写Java代码了。
* java.util 该包提供了包含集合框架、遗留的集合类、事件模型、日期和时间实施、国际化和各种实用工具类（字符串标记生成器、随机数生成器和位数组）。
* java.sql 该包提供了使用Java语言访问并处理存储在数据源（通常是一个关系型数据库）中的数据API

### 14. 预编译指令 操作符 函数
* 预编译指令(带#): eg. #pragma #define a:malloc; 
* 操作符: eg. new, delete, sizeof, +, -, *
* 函数: eg. malloc, 参数为字节数, 返回一个void*指针; free
    * free函数是由C语言继承而来的, 和malloc配对的, 而不能和new配对
    * 用new申请的就要用delete翻译, 用malloc申请的就要用free释放
    * free只是告诉操作系统回收内存, 而delete会先调用类的析构函数, 然后才告诉操作系统回收内存
```
int *p;
p = (int*)malloc(sizeof(int) * 128);
```

### 15. 前缀 中缀 后缀表达式
* 前缀表达式的计算机求值: 从右至左扫描表达式, 遇到数字时, 将数字压入堆栈, 遇到运算符时, 弹出栈顶的两个数, 用运算符对它们做相应的计算(栈顶元素 op 次顶元素), 并将结果入栈
* 中缀表达式转换为前缀表达式
    * 初始化两个栈: 运算符栈S1和储存中间结果的栈S2;
    * 从右至左扫描中缀表达式;
    * 遇到操作数时, 将其压入S2;
    * 遇到运算符时, 比较其与S1栈顶运算符的优先级:
      * 如果S1为空, 或栈顶运算符为右括号")", 则直接将此运算符入栈;
      * 否则, 若优先级比栈顶运算符的较高或相等, 也将运算符压入S1; 
      * 否则，将S1栈顶的运算符弹出并压入到S2中, 再次与S1中新的栈顶运算符相比较;
    * 遇到括号时:
      * 如果是右括号")", 则直接压入S1;
      * 如果是左括号"(", 则依次弹出S1栈顶的运算符, 并压入S2, 直到遇到右括号为止, 此时将这一对括号丢弃;
    * 最后将S1中剩余的运算符依次弹出并压入S2;
* 后缀表达式的计算机求值: 从左至右扫描表达式, 遇到数字时, 将数字压入堆栈, 遇到运算符时, 弹出栈顶的两个数, 用运算符对它们做相应的计算(次顶元素 op 栈顶元素), 并将结果入栈;
* 中缀表达式转换为后缀表达式
    * 初始化两个栈: 运算符栈S1和储存中间结果的栈S2;
    * 从左至右扫描中缀表达式;
    * 遇到操作数时, 将其压入S2;
    * 遇到运算符时, 比较其与S1栈顶运算符的优先级:
      * 如果S1为空, 或栈顶运算符为左括号"(", 则直接将此运算符入栈;
      * 否则, 若优先级比栈顶运算符的高, 也将运算符压入S1(注意转换为前缀表达式时是优先级较高或相同, 而这里则不包括相同的情况);
      * 否则, 将S1栈顶的运算符弹出并压入到S2中, 再次与S1中新的栈顶运算符相比较;
    * 遇到括号时:
      * 如果是左括号"(", 则直接压入S1;
      * 如果是右括号")", 则依次弹出S1栈顶的运算符, 并压入S2, 直到遇到左括号为止, 此时将这一对括号丢弃;
    * 最后将S1中剩余的运算符依次弹出并压入S2;
    * 依次弹出S2中的元素并输出, 结果的逆序即为中缀表达式对应的后缀表达式(转换为前缀表达式时不用逆序)
> ref: https://blog.csdn.net/Antineutrino/article/details/6763722
