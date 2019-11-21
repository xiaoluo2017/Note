### 3.2
```
class c_stack
{
public:
    void push(int i)
    {
        if (min_stack.empty() || i <= min_stack.top())
            min_stack.push(i);
        m_stack.push(i);
    }
    
    bool pop()
    {
        if (m_stack.empty())
            return false;
        
        if (m_stack.top() == min_stack.top())
            min_stack.pop();
        m_stack.pop();
        return true;
    }
    
    int min()
    {
        if (min_stack.empty())
            return -1;
        
        return min_stack.top();
    }
private:
    stack<int> m_stack;
    stack<int> min_stack;
};
```

### 3.3
```
class SetOfStackes
{
public:
    SetOfStackes(int capacity) : m_Capacity(capacity) {}
    
    void push(int i)
    {
        if (v.empty() || v[v.size() - 1].size() == m_Capacity)
        {
            stack<int> s;
            s.push(i);
            v.push_back(s);
        }
        else
        {
            v[v.size() - 1].push(i);
        }
    }
    
    bool popAt(int i)
    {
        if (i < v.size())
        {
            v[i].pop();
            if (v[i].empty())
                v.erase(v.begin() + i);
            return true;
        }
        return false;
    }
    
    bool pop()
    {
        if (!v.empty())
        {
            v[v.size() - 1].pop();
            if (v[v.size() - 1].empty())
                v.erase(v.begin() + v.size() - 1);
            return true;
        }
        return false;
    }
    
    int top()
    {
        if (v.empty())
            return -1;
        
        return v[v.size() - 1].top();
    }
    
private:
    vector<stack<int>> v;
    int m_Capacity;
};
```

### 3.4
```
class MyQueue
{
public:
    void push(int i)
    {
        while (!tmp.empty())
        {
            s.push(tmp.top());
            tmp.pop();
        }
        
        s.push(i);
    }
    
    bool pop()
    {
        while (!s.empty())
        {
            tmp.push(s.top());
            s.pop();
        }
        
        if (!tmp.empty())
        {
            tmp.pop();
            return true;
        }
        return false;
    }
    
    int front()
    {
        while (!s.empty())
        {
            tmp.push(s.top());
            s.pop();
        }
        
        if (!tmp.empty())
        {
            return tmp.top();
        }
        
        return -1;
    }
    
private:
    stack<int> s;
    stack<int> tmp;
};
```

### 3.5
```
void f(stack<int>& s)
{
    stack<int> tmp1;
    stack<int> tmp2;
    while (!s.empty())
    {
        int i = s.top();
        s.pop();
        
        while (!tmp1.empty() && i < tmp1.top())
        {
            tmp2.push(tmp1.top());
            tmp1.pop();
        }
        
        while (!tmp2.empty() && i > tmp2.top())
        {
            tmp1.push(tmp2.top());
            tmp2.pop();
        }
        
        tmp1.push(i);
    }
    
    while (!tmp2.empty())
    {
        tmp1.push(tmp2.top());
        tmp2.pop();
    }
    
    while (!tmp1.empty())
    {
        s.push(tmp1.top());
        tmp1.pop();
    }
}
```

```
void f(stack<int>& s)
{
    stack<int> tmp;
    while (!s.empty())
    {
        int i = s.top();
        s.pop();
        
        int count = 0;
        while (!tmp.empty() && i < tmp.top())
        {
            s.push(tmp.top());
            tmp.pop();
            count++;
        }
        
        tmp.push(i);
        
        while (count-- > 0)
        {
            tmp.push(s.top());
            s.pop();
        }
    }
    
    while (!tmp.empty())
    {
        s.push(tmp.top());
        tmp.pop();
    }
}
```

### 3.6
```
class Animal {
public:
    virtual void setOrder(int order)
    {
        m_Order = order;     
    }
    
    virtual int getOrder()
    {
        return m_Order;
    }
private:
    int m_Order;
};

class Dog: public Animal { };

class Cat: public Animal { };

class Shelter{
public:
    void enqueue(Animal* a)
    {
        if (Dog* d = dynamic_cast<Dog*>(a))
        {
            d->setOrder(order++);
            dog_list.push_back(d);
        }
        else if (Cat* c = dynamic_cast<Cat*>(a))
        {
            c->setOrder(order++);
            cat_list.push_back(c);
        }
    }
    
    Animal* dequeueAny()
    {
        if (dog_list.empty() && cat_list.empty())
            return NULL;
        
        Animal* a;
        if (cat_list.empty() 
            || (!dog_list.empty() && dog_list.front()->getOrder() < cat_list.front()->getOrder()))
        {
            a = dynamic_cast<Animal*>(dog_list.front());
            dog_list.pop_front();
        }
        else
        {
            a = dynamic_cast<Animal*>(cat_list.front());
            cat_list.pop_front();
        }
        
        return a;
    }
    
    Dog* dequeueDog()
    {
        if (dog_list.empty())
            return NULL;
        
        Dog* d = dog_list.front();
        dog_list.pop_front();
        return d;
    }
    
    Cat* dequeueCat()
    {
        if (cat_list.empty())
            return NULL;
        
        Cat* c = cat_list.front();
        cat_list.pop_front();
        return c; 
    }
private:
    static int order;
    list<Dog*> dog_list;
    list<Cat*> cat_list;
};

int Shelter::order = 0;
```
