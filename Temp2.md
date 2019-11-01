### 1. 右移操作 >>
* 对于有符号整数，每一次右移操作，高位补充的是1;
* 对于无符号整数，每一次右移操作，高位补充的则是0

### 2. java包
* java.lang 该包提供了Java编程的基础类，例如 Object、Math、String、StringBuffer、System、Thread等，不使用该包就很难编写Java代码了。
* java.util 该包提供了包含集合框架、遗留的集合类、事件模型、日期和时间实施、国际化和各种实用工具类（字符串标记生成器、随机数生成器和位数组）。
* java.sql 该包提供了使用Java语言访问并处理存储在数据源（通常是一个关系型数据库）中的数据API。

### 3. HTTP 1.0 vs HTTP 1.1
HTTP 1.1支持长连接; 流水线; host字段; 100(Continue) Status; Chunked transfer-coding; cache
> ref: https://www.jianshu.com/p/95a521b006a8

### 4. 霍夫曼编码
> ref: https://zh.wikipedia.org/wiki/%E9%9C%8D%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81

### 5. 贪心算法
贪心算法与动态规划的不同在于它对每个子问题的解决方案都做出选择，不能回退。动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。

Dijkstra
> ref: https://blog.csdn.net/qq_35644234/article/details/60870719

Kruskal
> ref: https://zh.wikipedia.org/wiki/%E5%85%8B%E9%B2%81%E6%96%AF%E5%85%8B%E5%B0%94%E6%BC%94%E7%AE%97%E6%B3%95

Prim
> ref: https://zh.wikipedia.org/wiki/%E6%99%AE%E6%9E%97%E5%A7%86%E7%AE%97%E6%B3%95

### 6. 子网掩码 
> ref: https://baike.baidu.com/item/%E5%AD%90%E7%BD%91%E6%8E%A9%E7%A0%81

### 7. 悲观锁与乐观锁
* 乐观锁: 版本号机制, CAS算法
* 乐观锁的缺点: ABA问题; 自旋CAS(不成功就一直循环执行直到成功)
> ref: https://zhuanlan.zhihu.com/p/40211594
