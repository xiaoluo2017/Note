### 4.1
```
bool helper(ListNode* node1, ListNode* node2)
{
    unordered_set<ListNode*> s;
    queue<ListNode*> q;
    q.push(node1);
    while (!q.empty())
    {
        ListNode* curr = q.front();
        q.pop();
        
        if (curr->next != NULL)
        {
            if (curr == node2)
                return true;
            
            if (s.find(curr->next) == s.end())
            {
                q.push(curr->next);
                s.insert(curr->next);
            } 
        }
    }
    return false;
}

bool f(ListNode* node1, ListNode* node2)
{
    return helper(node1, node2) || helper(node2, node1);
}
```

### 4.2
```
TreeNode* helper(vector<int> v, int start, int end)
{
    if (start > end)
        return NULL;
    
    if (start == end)
        return new TreeNode(v[start]);
    
    int mid = (start + end) / 2;
    TreeNode* root = new TreeNode(v[mid]);
    root->left = helper(v, start, mid - 1);
    root->right = helper(v, mid + 1, end);
    return root;
}

TreeNode* f(vector<int> v)
{
    return helper(v, 0, v.size() - 1);   
}
```

### 4.3
```
vector<ListNode*>* f(TreeNode* root)
{
    if (root == NULL)
        return new vector<ListNode*>();
    
    queue<TreeNode*> q;
    q.push(root);
    vector<ListNode*>* v = new vector<ListNode*>();;
    
    while (!q.empty())
    {
        int count = q.size();
        ListNode* head = NULL;
        
        while (count-- > 0)
        {
            TreeNode* curr = q.front();
            q.pop();
            
            ListNode* tmp = head;
            head = new ListNode(curr->val);
            head->next = tmp;
            
            if (curr->right != NULL) q.push(curr->right);
            if (curr->left != NULL) q.push(curr->left);
        }
        v->push_back(head);
    }
    
    return v;
}
```

### 4.4
```
int helper(TreeNode* root)
{
    if (root == NULL)
        return 0;
    
    int le = helper(root->left);
    int ri = helper(root->right);
    
    if (le - ri > 1 || le - ri < -1)
        return -1;
    
    return le >= ri ? le + 1 : ri + 1;
}

bool f(TreeNode* root)
{
    return helper(root) != -1;
}
```

### 4.5
```
bool f(TreeNode* root)
{
    if (root == NULL)
        return true;
    
    if (root->left != NULL && root->left->val > root->val)
        return false;
    
    if (root->right != NULL && root->right->val <= root->val)
        return false;
    
    return f(root->left) && f(root->right);
}
```

### 4.6
```
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

TreeNode* f(TreeNode* node)
{
    if (node->right != NULL)
        return node->right;
        
    TreeNode* parent = node->parent;   
    TreeNode* child = node;
    
    while (parent != NULL)
    {
        if (parent->left == child)
            return parent;
        
        child = parent;
        parent = parent->parent;
    }
    
    return NULL;
}
```

### 4.7
```
vector<int>* f(vector<int> projects, vector<pair<int, int>> dependencies)
{
    unordered_map<int, int> indegree;
    unordered_map<int, vector<int>> m;
    for (pair<int, int> dependency : dependencies)
    {
        if (indegree.find(dependency.second) == indegree.end())
            indegree[dependency.second] = 1;
        else
            indegree[dependency.second]++;

        
        if (m.find(dependency.first) == m.end())
        {
            vector<int> v{dependency.second};
            m[dependency.first] = v;
        }
        else
            m[dependency.first].push_back(dependency.second);
        
    }
    
    queue<int> q;
    for (int project : projects)
        if (indegree.find(project) == indegree.end())
            q.push(project);

    vector<int>* res = new vector<int>();
    while (!q.empty())
    {
        int project = q.front();
        res->push_back(project);
        q.pop();
        vector<int> v = m[project];
        for (int i : v)
        {
            if (--indegree[i] == 0)
            {
                q.push(i);
                indegree.erase(i);
            }
        }
    }
    
    return res->size() == projects.size() ? res : new vector<int>();
}
```

