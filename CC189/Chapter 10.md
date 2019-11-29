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

### 10.3
```
// assume no duplicate
int helper(vector<int> v, int target, int le, int ri)
{
    if (le > ri) return -1;
    
    int mid = (le + ri) / 2, res = -1;
    if (v[mid] > v[ri])
    {
        if (v[mid] == target)
        {
            return mid;
        }
        else if (v[mid] < target)
        {
            res = helper(v, target, mid + 1, ri); 
        }
        else
        {
            res = helper(v, target, le, mid - 1); 
            if (res == -1) res = helper(v, target, mid + 1, ri);
        }
    }
    else // v[mid] <= v[ri]
    {
        if (v[mid] == target)
        {
            return mid;
        }
        else if (v[mid] > target)
        {
            res = helper(v, target, le, mid - 1); 
        }
        else
        {
            res = helper(v, target, le, mid - 1); 
            if (res == -1) res = helper(v, target, mid + 1, ri); 
        }
    }
    
    return res;
}

int f(vector<int> v, int target)
{
    return helper(v, target, 0, v.size() - 1);
}
```

```
// duplicate exists
bool helper(vector<int>& v, int target, int le, int ri)
{
    if (le > ri) return false;
    
    int mid = (le + ri) / 2;
    if (v[mid] == target)
    {
        return true;
    }
    
    if (v[mid] > v[ri] && v[mid] < target)
    {
        return helper(v, target, mid + 1, ri); 
    }
    else if (v[mid] < v[ri] && v[mid] > target)
    {
        return helper(v, target, le, mid - 1); 
    }
    
    return helper(v, target, le, mid - 1) || helper(v, target, mid + 1, ri);
}

bool f(vector<int>& v, int target)
{
    return helper(v, target, 0, v.size() - 1);
}
```

### 10.4
```
class Listy
{
public:
    int elementAt(int i)
    {
        if (i >= v.size()) return -1;
        return v[i];
    }
private:
    vector<int> v{0, 1, 2, 3, 6, 7, 8};
};

bool helper(Listy& l, int target, int le, int ri)
{
    if (le > ri) return false;
    
    int mid = (le + ri) / 2;
    if (l.elementAt(mid) == target) return true;
    
    if (l.elementAt(mid) == -1 || l.elementAt(mid) > target)
    {
        return helper(l, target, le, mid - 1);
    }
    else
    {
        return helper(l, target, mid + 1, ri * 2);
    }
}

bool f(Listy& l, int target)
{
    return helper(l, target, 0, 1);
}
```

```
bool helper(Listy& l, int target, int le, int ri)
{
    if (le > ri) return false;
    
    int mid = (le + ri) / 2;
    if (l.elementAt(mid) == target) return true;
    
    if (l.elementAt(mid) == -1 || l.elementAt(mid) > target)
    {
        return helper(l, target, le, mid - 1);
    }
    else
    {
        return helper(l, target, mid + 1, ri);
    }
}

bool f(Listy& l, int target)
{
    int ri = 1;
    while (l.elementAt(ri) != -1 && l.elementAt(ri) < target) ri = ri * 2;
    
    return helper(l, target, ri / 2, ri);
}
```

### 10.5
```
int helper(vector<string>& v, string target, int le, int ri)
{
    if (le > ri) return -1;
    
    int mid = (le + ri) / 2;
    if (v[mid] == target) return mid;
    
    if (v[mid] != "" && v[mid] < target)
    {
        return helper(v, target, mid + 1, ri);
    }
    else if (v[mid] != "" && v[mid] > target)
    {
        return helper(v, target, le, mid - 1);
    }
    
    int res = helper(v, target, mid + 1, ri);
    if (res == -1) res = helper(v, target, le, mid - 1);
    
    return res;
}

int f(vector<string>& v, string target)
{
    return helper(v, target, 0, v.size() - 1);
}
```

```
int helper(vector<string>& v, string target, int le, int ri)
{
    if (le > ri) return -1;
    
    int mid = (le + ri) / 2;

    if (v[mid] == "")
    {
        int m1 = mid - 1, m2 = mid + 1;
        while (m1 >= le || m2 <= ri)
        {
            if (m1 >= le && v[m1] != "") {
                mid = m1;
                break;
            }
            if (m2 <= ri && v[m2] != "") {
                mid = m2;
                break;
            }
            
            m1--;
            m2++;
        }
        if (m1 < le && m2 > ri) return -1;
    }
    
    if (v[mid] == target) 
    {
        return mid;
    }
    else if (v[mid] < target)
    {
        return helper(v, target, mid + 1, ri);
    }
    else // v[mid] > target
    {
        return helper(v, target, le, mid - 1);
    }
}

int f(vector<string>& v, string target)
{
    return helper(v, target, 0, v.size() - 1);
}
```

### 10.8
```
vector<int> f(vector<int>& v)
{
    vector<int> bitV(1000, 0);
    int max = 0;
    for (int i : v)
    {
        max = max > i ? max : i;
        int index = (i - 1) / 32, offset = (i - 1) % 32;
        bitV[index] = bitV[index] ^ (1 << (31 - offset));
    }
    
    vector<int> res;
    for (int i = 0; i < bitV.size(); i++)
    {
        for (int j = 31; j >= 0; j--)
        {
            if (((bitV[i] >> j) & 1) == 0)
            {
                res.push_back(32 * i + 32 - j);
            }
            if (--max == 0) break;
        }
        if (max == 0) break;
    }
    
    return res;
}
```
