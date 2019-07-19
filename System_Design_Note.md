# System Design

* [System design topics: start here](#system-design-topics-start-here)
    * [Step 1: Review the scalability video lecture](#step-1-review-the-scalability-video-lecture)
    * [Step 2: Review the scalability article](#step-2-review-the-scalability-article)
    * [Next steps](#next-steps)
* [Performance vs scalability](#performance-vs-scalability)
* [Latency vs throughput](#latency-vs-throughput)
* [Availability vs consistency](#availability-vs-consistency)
    * [CAP theorem](#cap-theorem)
        * [CP - consistency and partition tolerance](#cp---consistency-and-partition-tolerance)
        * [AP - availability and partition tolerance](#ap---availability-and-partition-tolerance)

## System design topics: start here
### Step 1: Review the scalability video lecture
* Topics covered:
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
