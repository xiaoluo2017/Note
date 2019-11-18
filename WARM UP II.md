### 1. binary search
```
// binary search
int f(vector<int> v, int target)
{
    int le = 0, ri = v.size() - 1;
    while (le <= ri)
    {
        int mid = (le + ri) / 2;
        if (v[mid] == target)
        {
            return mid;
        }
        else if (v[mid] < target)
        {
            le = mid + 1;
        }
        else
        {
            ri = mid - 1;
        }
    }
    return -1;
}
```

```
// closest target value && <= target
int f(vector<int> v, int target)
{
    int le = 0, ri = v.size() - 1;
    while (le <= ri)
    {
        int mid = (le + ri) / 2;
        if (v[mid] > target)
        {
            ri = mid - 1;
        }
        else
        {
            le = mid + 1;
        }
    }
    return ri;
}
```

```
// closest target value >= target
int f(vector<int> v, int target)
{
    int le = 0, ri = v.size() - 1;
    while (le <= ri)
    {
        int mid = (le + ri) / 2;
        if (v[mid] < target)
        {
            le = mid + 1;
        }
        else
        {
            ri = mid - 1;
        }
    }
    return le <= v.size() - 1 ? le : -1;
}
```

```
// closest target value
int f(vector<int> v, int target)
{
    int le = 0, ri = v.size() - 1;
    while (le <= ri)
    {
        int mid = (le + ri) / 2;
        if (v[mid] > target)
        {
            ri = mid - 1;
        }
        else
        {
            le = mid + 1;
        }
    }
    
    if (ri == -1)
        return le;
    
    if (le == v.size())
        return ri;
    
    return target - v[ri] < v[le] - target ? ri : le;
}
```

### 2. Tree Traversals(Inorder Preorder Postorder)
* recursive
```
// preorder
void f(TreeNode* root)
{
    if (root == NULL) return;
    
    cout << root->val << " ";
    f(root->left);
    f(root->right);
}
```

```
// inorder
void f(TreeNode* root)
{
    if (root == NULL) return;

    f(root->left);
    cout << root->val << " ";
    f(root->right);
}
```

```
// postorder
void f(TreeNode* root)
{
    if (root == NULL) return;
    
    f(root->left);
    f(root->right);
    cout << root->val << " ";
}
```

* iterative
```
// preorder
void f(TreeNode* root)
{
    if (root == NULL) return;
    
    stack<TreeNode*> s;
    s.push(root);
    
    while (!s.empty())
    {
        root = s.top();
        s.pop();
        
        while (root != NULL)
        {
            cout << root->val << " ";
            if (root->right) s.push(root->right);
            root = root->left;
        }
    }
}

void f(TreeNode* root)
{
    if (root == NULL) return;
    
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty())
    {
        root = s.top();
        s.pop();
        cout << root->val << " ";
        
        if (root->right) s.push(root->right);
        if (root->left) s.push(root->left);
    }
}
```

```
// inorder
void f(TreeNode* root)
{
    stack<TreeNode*> s;
    while (root != NULL || !s.empty())
    {
        while (root != NULL)
        {
            s.push(root);
            root = root->left;
        }
        
        root = s.top();
        s.pop();
        cout << root->val << " ";
        root = root->right;
    }
}

void f(TreeNode* root)
{
    stack<TreeNode*> s;
    while (root != NULL || !s.empty())
    {
        if (root != NULL)
        {
            s.push(root);
            root = root->left;
        }
        else
        {
            root = s.top();
            s.pop();
            cout << root->val << " ";
            root = root->right;
        }
    }
}
```

```
// postorder
void f(TreeNode* root)
{
    stack<TreeNode*> s;
    TreeNode* pre = NULL;
    while (root != NULL || !s.empty())
    {
        while (root != NULL)
        {
            s.push(root);
            root = root->left;
        }
        root = s.top();
        if (root->right == NULL || root->right == pre)
        {
            s.pop();
            cout << root->val << " ";
            pre = root;
            root = NULL;
        }
        else{
            root = root->right;
        }
    }
}

void f(TreeNode* root)
{
    stack<TreeNode*> s;
    TreeNode* pre = NULL;
    while (root != NULL || !s.empty())
    {
        if (root != NULL)
        {
            s.push(root);
            root = root->left;
        }
        else
        {
            root = s.top();
            if (root->right == NULL || root->right == pre)
            {
                s.pop();
                cout << root->val << " ";
                pre = root;
                root = NULL;
            }
            else{
                root = root->right;
            }
        }
    }
}
```

### 3. quick sort/heap sort/merge sort
```
// quick sort
void f(vector<int>& v, int start, int end)
{
    if (start >= end) return;
    
    int pivot = start;
    int le = start + 1;
    int ri = end;
    
    while (le < ri)
    {
        if (v[le] <= v[pivot])
        {
            le++;
        }
        else
        {
            int tmp = v[le];
            v[le] = v[ri];
            v[ri--] = tmp;
        }
    }
    
    if (v[le] > v[pivot]) le--;
    
    int tmp = v[le];
    v[le] = v[pivot];
    v[pivot] = tmp;
    
    f(v, start, le - 1);
    f(v, le + 1, end);
}
```

