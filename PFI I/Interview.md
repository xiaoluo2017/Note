# Interview

## Amazon
### 1. OOD
* 设计自动售货机
    * Use Case
      * 显示饮料, 价格, 是否有货
      * 用户可以选择, 付款
    * 关键点: 自动售货机应添加初始化user方法, 传入user(todo: User类可能不需要)
    
```
class Machine
{
private:
    int state;
    unordered_map<string, item> items;
    Currency PricePaid;
    User currUser;

public:
    display();
    init(User u);
    checkPaid();
    GiveToUser();
    refund();
    getPrice(unordered_map<string, int> items);
    getter & setter
};

class Item
{
private:
    string name;
    double price;
    int count;
public:
    getter & setter
}

class User
{
private:
    int id;
    double price;
public:
    void select(map<string, int> items);
    void pay(map<Currency, int> money);
    void cancel();
};

class Currency
{
private:
    string name;
    double price;
public:
    getter & setter
};
```

### 2. 系统设计
* 中央管理系统, 管理多个自动售货机
    * Use Case
      * 判断售货机好坏
      * 判断售货机是否缺货, 如果是, 派人补货
      
### 3. 组介绍
* Group: FreeSearch
* service page: non-index, re-direct
* url: description, keyword
* secondary language
* Tools: Java, 大数据处理 eg. Tools on AWS(AWS EMR, S3, redshift)

## MicroSof
### 1. Phone interview
```
struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode(int v): left(NULL), right(NULL), val(v) {}
}

void serilizalition(TreeNode* root, string& str)
{
    if (root == NULL)
    {
        if (str != "") 
            str += "/";
            
        str += "n";
        return;
    }
    
    if (str != "") 
        str += "/";
    
    str += to_string(root.val); 
    serilizalition(root->left, str);
    serilizalition(root->right, str);
}

TreeNode* helper(vector<string>& v, int& i)
{
    TreeNode* root = NULL;
    if (v[i] != "n")
    {
        root.val = v[i];
        root->left = helper(v, ++i);
        root->right = helper(v, ++i);
    }
    return root;
}

TreeNode* deSerilizalition(string& str)
{
    std::string delimiter = "/";
    
    size_t pos = 0;
    std::string token;
    vector<string> v;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        v.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    
    int i = 0;
    return helper(v, i);
}
```

* follow-up:
    * recursive缺点
    * iterative写法
    * 时间/空间复杂度 for recursive & iterative
    
### 2. Onsite第一轮
```
bool solution(vector<vector<<int>>& matrix, int target)
{
    // assume m > 0 n > 0
    int m = matrix.size(), n = matrix[0].size();
    vector<int> tmp(m, 0); // subsum
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            tmp[j] = 0;
            
        for (int j = i; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                tmp[k] += matrix[k][j];
            }
            
            if (helper(tmp, target))
                return true;
        }
    }
    
    return false;
}

bool helper(vector<int>& input, int target)
{
    unordered_set<int> s;
    s.insert(0);
    int sum = 0;
    for (int& i : input)
    {
        sum += i;
        if (s.find(sum - target) != s.end())
        {
            return true;
        }
        
        s.insert(sum);
    }
    
    return false;
}
```

### 3. Onsite第二轮
```
int binarySearch(vector<int>& arr, int target)
{
    int le = 0, ri = arr.size() - 1;
    while (le <= ri)
    {
        int mid = (le + ri) / 2;
        if (arr[mid] < target)
        {
            le = mid + 1;
        }
        else
        {
            ri = mid - 1;
        }
    }
    
    return ri;
}

int solution(vector<int>& arr, int target)
{
    vector<int> subSum{0};
    int res = INT_MAX, currSum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        currSum += arr[i];
        int index = binarySearch(currSum - target);
        if (index != -1)
        {
            res = min(res, i - index + 1);
        }
        subSum.push_back(currSum);
    }
    
    return res == INT_MAX ? -1 : res;
}
```

* follow-up:
    * sync API function call: 2 thread + sendMessage
    * linux: shared memory + volatlie

### 4. Onsite第三轮
```
vector<string> solution(vector<string>& logs)
{
    unordered_map<string, pair<int, int>> m;
    for (string& log : logs)
    {
        stringstream ss(log);
        string token;
        vector<string> tmp;
        char delimiter = ',';
        while (getline(ss, token, delimiter))
        {
            tmp.push_back(token);
        }
        
        string API = tmp[2];
        int delay = stoi(tmp[3]);
        if (m.find(API) == m.end())
        {
            m[API] = pair(0, 0); //
        }
        
        if (delay > 100)
        {
            m[API].first++;
        }
        m[API].second++;
    }
    
    vector<string> res;
    double rate = 0;
    for (auto iter = m.begin(); iter != m.end(); iter++)
    {
        double currRate = (double)iter->second->first / iter->second->second; 
        if (rate == currRate)
        {
            res.push_back(iter->first);
        }
        else if (rate < currRate)
        {
            rate = currRate;
            res.clear();
            res.push_back(iter->first);
        }
    }
    
    return res;
}
```

* follow-up:
    * After deal, throw; folder TTL
    
### 5. Onsite第四轮
```
void helper(int k, int n, vector<int>& tmp, int& cnt, int start)
{   
    if (tmp.size() == k)
    {
        for (int& i : tmp)
        {
            cout << i << " ";
        }
        cout << endl;
        cnt++;
        return;
    }
    
    for (int i = start; i <= n; i++)
    {
        tmp.push_back(i);
        helper(k, n, tmp, cnt, i + 1);
        tmp.pop_back();
    }
}
```

* follow-up:
    * 实现一个锁
