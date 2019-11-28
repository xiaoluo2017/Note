### 10.1
```
void f(int A[], int B[], int m, int n)
{
    int p1 = m - 1, p2 = n - 1;
    while (p1 >= 0 && p2 >= 0)
    {
        if (A[p1] > B[p2])
        {
            A[p1 + p2 + 1] = A[p1];
            p1--;
        }
        else
        {
            A[p1 + p2 + 1] = B[p2];
            p2--;
        }
    }
    
    while (p2 >= 0)
    {
        A[p2] = B[p2];
        p2--;
    }
}
```

### 10.2
```
string trans(string s)
{
    int hash[256] = {0};
    for (char c: s)
    {
        hash[c]++;
    }
    
    string res = "";
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < hash[i]; j++)
        {
            res += (char)i;
        }
    }
    return res;
}

void f(vector<string>& v)
{
    sort(v.begin(), v.end(), [ ]( const string& s1, const string& s2)
    {
        return trans(s1) < trans(s2);
    });
}
```

```
bool isAnagram(string s1, string s2)
{
    if (s1.size() != s2.size()) return false;
    
    int hash[256] = {0};
    for (char c: s1)
        hash[c]++;
    
    for (char c: s2)
        if (hash[c]-- == 0)
            return false;
    
    return true;
}

void f(vector<string>& v)
{
    int le = 0, ri = 1;
    while (le < v.size())
    {
        for (int i = le + 1; i < v.size(); i++)
        {
            if (isAnagram(v[i], v[le]))
            {
                string tmp = v[ri];
                v[ri++] = v[i];
                v[i] = tmp;
            }
        }
        le = ri;
        ri = le + 1;
    }
}
```
