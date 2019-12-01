### 12.2
```
void f(char* str)
{
    int le = 0, ri = 0;
    while (str[ri] != '\0')
    {
        ri++;
    }
    ri--;
    
    while (le < ri)
    {
        char tmp = str[le];
        str[le++] = str[ri];
        str[ri--] = tmp;
    }
}

int main() {
    char str[] = "hello world";
    f(str);
    cout << str << endl;
}
```

### 12.8
```
Node* helper(Node* node, unordered_map<Node*, Node*>& m)
{
    if (node == NULL) return NULL;

    if (m.find(node) != m.end()) return m[node];

    vector<Node*> v;
    Node* res = new Node(node->val, v);
    m[node] = res;
    for (Node* curr : node->neighbors)
    {
        if (m.find(curr) == m.end())
        {
            res->neighbors.push_back(helper(curr, m));
        }
        else
        {
            res->neighbors.push_back(m[curr]);
        }
    }
    return res;
}

Node* cloneGraph(Node* node) {
    unordered_map<Node*, Node*> m;
    return helper(node, m);
}
```
> ref: https://leetcode.com/problems/clone-graph/submissions/

### 12.9
```
template <typename T> 
class smartPointer { 
public:
    smartPointer(T* t) : m_ptr(t)
    {
        ref_count = new int(1);
    }
    
    virtual ~smartPointer() { 
        if (--(*ref_count) == 0)
        {
            delete m_ptr;
            delete ref_count;
            ref_count = nullptr;
            m_ptr = nullptr;
        }
            
    }
    
    smartPointer(const smartPointer& s) : m_ptr(s.m_ptr), ref_count(s.ref_count)
    {  
        (*ref_count)++;
    }
    
    smartPointer& operator= (const smartPointer& s)
    {
        if (this != &s)
        {
            if (--(*ref_count) == 0)
            {
                delete m_ptr;
                delete ref_count;
            }
            m_ptr = s.m_ptr;
            ref_count = s.ref_count;
            (*ref_count)++;
        }
        return *this;
    }
    
    T& operator*(){
        return *m_ptr;
    }

    T* operator->(){
        return m_ptr;
    }
private: 
    T* m_ptr;
    int* ref_count;
}; 
```

### 12.10
```
void* align_malloc(int size, int align)
{
    int offset = align - 1 + sizeof(void*);
    void* p;
    if ((p = malloc(size + offset)) == NULL)
        return NULL;
    
    void* res = (void*)((size_t(p) + offset) & ~(align - 1));
    ((void**)res)[-1] = p;
    
    return res;
}

void align_free(void* ptr)
{
    void* p = ((void**)ptr)[-1];
    free(p);
}
```
