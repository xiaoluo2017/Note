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
