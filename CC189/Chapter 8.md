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
void helper(vector<vector<int>>& matrix, vector<pair<int, int>>& res, int m, int n, int r, int c)
{
    if (res.size() == r + c - 1)
        return;
    
    if (m >= r || n >= c || matrix[m][n] == 1)
        return;
    
    res.push_back(make_pair(m, n));
    helper(matrix, res, m + 1, n, r, c);
    helper(matrix, res, m, n + 1, r, c);
    if (res.size() < r + c - 1) res.erase(res.end() - 1);
}

void f(vector<vector<int>>& matrix, vector<pair<int, int>>& res)
{
    if (matrix.size() == 0 || matrix[0].size() == 0) 
        return;
    
    helper(matrix, res, 0, 0, matrix.size(), matrix[0].size());
}
```
