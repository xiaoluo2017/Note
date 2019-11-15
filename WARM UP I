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
// 未完成
```
class B
{
public:
    B() { cout << "B()" << endl; }
    
    B(int i) 
    { 
        cout << "B(int " + std::to_string(i) + ")" << endl; 
        m_pi = new int(i);
    }
    
    virtual ~B() { cout << "~B" << endl; }
private:
    int* m_pi;
};

class A
{
public:
    A(int i) { 
        cout << "A" << endl; 
        b = new B(i);
    }
    
    virtual ~A() { 
        cout << "~A" << endl; 
        delete b;
    }
    
    A(const A& a) 
    {  
        cout << "A copy constructor" << endl; 
        b = new B;
        *b = *(a.b);
    }
private:
    B* b;
};

void f(A a) {}

int main() {
    A a(18);
    f(a);
    cout << "Hello World" << endl;
}
```
