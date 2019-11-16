### 1. iterator, map/set insert/get/search/delete
```
std::unordered_map<string, int> m;
m["a"] = 18;
m["b"] = 7;
m["c"] = 22;
m["d"] = 10;
m["e"] = 69;
m["f"] = 2; // set: insert

if (m.find("c") != m.end())
    m.erase("c"); 

for (std::unordered_map<string, int>::iterator it = m.begin(); it != m.end(); it++)
    cout << it->first << ": " << it->second << endl;
    // set: *it
```

### 2. copy constructor, assignment, move constructor, move assignment
```
class B {};

class A
{
public:
    A() { b = new B(); }
    virtual ~A() { delete b; }
    
    A(const A& a) 
    {  
        b = new B;
        *b = *(a.b);
    }
    
    A& operator= (const A& a)
    {
        if (this != &a)
        {
            (*b) = *(a.b);
        }
        return *this;
    }
    
    A(A&& a)
    {
        b = a.b;
        a.b = nullptr;
    }
    // A(A&& a) : b(std::exchange(a.b, nullptr)) {}
    
    A& operator= (A&& a)
    {
        if (b != nullptr)
        {
            delete b;
        }
        b = a.b;
        a.b = nullptr;
        return *this;
    }
private:
    B* b;
};
```
assignment
> ref: https://www.geeksforgeeks.org/assignment-operator-overloading-in-c/

move constructor:
> ref: https://www.quora.com/How-do-you-write-a-move-constructor-in-C

move assignment
> ref: https://www.quora.com/In-C-how-do-you-write-a-move-assignment-operator
> ref: https://stackoverflow.com/questions/9322174/move-assignment-operator-and-if-this-rhs

### 3. Operator Overloading
```
class A
{
public:
    A() { m_i = 0; }
    
    A operator+ (const A& a) 
    { 
        A res;
        res.m_i = m_i + a.m_i;
        return res;
    }
    
    A& operator++() // pre-increment
    {
        m_i++;
        return *this;
    }
    
    A operator++(int) // post-increment
    {
        A tmp(*this);
        operator++();
        return tmp;
    }
    
    friend std::ostream& operator<< (std::ostream& os, const A& a)
    {
        os << a.m_i;
        return os;
    }
    
    friend A operator+ (const A& a1, int i)
    {
        A res;
        res.m_i = a1.m_i + i;
        return res;
    }
    
    friend A operator+ (int i, const A& a2)
    {
        A res;
        res.m_i = i + a2.m_i;
        return res;
    }
    
private:
    int m_i;
};

int main()
{
    A a;
    cout << a << endl; // 0
    
    cout << ++a << endl; // 1
    cout << a++ << endl; // 1

    cout << (a + a) << endl; // 4
    cout << (a + 1) << endl; // 3
    cout << (1 + a) << endl; // 3
}
```
> ref: https://en.cppreference.com/w/cpp/language/operators

### 4. template
```
template <typename T>
T tf(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
}

template <typename T> 
class A { 
public: 
    A(T t) { m_t = t; }
    void print() { cout << m_t << endl; }
private: 
    T m_t; 
}; 

// int vip
template<>
class A<int> {
public:
    A(int i) { m_i = i * 2; }
    void print() { cout << m_i << endl; }
private: 
    int m_i;     
};

int main()
{
    cout << tf<int>(18, 7) << endl;
    
    A<double> a1(22);
    a1.print();
    
    A<int> a2(10);
    a2.print();
}
```
> ref: https://www.geeksforgeeks.org/templates-cpp/
Template Specialization
> ref: https://www.geeksforgeeks.org/template-specialization-c/

### 5. ListNode TreeNode
```
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(NULL) {}
};

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};
```
