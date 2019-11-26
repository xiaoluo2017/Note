### 8.1
```
int f(int n)
{
    if (n <= 2) return n;
    
    int arr[n + 1] = {1, 1, 2};
    for (int i = 3; i <= n; i++)
    {   
        arr[i] = arr[i - 3] + arr[i - 2] + arr[i - 1];
    }
    
    return arr[n];
}
```

### *8.2
```
void helper(vector<vector<int>>& matrix, vector<pair<int, int>>& res, vector<vector<bool>>& isVisited, int m, int n, int r, int c)
{
    if (res.size() == r + c - 1)
        return;
    
    if (m >= r || n >= c || matrix[m][n] == 1 || isVisited[m][n])
        return;
    
    res.push_back(make_pair(m, n));
    isVisited[m][n] = true;
    helper(matrix, res, isVisited, m + 1, n, r, c);
    helper(matrix, res, isVisited, m, n + 1, r, c);
    if (res.size() < r + c - 1) res.erase(res.end() - 1);
}

void f(vector<vector<int>>& matrix, vector<pair<int, int>>& res)
{
    if (matrix.size() == 0 || matrix[0].size() == 0) 
        return;
    
    vector<bool> v(matrix[0].size(), 0);
    vector<vector<bool>> isVisited(matrix.size(), v);
    helper(matrix, res, isVisited, 0, 0, matrix.size(), matrix[0].size());
}
```

### 8.3
```
int helper(vector<int> v, int le, int ri)
{
    if (le > ri)
        return -1;
    
    int mid = (le + ri) / 2;
    if (v[mid] == mid)
    {
        return mid;
    }
    else if (v[mid] > mid)
    {
        return helper(v, le, mid - 1);
    }
    else
    {
        return helper(v, mid + 1, ri);
    }
}

int f(vector<int> v)
{
    return helper(v, 0, v.size() - 1);
}
```

```
int helper(vector<int> v, int le, int ri)
{
    if (le > ri)
        return -1;
    
    int mid = (le + ri) / 2, res = -1, tmp = -1;
    if (v[mid] == mid)
    {
        return mid;
    }
    else if (v[mid] > mid)
    {
        tmp = helper(v, le, mid - 1);
        res = tmp != -1 ? tmp : res;
        
        tmp = helper(v, v[mid], ri);
        res = tmp != -1 ? tmp : res;
    }
    else
    {
        tmp = helper(v, mid + 1, ri);
        res = tmp != -1 ? tmp : res;
        
        tmp = helper(v, le, v[mid]);
        res = tmp != -1 ? tmp : res;
    }
    
    return res;
}

int f(vector<int> v)
{
    return helper(v, 0, v.size() - 1);
}
```

### 8.4
```
void helper(vector<int>& v, vector<vector<int>>& res, vector<int>& tmp, int start)
{
    for (int i = start; i < v.size(); i++)
    {
        tmp.push_back(v[i]);
        res.push_back(tmp);
        helper(v, res, tmp, i + 1);
        tmp.pop_back();
    } 
}

vector<vector<int>> f(vector<int>& v)
{
    vector<vector<int>> res;
    vector<int> tmp;
    helper(v, res, tmp, 0);
    return res;
}
```

```
// subset II
void helper(vector<int>& v, vector<vector<int>>& res, vector<int>& tmp, vector<bool>& isVisited, int start)
{
    for (int i = start; i < v.size(); i++)
    {
        if (i > 0 && v[i] == v[i - 1] && !isVisited[i - 1])
        {
            continue;
        }
        
        tmp.push_back(v[i]);
        res.push_back(tmp);
        isVisited[i] = true;
        helper(v, res, tmp, isVisited, i + 1);
        isVisited[i] = false;
        tmp.pop_back();
    } 
}

vector<vector<int>> f(vector<int>& v)
{
    sort(v.begin(), v.end());
    vector<vector<int>> res;
    vector<int> tmp;
    vector<bool> isVisited(v.size(), false);
    helper(v, res, tmp, isVisited, 0);
    return res;
}
```
### 8.5
```
int helper(int i1, int i2, int num)
{
    if (i2 == 1) return i1 + num;
    
    int remainder = i2 % 2;
    i2 = i2 / 2;
    
    if (remainder == 1) num += i1;
    if (i2 != 0) i1 = i1 << 1;

    return helper(i1, i2, num);
}

int f(int i1, int i2)
{
    if (i1 < i2)
    {
        int tmp = i1;
        i1 = i2;
        i2 = tmp;
    }
    
    return helper(i1, i2, 0);
}
```