### 4.8 
```
TreeNode* f(TreeNode* root, TreeNode* node1, TreeNode* node2)
{
    if (root == NULL || root == node1 || root == node2)
        return root;
    
    TreeNode* le = f(root->left, node1, node2);
    TreeNode* ri = f(root->right, node1, node2);
    
    if (le != NULL && ri != NULL)
    {
        return root;
    }
    else if (le == NULL) 
    {
        return ri;
    }
    else 
    {
        return le;
    }
}
```

### 4.9
```
void helper(vector<TreeNode*> res, vector<TreeNode*> v, vector<bool> isVisited)
{   
    if (res.size() == v.size())
    {
        for (TreeNode* node : res)
        {
           cout << node->val << " "; 
        }
        cout << endl;
        return;
    }
    
    for (int i = 0; i < v.size(); i++)
    {
        if (isVisited.size() == i)
            isVisited.push_back(false);
        
        if (!isVisited[i])
        {
            TreeNode* curr = v[i];
            res.push_back(curr);
            
            if (curr->left != NULL)
                v.push_back(curr->left);
        
            if (curr->right != NULL)
                v.push_back(curr->right);

            isVisited[i] = true;
            helper(res, v, isVisited);
            isVisited[i] = false;
            
            if (curr->left != NULL)
                v.erase(v.end() - 1);
        
            if (curr->right != NULL)
                v.erase(v.end() - 1);
            
            res.erase(res.end() - 1);
        }
    }
}

void f(TreeNode* root)
{
    if (root == NULL) return;
    
    vector<TreeNode*> res;
    vector<TreeNode*> v{root};
    vector<bool> isVisited;
    helper(res, v, isVisited);
}
```

### 4.10
```
bool helper(TreeNode* T1, TreeNode* T2)
{   
    if (T1 == NULL && T2 == NULL)
        return true;
    
    if (T1 == NULL || T2 == NULL || T1->val != T2->val)
        return false;
    
    return helper(T1->left, T2->left) && helper(T1->right, T2->right);
}

bool f(TreeNode* T1, TreeNode* T2)
{
    if (T1 == NULL) return false;
    
    if (helper(T1, T2)) return true;
    
    return helper(T1->left, T2) || helper(T1->right, T2);
}
```

### 4.11
```
struct TreeNode
{
    int val;
    int count;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), count(1), left(NULL), right(NULL) {}
};

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
        
        root->count++; 
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
        
        root->count--;
        
        return root;
    }
    
    void remove(int val)
    {
        if (search(val))
            root = remove(root, val);
    }
    
    TreeNode* getRandomNode(TreeNode* root)
    {
        int residue = rand() % root->count;
        
        if (residue == 0)
            return root;
            
        if (root->left == NULL || residue > root->left->count)
            return getRandomNode(root->right);
        
        return getRandomNode(root->left);
    }
    
    TreeNode* getRandomNode()
    {
        if (root == NULL)
            return NULL;
        
        return getRandomNode(root);
    }

private:
    TreeNode* root;
};
```

### 4.12
```
unordered_map<int, int> helper(TreeNode* root, int target, int* count)
{
    if (root == NULL)
    {
        unordered_map<int, int> tmp;
        return tmp;
    }
        
    int val = root->val;
    unordered_map<int, int> le = helper(root->left, target, count);
    unordered_map<int, int> ri = helper(root->right, target, count);

    unordered_map<int, int> m;
    for (std::unordered_map<int, int>::iterator it = le.begin(); it != le.end(); it++)
        m[it->first + val] = it->second;
        
    for (std::unordered_map<int, int>::iterator it = ri.begin(); it != ri.end(); it++)
    {
        if (m.find(it->first + val) == m.end())
            m[it->first + val] = it->second;
        else
            m[it->first + val] += it->second;
    }
        
    if (m.find(val) == m.end())
        m[val] = 1;
    else
        m[val]++;
    
    if (m.find(target) != m.end()) *count += m[target];
    
    return m;
}

int f(TreeNode* root, int target)
{
    int count = 0;
    helper(root, target, &count);
    return count;
}
```
