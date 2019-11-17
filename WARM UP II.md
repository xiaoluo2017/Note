### 1. binary search
* binary search
```
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
* closest target value && <= target
```
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
* closest target value >= target
```
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
* closest target value
```
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

// inorder
void f(TreeNode* root)
{
    if (root == NULL) return;

    f(root->left);
    cout << root->val << " ";
    f(root->right);
}

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
