### 1. 描述使用场景, 约束和假设
* 使用场景
   * system main service
     * eg. Pastebin.com: write: 用户添加content, 生成url; 用户使用url, 访问content
   * service要求 eg. 要求高可用
   * 超出范畴的用例
* 约束和假设
   * 流量分布不均匀
   * service应该是很快的/不需要实时
   * 读重于写 or 写重于读
   * content只能是文本, 用户是否匿名, timestamp, etc.
   * 用户量/单位写入次数/单位读取次数/单次写入数据量
* 计算使用
   * Read/Write QPS + space + Read/Write ratio
   * 10^8/month -> QPS: 40/s
   
### 2. 创建一个高层次设计
* Client, Server
* Write API, Read API
   * Query API(eg. web crawler), Accounts ApI(eg. Mint.com)
* Service + Queue
   * Reverse Index Service, Document Service(eg. web crawler)
   * Transaction Extraction Service, Category Service, Budget Service, Notification Service(eg. Mint.com)
* SQL, object store(eg. Amazon S3), Key-value Nosql(eg. web crawler)

### 3. 设计核心组件
* request: Client -> Server -> Write API/Read API
* SQL中表的结构
   * created_at datetime NOT NULL
   * xxx_path varchar(255) NOT NULL
   * 数据库字段创建索引
* Rest API
   * $ curl -X POST --data '{"expiration_length_in_minutes":"60", "paste_contents":"Hello World!"}' https://pastebin.com/api/v1/paste
     * { "shortlink": "foobar" }
   * $ curl -X POST --data '{ "user_id": "foo", "account_url": "bar", "account_login": "baz", "account_password": "qux" }' https://mint.com/api/v1/account
   
   * $ curl https://pastebin.com/api/v1/paste?shortlink=foobar
     * { "paste_contents": "Hello World", "created_at": "YYYY-MM-DD HH:MM:SS", "expiration_length_in_minutes": "60" }
   * $ curl https://search.com/api/v1/search?query=hello+world
   * $ curl https://amazon.com/api/v1/popular?category_id=1234
     
### 4. 扩展设计
* SQL -> SQL Write Master-Slave --- SQL Read Replicas
* Read API + Memory cache
* Client + CDN + Object store
* Client + DNS
* Client + Load Balancer

### 5. 讨论要点、权衡和替代方案
* SQL Write Master-Slave
   * Federation(联合), 将数据库按对应功能分割 eg. 论坛/用户/产品
   * Sharding(分片), 将数据分配在不同的数据库上 eg. 用户姓氏的首字母或者用户的地理位置来分隔用户表
   * 优点
     * 减少每个数据库的读取和写入流量
     * 提高缓存命中率
     * 可以并行写入，提高负载能力
   * 缺点
     * 联结多个联合/分片的数据操作更复杂
     * 联合/分片需要更多的硬件和额外的复杂度
     * 联合需要额外逻辑来确定要读取和写入哪个数据库
     * 分片不合理可能导致数据负载不均衡(一致性哈希)
* SQL Read Replicas
   * denormalized(非规范化): 冗余数据副本，以避免高成本的联结操作
     * 约束可以帮助冗余的信息副本保持同步，但这样会增加数据库设计的复杂度
     * 在高写入负载下性能可能比规范化的数据库差
   * cache(缓存)
     * Cache-aside(旁路缓存模式): 应用向缓存中读取数据
     * Write-through(直写模式): 应用向缓存中读取/添加/更新数据
       * 后端存储将始终具有最新数据, 如果写入了缓存, 则后端存储也将被相应地写入
       * 写入的大多数数据可能永远都不会被读取
     * write-back(回写模式): 在数据更新时只写入缓存, 只在数据被替换出缓存时, 被修改的缓存数据才会被写到后端存储
       * 回写策略不能保证该块在后端存储与缓存中是相同的
       * 一旦更新后的数据未被写入存储时出现系统掉电的情况, 数据将无法找回
* SQL vs NOSQL
   * SQL: 事务, 关系型数据
   * NoSQL: 高吞吐量, 存储TB(甚至PB)级别的数据, 非关系型数据
* 高可用
   * fail-over(故障切换)
     * 主从切换(Active-passive): 工作到备用切换, 工作服务器发送周期信号给待机中的备用服务器, 如果周期信号中断, 备用服务器切换成工作服务器的IP地址并恢复服务
     * 主主切换(Active-active): 双工作切换, 双方都在管控流量, 在它们之间分散负载
   * replica(复制)
     * 主从复制: 主库同时负责读取和写入操作, 并复制写入到一个或多个从库中, 从库只负责读操作, 树状形式的从库再将写入复制到更多的从库中去
     * 主主复制: 两个主库都负责读操作和写操作，写入操作时互相协调。如果其中一个主库挂机，系统可以继续读取和写入
* Load Balaner
* DNS
* CDN
   * 内容分发网络(CDN)是一个全球性的代理服务器分布式网络, 它从靠近用户的位置提供静态内容, CDN的DNS解析会告知客户端连接哪台服务器
     * eg. HTML/CSS/JS，图片和视频 
   * CDN推送(push): 当你服务器上内容发生变动时, 直接推送给CDN并重写URL地址以指向存储内容的CDN地址 
     * 内容只有在更改或新增是才推送, 流量最小化, 但储存最大化
   * CDN拉取(pull): 当用户请求资源时, 从服务器上拉取资源, 将内容留在CDN服务器上并重写URL指向CDN地址
     * CDN拉取方式最小化CDN上的储存空间, CDN缓存内容可能会过时(存活时间TTL), 高流量站点使用CDN拉取效果不错
> ref: https://stackoverflow.com/questions/27087912/write-back-vs-write-through-caching

### 6. 设计 Pastebin.com
* 生成唯一的url:
   * 使用MD5来哈希用户的IP地址 + 时间戳
   * 用Base 62编码MD5哈希值
   * 取输出的前7个字符

### 7. Design a web crawler
* Service crawls a list of urls
   * links_to_crawl(key-value NoSQL Database + Redis with sorted sets, initially based on overall site popularity), crawled_links(key-value NoSQL Database)
   * Takes the top ranked page link to crawl
   * Checks crawled_links in the NoSQL Database for an entry with a similar page signature
     * If we have a similar page, reduces the priority of the page link
     * If not: Job: Reverse Index Service queue; Job: Document Service queue; Generates page signature; Removes from links_to_crawl; Inserts into crawled_links

### 8. Design Mint.com
* Use case: Service extracts transactions from the account
   * Accounts API server places a job on a Queue
   * Transaction Extraction Service: Pulls from the Queue and extracts transactions for the given account from the financial institution, storing the results as raw log files in the Object Store
   * Category Service: categorize each transaction
   * Budget Service: calculate aggregate monthly spending by category
   * Notification Service: let users know if they are nearing or have exceeded their budget
   * Updates SQL Database transactions table & monthly_spending table
   
### 9. Design a key-value cache to save the results of the most recent web server queries
* Query API server
   * Parses the query
   * Removes markup
   * Breaks up the text into terms
   * Fixes typos
   * Normalizes capitalization
   * Converts the query to use boolean operations
* The page contents change
   * Set a max time that a cached entry can stay in the cache before it is updated, usually referred to as time to live (TTL).
   
### 10. Design Amazon's sales rank by category feature
* Sales Rank Service
   * store the raw Sales API server log files on a managed Object Store such as Amazon S3
   * The Sales Rank Service could use MapReduce, using the Sales API server log files as input and writing the results to an aggregate table sales_rank in a SQL Database