### 8.7
```
void helper(string& input, string& tmp, vector<string>& v, vector<bool>& isVisited)
{  
    if (tmp.size() == input.size())
    {
        v.push_back(tmp);
        return;
    }
    
    for (int i = 0; i < input.size(); i++)
    {
        if (!isVisited[i])
        {
            tmp += input[i];
            isVisited[i] = true;
            helper(input, tmp, v, isVisited);
            isVisited[i] = false;
            tmp = tmp.substr(0, tmp.size() - 1);
        }
    }
}

vector<string> f(string input)
{
    vector<string> v;
    vector<bool> isVisited(input.size(), false);
    string tmp = "";
    helper(input, tmp, v, isVisited);
    return v;
}
```

### 8.8
```
void helper(string& input, string& tmp, vector<string>& v, vector<bool>& isVisited)
{  
    if (tmp.size() == input.size())
    {
        v.push_back(tmp);
        return;
    }
    
    for (int i = 0; i < input.size(); i++)
    {
        if (i > 0 && input[i] == input[i - 1] && !isVisited[i - 1])
            continue;
        
        if (!isVisited[i])
        {
            tmp += input[i];
            isVisited[i] = true;
            helper(input, tmp, v, isVisited);
            isVisited[i] = false;
            tmp = tmp.substr(0, tmp.size() - 1);
        }
    }
}

vector<string> f(string input)
{
    vector<string> v;
    sort(input.begin(), input.end());
    vector<bool> isVisited(input.size(), false);
    string tmp = "";
    helper(input, tmp, v, isVisited);
    return v;
}
```

### 8.9
```
void helper(string& tmp, vector<string>& v, int le, int ri)
{  
    if (le == 0 && ri == 0)
        v.push_back(tmp);
    
    if (le > 0)
    {
        tmp += "(";
        helper(tmp, v, le - 1, ri);
        tmp = tmp.substr(0, tmp.size() - 1);
    }
    
    if (ri > 0 && le < ri)
    {
        tmp += ")";
        helper(tmp, v, le, ri - 1);
        tmp = tmp.substr(0, tmp.size() - 1);
    }
}

vector<string> f(int i)
{
    vector<string> v;
    string tmp = "";
    helper(tmp, v, i, i);
    return v;
}
```

### 8.10
```
void helper(vector<vector<int>>& matrix, int x, int y, int color, int orgColor)
{
    if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size())
        return;
    
    if (matrix[x][y] == orgColor)
    {
        matrix[x][y] = color;
        helper(matrix, x + 1, y, color, orgColor);
        helper(matrix, x - 1, y, color, orgColor);
        helper(matrix, x, y + 1, color, orgColor);
        helper(matrix, x, y - 1, color, orgColor);
    }
}

void f(vector<vector<int>>& matrix, int x, int y, int color)
{
    if (matrix.size() == 0 || matrix[0].size() == 0) 
        return;
    
    helper(matrix, x, y, color, matrix[x][y]);
}
```

### *8.11
```
int helper(int i, int pre)
{
    if (i == 0) return 1;
    if (i < 0) return 0;
    int count = 0;
    
    if (pre != 10 && pre != 5 && pre != 1) count += helper(i - 25, 25);
    if (pre != 5 && pre != 1) count += helper(i - 10, 10);
    if (pre != 1) count += helper(i - 5, 5);
    count += helper(i - 1, 1);
    
    return count;
}

int f(int i)
{
    return helper(i, 0);
}
```

```
int helper(int cents, int currency[], vector<int>& tmp) // , map<vector<int>, int>& m)
{ 
    if (cents < 0) return 0;
    if (cents == 0 || tmp[3] != 0) return 1;

    // if (m.find(tmp) != m.end())
    //    return m[tmp];
    
    int count = 0;
    
    for (int i = 0; i < 4; i++)
    {
        bool bCurrCurrency = true;
        for (int j = i + 1; j < 4; j++)
        {
            if (tmp[j] != 0){
                bCurrCurrency = false;
                break;
            }
                
        }
        
        if (bCurrCurrency)
        {
            tmp[i]++;
            count += helper(cents - currency[i], currency, tmp); // , m);
            tmp[i]--;
        }
            
    }
    
    // m[tmp] = count;
    return count;
}

int f(int cents)
{
    // map<vector<int>, int> m;
    vector<int> tmp(4, 0);
    int currency[] = {25, 10, 5, 1};
    return helper(cents, currency, tmp); // , m);
}
```
