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

### 8.2
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
