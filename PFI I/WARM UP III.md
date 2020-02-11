### 1. KMP
```
void createLPS(string s, int lps[], int n)
{
    int len = 0;
    lps[0] = 0;
    for (int i = 1; i < n; i++)
    {
        if (s[i] == s[len])
        {
            len++;
            lps[i] = len;
        }
        else
        {
            if (len == 0)
            {
                lps[i] = 0;
            }
            else
            {
                len = lps[len - 1];
                i--;
            }
        }
    }
}

vector<int> f(string s1, string s2)
{
    int m = s1.size(), n = s2.size();
    int lps[n] = {0};
    createLPS(s2, lps, n);
    
    vector<int> res;
    int i = 0, j = 0;
    while (i <= m)
    {
        if (s1[i] == s2[j])
        {
            i++;
            j++; 
        }
        else
        {
            if (j == 0)
            {
                i++;
            }
            else
            {
                j = lps[j - 1];
            }
        }
        
        if (j == n)
        {
            res.push_back(i - j);
            j = lps[j - 1];
        }
    }
    return res;
}
```

### 2. Trie
```
struct TrieNode
{
    bool isWord;
    TrieNode* children[26];
    TrieNode() : isWord(false) {
        memset(children, NULL, sizeof(children));
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word)
        {
            if (curr->children[c - 'a'] == NULL)
            {
                curr->children[c - 'a'] = new TrieNode();
            }
            curr = curr->children[c - 'a'];
        }
        curr->isWord = true;
    }
    
    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word)
        {
            if (curr->children[c - 'a'] != NULL)
            {
                curr = curr->children[c - 'a'];
            }
            else
            {
                return false;
            }
        }
        
        return curr->isWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix)
        {
            if (curr->children[c - 'a'] != NULL)
            {
                curr = curr->children[c - 'a'];
            }
            else
            {
                return false;
            }
        }
        
        return true;
    }
private:
    TrieNode* root;
};
```

### 3. LRU
```
struct DLL
{
    int key, val;
    DLL* prev;
    DLL* next;
    DLL(int k = 0, int v = 0) : key(k), val(v), prev(NULL), next(NULL) {}
};

class LRUCache {
public:
    LRUCache(int c) : capacity(c), size(0) {
        head = new DLL();
        tail = new DLL();
        head->next = tail;
        tail->prev = head;
    }
    
    virtual ~LRUCache()
    {
        delete head;
        delete tail;
    }
    
    void addToHead(DLL* node)
    {
        head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
    }
    
    void removeNode(DLL* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = NULL;
        node->next = NULL;
    }
    
    
    int get(int key) {
        if (m.find(key) == m.end())
        {
            return -1;
        }
        
        DLL* curr = m[key];
        removeNode(curr);
        addToHead(curr);
        
        return curr->val;
    }
    
    void put(int key, int value) {
        if (m.find(key) != m.end())
        {
            DLL* curr = m[key];
            curr->val = value;
            removeNode(curr);
            addToHead(curr);
            return;
        }
        
        if (size < capacity)
        {
            size++;
        }
        else
        {
            DLL* removed = tail->prev;
            m.erase(removed->key);
            removeNode(removed);
            delete removed;
        }
        
        DLL* curr = new DLL(key, value);
        addToHead(curr);
        m[key] = curr;
    }
private:
    DLL* head;
    DLL* tail;
    unordered_map<int, DLL*> m;
    int size, capacity;
};
```

### 4. Basic Calculator
```
int calculate(string str) {
    stack<int> s;
    int i = 0, num = 0;
    char symbol = '+';
    while (i <= str.size())
    {
        if (str[i] == ' ')
        {
            i++;
            continue;
        }

        if (i == str.size() 
            || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            if (symbol == '*')
            {
                num = s.top() * num;
                s.pop();
            }
            else if (symbol == '/')
            {
                num = s.top() / num;
                s.pop();
            }
            else if (symbol == '-')
            {
                num *= -1;
            }

            s.push(num);

            if (i == str.size()) break;

            symbol = str[i];
            num = 0;
        }
        else
        {
            num *= 10;
            num += str[i] - '0';
        }

        i++;
    }

    int res = 0;
    while (!s.empty())
    {
        res += s.top();
        s.pop();
    }

    return res;
}
```

### 5. 
```
int lengthOfLongestSubstring(string s) {
    int le = 0, ri = 0, res = 0;
    int hash[256] = {0};
    while (ri <= s.size())
    {
        if (ri == s.size())
        {
            int tmp = ri - le;
            res = res > tmp ? res : tmp;
        }

        if (hash[s[ri]]++ == 1)
        {
            int tmp = ri - le;
            res = res > tmp ? res : tmp;

            while(le < ri)
            {
                if (hash[s[le++]]-- == 2)
                {
                    break;
                }
            }
        }

        ri++;
    }

    return res;
}
```

### 6. Kth Largest Element in an Array
```
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int> pq;
    for (int i : nums)
    {
        pq.push(i);
    }

    while (--k > 0)
    {
        pq.pop();
    }

    return pq.top();
}
```

```
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i : nums)
    {
        pq.push(i);
        if (pq.size() > k) pq.pop();
    }

    return pq.top();
}
```

```
int quickSort(vector<int>& nums, int k, int start, int end)
{
    if (start == end) return nums[start];

    int pivot = start, le = start + 1, ri = end;

    while (le < ri)
    {
        if (nums[le] < nums[pivot])
        {
            le++;
        }
        else
        {
            int tmp = nums[le];
            nums[le] = nums[ri];
            nums[ri] = tmp;
            ri--;
        }
    }

    
    if (nums[le] > nums[pivot])
        le--;
    
    int tmp = nums[le];
    nums[le] = nums[pivot];
    nums[pivot] = tmp;

    if (le == nums.size() - k)
    {
        return nums[le];
    }
    else if (le < nums.size() - k)
    {
        return quickSort(nums, k, le + 1, end);
    }
    else
    {
        return quickSort(nums, k, start, le - 1);
    }
}

int findKthLargest(vector<int>& nums, int k) {
    return quickSort(nums, k, 0, nums.size() - 1);
}
```
