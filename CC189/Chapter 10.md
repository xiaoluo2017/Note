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

### 10.9
```
pair<int, int> helper(vector<vector<int>>& matrix, int target, int m1, int n1, int m2, int n2)
{
    if (m1 > m2 || n1 > n2) return make_pair(-1, -1);
    int mc = (m1 + m2) / 2, nc = (n1 + n2) / 2;
    pair<int, int> res;
    if (matrix[mc][nc] == target) 
    {
        return make_pair(mc, nc);
    }
    else if (matrix[mc][nc] < target)
    {
        res = helper(matrix, target, mc + 1, nc + 1, m2, n2);
        if (res == make_pair(-1, -1)) res = helper(matrix, target, mc + 1, n1, m2, nc + 1);
        if (res == make_pair(-1, -1)) res = helper(matrix, target, m1, nc + 1, mc + 1, n2);
    }
    else
    {
        res = helper(matrix, target, m1, n1, mc - 1, nc - 1);
        if (res == make_pair(-1, -1)) res = helper(matrix, target, mc - 1, n1, m2, nc - 1);
        if (res == make_pair(-1, -1)) res = helper(matrix, target, m1, nc - 1, mc - 1, n2);
    }
    
    return res;
}

pair<int, int> f(vector<vector<int>>& matrix, int target)
{
    if (matrix.size() == 0 || matrix[0].size() == 0) return make_pair(-1, -1);
        
    return helper(matrix, target, 0, 0, matrix.size() - 1, matrix[0].size() - 1);
}
```

### 10.10
```
struct TreeNode
{
    int val;
    int count;
    int rank;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int v, int r) : val(v), count(1), rank(r), left(NULL), right(NULL) {}
};

class BST
{
public:
    BST(): root(NULL) {}
    
    int search(int val)
    {
        if (root == NULL) return 0;
        
        int res = search(root, val);
        if (res == -1)
        {
            TreeNode* node = root;
            while (node->right != NULL)
            {
                node = node->right;
            }
            return node->count + node->rank;
        }
        return res;
    }
    
    int search(TreeNode* root, int val)
    {
        if (root == NULL)
            return -1;
            
        if (val == root->val)
        {
            return root->rank + root->count - 1;
        }
        else if (val < root->val)
        {
            int res = search(root->left, val);
            if (res == -1) res = root->rank;
            return res;
        }
        else
        {
            return search(root->right, val);
        }
    }
    
    TreeNode* insert(TreeNode* root, int val, int rank)
    {
        if (root == NULL)
            return new TreeNode(val, rank);
        
        if (val == root->val)
        {
            root->count++;
            updateRank(root->left);
            updateRank(root->right);
            return root;
        }
        else if (val < root->val)
        {
            root->left = insert(root->left, val, rank);
            root->rank++;
            updateRank(root->right);
        }
        else
        {
            rank = root->count + root->rank;
            root->right = insert(root->right, val, rank);
        }

        return root;
    }
    
    void insert(int val)
    {
        if (root == NULL)
        {
            root = new TreeNode(val, 0);
            return;
        }
        
        int rank = 0;
        insert(root, val, rank);
    }


    void updateRank(TreeNode* root)
    {
        if (root == NULL) return;
        
        root->rank++;
        updateRank(root->left);
        updateRank(root->right);
    }
private:
    TreeNode* root;
};

class Solution
{
public:
    void track(int x)
    {
        b.insert(x); 
    }
    
    int getRankOfNumber(int x)
    {
        return b.search(x);
    }
private:  
    BST b;
};
```

### 10.11
```
void f(vector<int>& v)
{
    vector<int> tmp = v;
    sort(tmp.begin(), tmp.end());
    for (int i = 1; i < v.size(); i += 2)
    {
        v[i] = tmp[i / 2];
    }
    
    for (int i = 0; i < v.size(); i += 2)
    {
        v[i] = tmp[(v.size() + i) / 2];
    }
}
```

```
void f(vector<int>& v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        if (i % 2 == 0)
        {
            if (v[i] < v[i + 1])
            {
                int tmp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tmp;
            }
        }
        else
        {
            if (v[i] > v[i + 1])
            {
                int tmp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tmp;
            }
        }
    }
}
```
