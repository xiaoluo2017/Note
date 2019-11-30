### 1. 描述使用场景, 约束和假设
* 使用场景
   * system main service
     * eg. Pastebin.com: write: 用户添加content, 生成url; 用户使用url, 访问content
   * service要求 eg. 要求高可用
   * 用户是否匿名, timestamp, etc.
   * 超出范畴的用例
* 约束和假设
   * 流量分布不均匀
   * service应该是很快的/不需要实时
   * 读重于写 or 写重于读
   * content只能是文本
   * 用户量/写入量/读取量 -> 读写比
* 计算使用
   * QPS + space
   * 10^8/month -> QPS: 40/s
   
### 2. 创建一个高层次设计
* Client, Server
* Write API, Read API
* SQL, object store(eg. Amazon S3)

### 3. 设计核心组件
* request: Client -> Server -> Write API/Read API
* SQL中表的结构
   * created_at datetime NOT NULL
   * xxx_path varchar(255) NOT NULL
   * 数据库字段创建索引
* Rest API
   * $ curl -X POST --data '{"expiration_length_in_minutes":"60", \"paste_contents":"Hello World!"}' https://pastebin.com/api/v1/paste
   * curl https://pastebin.com/api/v1/paste?shortlink=foobar
     * { "paste_contents": "Hello World", "created_at": "YYYY-MM-DD HH:MM:SS", "expiration_length_in_minutes": "60" }

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
   
### 7.
* 创建高级设计(重看)
