### 4. Hash Table Collision Resolution
* Open Addressing with Linear Probing: cause an issue called clustering

### 5. Rabin-Karp Substring Search

### 6. AVL Trees
* Inserts
   * Blance is 2(le - ri = 2): left right shape ->(left rotation) left left shape ->(right rotation) balanced
   * Blance is -2(le - ri = -2): right left shape ->(right rotation) right right shape ->(left rotation) balanced

### 7.Red-Black Trees
* Insertion
   * N: current node; P: N's parent; G: N's grandparent; U: P's sibling
   * N has a Red violation
   * Case 1: U is red
     * Flip G from black to red. Flip P & U from red to black.
   * Case 2: U is black
     * Reorgnaize based on in-order traverse

### 8. MapReduce
* process large amounts of data in parallel
* Requires you to write a Map step and a Reduce step, the rest is handle by the system
* Process:
   * The system splits up the data into different machines
   * Each machine starts running the user-provided the Map program, the Map program takes some data and emits a <key, value> pair
   * The system-provided Shuffle process reorganizes the data so that all the <key, value> pair associated with a given key go to the same machine, to be processed by reduce
   * The user-provided Reduce process takes a key and a set of associated values and "reduces" them in some way, emitting a new key and value.
   
### 12. B-Trees
* Commonly used on disks or other storage devices. Similar to a red-black tree, but use fewer I/O operations.
