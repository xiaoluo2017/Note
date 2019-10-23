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
* 对称密钥: DES、RC4,RC5, AES
* 非对称密钥: RSA
* 哈希算法: MD5, SHA-1，SHA-2(SHA-256，SHA-512)

### 6. 调用约定
* stdcall: 1) 参数从右向左压入堆栈; 2) 函数自身修改堆栈; 3) 函数名自动加前导的下划线，后面紧跟一个@符号，其后紧跟着参数的尺寸
* cdecl: 1) 参数从右向左压入堆栈; 2) 调用者负责清理堆栈
* fastcall: 1) 函数的第一个和第二个DWORD参数（或者尺寸更小的）通过ecx和edx传递，其他参数通过从右向左的顺序压栈; 2) 被调用函数清理堆栈; 3) 函数名修改规则同stdcall
* thiscall: 1) 参数从右向左入栈; 2) 如果参数个数确定，this指针通过ecx传递给被调用者; 如果参数个数不确定，this指针在所有参数压栈后被压入堆栈; 3) 对参数个数不定的，调用者清理堆栈，否则函数自己清理堆栈。
> ref: https://blog.csdn.net/u010852680/article/details/78316633

### 7. 锁
* mutex（互斥锁): 
    * 同一时间，锁只有一把，如果线程A加锁正在访问资源，这时B尝试加锁，就会阻塞;
    * 不加锁也可以访问数据 eg. 线程A加锁了正在访问资源，这时B不加锁也可以直接访问数据

```
// pthread_mutex_t变量类型是一个结构体，可以简单理解成整数，只有1或者0两个取值，初始值为0
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr); 
int pthread_mutex_destroy(pthread_mutex_t* mutex);
int pthread_mutex_lock(pthread_mutex_t* mutex); // mutex--
int pthread_mutex_trylock(pthread_mutex_t* mutex); 
int pthread_mutex_unlock(pthread_mutex_t* mutex); // mutex++
// 当解锁成功时，该函数会把阻塞在该锁上的所有线程全部唤醒，之后哪个线程抢到锁继续执行，就是调度优先级的问题了，默认是先阻塞的先唤醒。
```

* 读写锁: 写独占，读共享。写锁优先级高。读写锁特别适用于读的次数远大于写的情况。
    * 当读写锁是读模式加锁时，其它线程以读模式加锁都会成功，但是线程以写模式加锁会阻塞;
    * 当读写锁是写模式加锁时，直到解锁前，其它线程加锁都会被阻塞;
    * 当读写锁是读模式加锁时，其它线程既有试图以写模式加锁的线程，也有试图以读模式加锁的线程，这时读写锁会阻塞在写模式加锁请求之后的读模式加锁请求，优先满足写模式
    
```
int pthread_rwlock_init(pthread_rwlock_t* rwlock, const pthread_rwlockattr_t* attr);
// attr：表示读写锁属性，通常使用默认属性，传NULL就行了
int pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);
```

* 死锁
* 条件变量

```
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr); 
int pthread_cond_destroy(pthread_cond_t *restrict cond);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
int pthread_cond_timewait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restirct abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
```

* 信号量: 
    * 互斥锁在同一时刻只能有一个线程访问加锁的数据，但是信号量可以允许多个线程来访问。
    * 互斥量的加锁和解锁必须由同一线程分别对应使用，信号量可以由一个线程释放，另一个线程得到。
    * 基于上面的特点，互斥锁一般用于控制一段临界代码，当然信号量也可以做到。但是如果释放和获取不在一个函数中甚至不在一个线程中时就必须使用信号量了。

```
int sem_init(sem_t *sem, int pshared, unsigned int value)

int sem_init(sem_t *sem, int pshared, unsigned int value) // pshared:取0代表用于线程间，取非0代表用于进程间； value:该参数指定信号量初值
int sem_destroy(sem_t *sem)
int sem_wait(sem_t *sem) // == sem--
int sem_post(sem_t *sem) // == sem++
int sem_trywait(sem_t *sem)
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
```

* 信号量vs互斥锁
    * 信号量：对一个进程加锁，可以不断加锁，设置一个标记a == 0, a++。解锁的时候a--, 当a == 0时可以继续进行。应用场景：生产者-消费者模型; 使用场景：操作系统分配多个打印任务时
    * 互斥锁：当一个进程把持资源时，其他进程不能访问此资源，此特性代表了此资源一次只能被一个进程利用，使用场景：文本的写入

### 8. sizeof(struct A)
* 每个结构体成员的起始地址为该成员大小的整数倍，即int型成员的起始地址只能为0、4、8等
> ref: https://blog.csdn.net/RadianceBlau/article/details/60867307

### 9. TCP UDP
> ref: https://www.quora.com/What-is-the-difference-between-HTTP-protocol-and-TCP-protocol

### 10. 二维数组
```
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
```

### 10. TCP的流量控制 拥塞控制
* 流量控制: 滑动窗口

* 拥塞控制: 慢开始、拥塞避免、快重传、快恢复
    * 增加缓存空间到一定程度时，只会加重拥塞，而不是减轻拥塞，因为当数据包经过长期时间排队完成转发时，他们可能早已经超时，从而引起源端超时重发; 增加链路宽带及提高处理能力也不能解决拥塞问题
    * 缓存空间不足导致的丢包更多的是拥塞"症状"而非原因
    * 拥塞只是一个动态问题，我们没有办法用一个静态方案去解决，从这个意义上说，拥塞时不可避免的; 拥塞是一个全局控制的过程，他不像点对点的流控机制，是一个局部的控制

* 慢开始: cwnd *= 2
    * 发送方维持着一个拥塞窗口cwnd（congestion window）
    * cwnd初始化为1个最大报文段（MSS）大小
    * cwnd的值就随着网络往返时间（Round trip time，RTT）呈指数级增长(cwnd *= 2)
    * 如果宽带为W，那么经过RTT*log2W时间就可以占满带宽
* 拥塞避免: cwnd += 1
    * 慢启动门限（ssthresh）
    * 当cwnd < ssthresh时，使用慢开始算法。
    * 当cwnd > ssthresh时，改用拥塞避免算法。(cwnd += 1)
    * 当cwnd = ssthresh时，慢开始与拥塞避免算法任意。
* 快重传
    * 发送方只要一连收到三个重复确认就应当立即重传对方尚未收到的报文段，而不必继续等待设置重传计时器时间到期。
* 快恢复
    * 当发送方连续收到三个重复确认时，把ssthresh门限减半(ssthresh = cwnd / 2), 并直接进入拥塞避免算法(cwnd = ssthresh)
* 发生超时重传: 网络拥塞的主要依据是它重传了一个报文段
    * 把ssthresh降低为cwnd值的一半(ssthresh = cwnd / 2);
    * 把cwnd重新设置为1(cwnd = 1);
    * 重新进入慢启动过程;
> ref: http://www.voidcn.com/article/p-vrdkquop-ms.html

### 11. 悲观锁与乐观锁
* 乐观锁: 版本号机制, CAS算法
* 乐观锁的缺点: ABA问题; 自旋CAS(不成功就一直循环执行直到成功)
> ref: https://zhuanlan.zhihu.com/p/40211594

### 12. KMP
> ref: http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
