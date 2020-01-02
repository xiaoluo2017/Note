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
* SQL vs NOSQL
* Load Balaner
* DNS
* CDN

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
