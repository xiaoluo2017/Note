### 1.1
```
bool f(string s)
{
    int hash[256] = {0};

    for (char c : s)
        if (++hash[c] > 1) 
            return false;
    
    return true;
}
```

### 1.2
```
bool f(string s1, string s2)
{
    if (s1.size() != s2.size()) return false;
    
    int hash[256] = {0};
    for (char c: s1)
        hash[c]++;
    
    for (char c: s2)
        if (--hash[c] < 0)
            return false;
    
    return true;
}
```

### 1.3
```
string f(string s, int length)
{
    int i1 = length - 1, i2 = i1;
    for (int i = 0; i < length; i++)
        if (s[i] == ' ')
            i2 += 2;
    
    while (i1 >= 0 && i2 >= 0)
    {
        if (s[i1] == ' ')
        {
            s[i2--] = '0';
            s[i2--] = '2';
            s[i2--] = '%';
            i1--;
        }
        else
            s[i2--] = s[i1--];
    }

    return s;
}
```

### 1.4
```
bool f(string s)
{
    int hash[26] = {0};
    transform(s.begin(), s.end(), s.begin(), ::tolower); 
    for (char c : s)
    {
        if(c >= 'a' && c <= 'z')
            hash[c - 'a']++;
    }
    
    bool bHasMid = false;
    for (int i : hash)
    {
        if (i % 2 == 1)
        {
            if (bHasMid)
                return false;
            else
                bHasMid = true;
        }
    }
    
    return true;
}
```

### 1.5
```
bool f(string s1, string s2)
{
    if (s1.size() != s2.size() && s1.size() - s2.size() != 1 && s2.size() - s1.size() != 1)
        return false;
    
    if (s1.size() > s2.size())
    {
        string tmp = s1;
        s1 = s2;
        s2 = tmp;
    }
    
    if (s1.size() < s2.size())
    {
        int i1 = 0, i2 = 0;
        bool bInsert = false;
        while (i1 < s1.size() && i2 < s2.size())
        {
            if (s1[i1++] != s2[i2++])
            {
                if (bInsert)
                    return false;
                else
                {
                    bInsert = true;
                    i1--;
                }
            }
        }
    }
    
    if (s1.size() == s2.size())
    {
        int i1 = 0, i2 = 0;
        bool bReplace = false;
        while (i1 < s1.size() && i2 < s2.size())
        {
            if (s1[i1++] != s2[i2++])
            {
                if (bReplace)
                    return false;
                else
                {
                    bReplace = true;
                }
            }
        }
    }
    
    return true;
}
```

### 1.6
```
string f(string s)
{
    if (s.size() <= 1)
        return s;
    
    string res;
    char c = s[0];
    int num = 1;
    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] == s[i - 1])
        {
            num++;
        }
        else
        {
            res += c + std::to_string(num);
            c = s[i];
            num = 1;
        }
    }
    
    res += c + std::to_string(num);
    return s.size() <= res.size() ? s : res;
}
```

### *1.7
```
void f(int matrix[][4], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[N - 1 - j][N - 1 - i];
            matrix[N - 1 - j][N - 1 - i] = tmp;
        }
    }
    
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[N - 1 - i][j];
            matrix[N - 1 - i][j] = tmp;
        }
    }
}
```

### 1.8
```
void f(vector<vector<int>>& matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    vector<int> v1(m, 1), v2(n, 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0) 
            {
                v1[i] = 0;
                v2[j] = 0;
            } 
        }
    }

    for (int i = 0; i < m; i++)
        if (v1[i] == 0)
            for (int j = 0; j < n; j++)
                matrix[i][j] = 0;
            
    for (int j = 0; j < n; j++)
        if (v2[j] == 0)
            for (int i = 0; i < m; i++)
                matrix[i][j] = 0; 
}
```

### *1.9
```
bool isSubstring(string s1, string s2) 
{ 
    int M = s1.length(); 
    int N = s2.length(); 
  
    for (int i = 0; i <= N - M; i++) { 
        int j; 
  
        for (j = 0; j < M; j++) 
            if (s2[i + j] != s1[j]) 
                break; 
  
        if (j == M) 
            return true; 
    } 
  
    return false; 
} 

/* bool isRotation(string s1, string s2)
{
    if (s1.size() != s2.size())
        return false;
    
    int m = s1.size();
    bool res1 = false, res2 = false;
    
    for (int i = 0; i < s1.size(); i++)
    {
        if (isSubstring(s1.substr(0, i), s2) && isSubstring(s1.substr(i, m), s2))
        {
            res1 = true;
            break;
        }
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        if (isSubstring(s2.substr(0, i), s1) && isSubstring(s2.substr(i, m), s1))
        {
            res2 = true;
            break;
        }
    }
    
    return res1 && res2;
} */

bool isRotation(string s1, string s2)
{
    if (s1.size() != s2.size())
        return false;

    s2 = s2 + s2;
    return isSubstring(s1, s2);
}
```