```
// merge sort
void f(vector<int>& v, int start, int end)
{
    if (start == end)
        return;

    int mid = (start + end) / 2;
    f(v, start, mid);
    f(v, mid + 1, end);

    vector<int> tmp;
    for (int i = start; i <= end; i++)
        tmp.push_back(v[i]);
    
    int le = 0, ri = mid + 1 - start, index = start;
    
    while (le <= mid - start && ri <= end - start)
    {
        if (tmp[le] <= tmp[ri])
        {
            v[index++] = tmp[le++];
        }
        else
        {
            v[index++] = tmp[ri++];
        }
    }
    
    while (le <= mid - start)
    {
        v[index++] = tmp[le++];
    }
    
    while (ri <= end - start)
    {
        v[index++] = tmp[ri++];
    }
}
```

```
// heap sort
void swap(vector<int>& v, int le, int ri)
{
    int tmp = v[le];
    v[le] = v[ri];
    v[ri] = tmp;
}

void heapify(vector<int>& v, int i, int end)
{
    int le = 2 * i + 1, ri = 2 * i + 2, index = i;
    
    if (le <= end && v[index] < v[le])
    {
        index = le;
    }
    
    if (ri <= end && v[index] < v[ri])
    {
        index = ri;
    }
    
    if (index != i)
    {
        swap(v, i, index);
        heapify(v, index, end);
    }
}

void heapSort(vector<int>& v)
{
    for (int i = (v.size() - 2) / 2; i >= 0; i--)
        heapify(v, i, v.size() - 1);
    
    for (int i = v.size() - 1; i > 0; i--)
    {
        swap(v, 0, i);
        heapify(v, 0, i - 1); 
    }
}
```

### 4. binary search tree
* iterative
```
class BST
{
public:
    BST(): root(NULL) {}
    
    bool search(int val)
    {
        TreeNode* curr = root;
        while (curr != NULL)
        {
            if (val == curr->val)
            {
                return true;
            }
            else if (val < curr->val)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        return false;
    }
    
    void insert(int val)
    {
        if (root == NULL)
        {
            root = new TreeNode(val);
            return;
        }
        
        TreeNode* curr = root;
        while (curr != NULL)
        {
            if (val <= curr->val)
            {
                if (curr->left == NULL)
                {
                    curr->left = new TreeNode(val);
                    break;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {    
                if (curr->right == NULL)
                {
                    curr->right = new TreeNode(val);
                    break;
                }
                else
                {
                    curr = curr->right;
                }
                
            }
        }
    }
    
    void remove(int val)
    {
        TreeNode* curr = root;
        TreeNode* prev = NULL;
        while (curr != NULL)
        {
            if (val == curr->val)
            {
                if (curr->left == NULL)
                {
                    if (prev == NULL)
                    {
                        root = root->right;
                    }
                    else if (curr->val <= prev->val)
                    {
                        prev->left = curr->right;
                    }
                    else
                    {
                        prev->right = curr->right;
                    }
                    return; 
                }
                
                if (curr->right == NULL)
                {
                    if (prev == NULL)
                    {
                        root = root->left;
                    }
                    else if (curr->val <= prev->val)
                    {
                        prev->left = curr->left;
                    }
                    else
                    {
                        prev->right = curr->left;  
                    }
                    return; 
                }
                
                TreeNode* tmp = curr->right;
                TreeNode* tmpPrev = curr;
                while (tmp->left != NULL)
                {
                    tmpPrev = tmp;
                    tmp = tmp->left;
                }                
                if (tmpPrev != curr) tmpPrev->left = NULL;
                if (curr->val <= prev->val)
                {
                    prev->left = tmp;
                }
                else
                {
                    prev->right = tmp;
                }
                tmp->left = curr->left;
                if (curr->right != tmp) tmp->right = curr->right;
                curr->left = NULL;
                curr->right = NULL;
                return;
            }
            else if (val < curr->val)
            {
                prev = curr;
                curr = curr->left;
            }
            else
            {
                prev = curr;
                curr = curr->right;
            }
        }
    }    
    
private:
    TreeNode* root;
};
```

* recursive
```
class BST
{
public:
    BST(): root(NULL) {}
    
    bool search(int val)
    {
        return search(root, val);
    }
    
    bool search(TreeNode* root, int val)
    {
        if (root == NULL)
            return false;
            
        if (val == root->val)
            return true;
        else if (val <= root->val)
            return search(root->left, val); 
        else
            return search(root->right, val);
    }
    
    TreeNode* insert(TreeNode* root, int val)
    {
        if (root == NULL)
            return new TreeNode(val);
        
        if (val <= root->val)
            root->left = insert(root->left, val);
        else
            root->right = insert(root->right, val);
        
        return root;
    }
    
    void insert(int val)
    {
        if (root == NULL)
        {
            root = new TreeNode(val);
            return;
        }
        
        insert(root, val);
    }
    
    TreeNode* remove(TreeNode* root, int val)
    {
        if (root == NULL)
            return NULL;
        
        if (val == root->val)
        {
            if (root->left == NULL)
            {
                return root->right;
            }
            else if (root->right == NULL)
            {
                return root->left;
            }
            else
            {
                TreeNode* tmp = root->right;
                while (tmp->left != NULL)
                {
                    tmp = tmp->left;
                }
                root->val = tmp->val;
                tmp->val = val;
                
                root->right = remove(root->right, val);
            }
        }
        else if (val < root->val)
        {
            root->left = remove(root->left, val);
        }
        else
        {
            root->right = remove(root->right, val);
        }
        
        return root;
    }
    
    void remove(int val)
    {
        root = remove(root, val);
    }

private:
    TreeNode* root;
};
```
