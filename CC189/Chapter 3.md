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
