# System Design

* [System design topics: start here](#system-design-topics-start-here)
    * [Step 1: Review the scalability video lecture](#step-1-review-the-scalability-video-lecture)
    * [Step 2: Review the scalability article](#step-2-review-the-scalability-article)

## System design topics: start here
### Step 1: Review the scalability video lecture
 * Scaling
     * Vertical scaling: Get more RAM, more processor, more disk space. eg. mechanical drive -> solid-state drive(SSD)
     * Horizontal scaling: a bunch of slower/cheaper servers
         * load balancer: public IP address
         * back-end servers: private(rest of world can't see) IP addresses
 * Load balancer select server(how busy)
     * Dedicated servers: PHP, Gif, video server
         * Downside: 1) No redundancy, not good for uptime if anything breaks 2) May have too much load for a single PHP server
     * Round robin(DNS based)
         * Downside: Some servers may get more heavyweight users then other server; No sticky session
 * RAID(Redundant Array of Independent disks): solve redundancy issue of confines of a single server
     * raid 0: 2 identical hard drives, stripe(write in turn), nice for performance
     * raid 1: 2 identical hard drives, mirror data, store in both places, either can die
     * raid 5: 3/4/5 drives, only 1 of them is used for redundancy
     * raid 6: Any 2 drives can die, won't have lost any data 
     * raid 10: 4 identical hard drives, both striping & redundancy
 * Sticky Session
     * File server(big external hard drive), or Sessions on load balancer
     * cookies
         * Downside: 1) violant privacy: store info 2) have a finite size
     * Store ID of server in cookies
         * Downside: 1) put private IP, maybe IP changes 2) need reveal to world what your IP scheme is
     * Store a big random number: load balancer remember big number belongs to which server
 * MySQL feature
     * memory engine: store in RAM
     * Archieve storage engine: compressed by default(take smaller space), research/diagnostic purposes(slower to query). eg. log file
     * NDB(Network storage engine): clustering, solve single point failure
 * Data replication
     * Master-slave
         * upside: 1) redundancy 2) good for read heavy, write less, blance read requests. eg. facebook
     * Master-Master: to solve single point failure
     * load balancer
         * active-active: Send heartbeats(a packet), either can receive
         * active-passive: When active die, passive promote itself to be active
 * Partitioning: eg. Login based on last name: A to M, N to Z
 * Data center redundancy: get IP of load balancer of building
 * Security
     * cloud - load balancer: TCP80, TCP443(default port used for SSL, for HTTP based urls)
     * load balancer - web servers: TCP80, offload SSL, unencrypted
     * web server - databases: TCP3306(SQL queries)
     * Firewalls: least privilege, avoid unexpected behaviour
     
### Step 2: Review the scalability article
 * Clones
     * Every server contains exactly the same codebase and does not store any user-related data, like sessions or profile pictures, on local disc or memory
     * Sessions store in centralized data store(an external persistent cache, like Redis), near the data center, not reside on the application servers
     * To make sure code change sent to all your servers without one server still serving old code, use Capistrano(Ruby on Rails)
 * Databases
     * Path 1: Hire a database administrator(DBA), do master-slave replication (read from slaves, write to master), upgrade master server by adding RAM. -> DBA will come up with words like “sharding”, “denormalization” and “SQL tuning", every new action to keep your database running will be more expensive and time consuming than the previous one
     * Path 2: Denormalize right from the beginning and include no more Joins in any database query, use MySQL like a NoSQL database, or switch to a NoSQL database like MongoDB or CouchDB(better and easier to scale), Joins need to be done in application code. -> slower and slower, need to introduce a cache
 * Caches
     * In-memory caches: Memcached or Redis, lightning-fast
     * Redis(vs Memcached): extra database-features, persistence and the built-in data structures like lists and sets
     * Cached Database Queries
         * key: A hashed version of your query
         * Downside: expiration, it is hard to delete a cached result when you cache a complex query, when one piece of data changes you need to delete all cached queries who may include that table cell
     * Cached Objects
 * Asynchronism
     * Async 1: Doing the time-consuming work in advance and serving the finished work with a low request time. eg. turn dynamic content into static content
     * Async 2: Handle tasks asynchronously. Backend have a queue of tasks or jobs that a worker can process; frontend constantly checks for new “job is done” signals
