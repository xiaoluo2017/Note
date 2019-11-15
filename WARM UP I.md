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

