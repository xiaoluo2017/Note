### 2.1
```
void f(ListNode* head)
{
    if (head == NULL || head->next == NULL)
        return;
    
    unordered_set<int> set;
    ListNode* curr = head;
    set.insert(curr->val);
    
    while (curr->next != NULL)
    {
        if (set.find(curr->next->val) != set.end())
        {
            curr->next = curr->next->next;
        }
        else
        {
            curr = curr->next;
            set.insert(curr->val);
        }
    }
}
```

### 2.2
```
ListNode* f(ListNode* head, int K)
{
    if (head == NULL || head->next == NULL)
        return head;
    
    ListNode* curr = head;
    int length = 0;
    while (curr != NULL)
    {
        curr = curr->next;
        length++;
    }
    
    
    K = length - K % length;
    curr = head;
    for (int i = 0; i < K; i++)
        curr = curr->next;
    
    return curr;
}
```

### 2.3
```
void f(ListNode* node)
{
    ListNode* prev = NULL;
    while (node->next != NULL)
    {
        prev = node;
        node->val = node->next->val;
        node = node->next;
    }
    prev->next = NULL;
}
```

### 2.4
```
ListNode* f(ListNode* head, int val)
{
    ListNode* curr = head;
    ListNode* le = NULL;
    ListNode* ri = NULL;
    ListNode* mid = NULL;
    while (curr != NULL)
    {
        if (curr->val < val)
        {
            if (le == NULL)
            {
                le = curr;
                head = curr;
            }
            else
            {
                le->next = curr;
                le = le->next;
            }
        }
        else
        {
            if (ri == NULL)
            {
                ri = curr;
                mid = curr;
            }
            else
            {
                ri->next = curr;
                ri = ri->next;
            }
        }
        curr = curr->next;
    }
    
    if (le == NULL || ri == NULL) return head;
    
    ri->next = NULL;
    le->next = mid;
    
    return head;
}
```

### *2.5
```
ListNode* f(ListNode* node1, ListNode* node2)
{
    if (node1 == NULL)
        return node2;
    
    if (node2 == NULL)
        return node1;
    
    ListNode* res = node1;
    ListNode* prev = NULL;
    int carry = 0;
    while (node1 != NULL && node2 != NULL)
    {
        int sum = node1->val + node2->val + carry;
        node1->val = sum % 10;
        carry = sum / 10;
        prev = node1;
        node1 = node1->next;
        node2 = node2->next;
    }
    
    if (node2 != NULL)
    {
        prev->next = node2;
        node1 = node2;
    }
    
    while (node1 != NULL)
    {
        int sum = node1->val + carry;
        node1->val = sum % 10;
        carry = sum / 10;
        if (carry == 0) break;
        prev = node1;
        node1 = node1->next;
    }
    
    if (carry != 0)
        prev->next = new ListNode(carry);
    
    return res;
}
```

```
int helper(ListNode* node1, ListNode* node2, int length)
{
    if (node1 == NULL && node2 == NULL)
        return 0;
    
    int sum;
    if (length > 0)
    {
        sum = helper(node1->next, node2, length - 1) + node1->val;
    }
    else
    {
        sum = helper(node1->next, node2->next, length) + node1->val + node2->val;
    }
    
    node1->val = sum % 10;

    return sum / 10;
}

ListNode* f(ListNode* node1, ListNode* node2)
{
    if (node1 == NULL)
        return node2;
    
    if (node2 == NULL)
        return node1;
    
    ListNode* p1 = node1;
    ListNode* p2 = node2;
    while (p1 != NULL && p2 != NULL)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    
    if (p2 != NULL)
    {
        ListNode* tmp = node1;
        node1 = node2;
        node2 = tmp;
        p1 = p2;
    }
    
    int length = 0;
    while (p1 != NULL)
    {
        p1 = p1->next;
        length++;
    }
    
    int res = helper(node1, node2, length);
    
    if (res == 1)
    {
        ListNode* newNode = new ListNode(1);
        newNode->next = node1;
        return newNode;
    }
    else
    {
        return node1;
    }
}
```

### *2.6
```
ListNode* helper(ListNode* node1, ListNode* node2)
{
    if (node2 == NULL)
        return node1;
    
    node1 = helper(node1, node2->next);
    
    if (node1 == NULL || node1->val != node2->val)
        return NULL;
    
    if (node1->next != NULL) 
        node1 = node1->next;
    
    return node1;
}

bool f(ListNode* node)
{
    if (node == NULL) 
        return true;
    
    return helper(node, node) != NULL ? true : false;
}
```

```
bool helper(ListNode** node1, ListNode* node2)
{
    if (node2 == NULL)
        return true;
    
    bool res = helper(node1, node2->next);

    if ((*node1)->val != node2->val)
        return false;
    
    *node1 = (*node1)->next;

    return res;
}

bool f(ListNode* head)
{
    if (head == NULL) 
        return true;
    
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return helper(&head, slow);
}
```

### 2.7
```
bool f(ListNode* node1, ListNode* node2)
{
    ListNode* p1 = node1;
    ListNode* p2 = node2;
    
    bool bP1MetTail = false, bP2MetTail = false;
    
    while (1)
    {
        if (p1 == NULL)
        {
            if (!bP1MetTail)
            {
                p1 = node2;
                bP1MetTail = true;
            }
            else
                break;
            
        }
        
        if (p2 == NULL)
        {
            if (!bP2MetTail)
            {
                p2 = node1;
                bP2MetTail = true;
            }
            else
                break;
        }
        
        cout << p1->val << " " << p2->val << endl;
        
        if (p1 == p2)
            return true;
        
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return false;
}
```

### 2.8
```
ListNode* f(ListNode* head)
{
    ListNode* fast = head->next->next;
    ListNode* slow = head->next;
    
    while (fast != slow)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    
    ListNode* res = head;
    while (res != slow)
    {
        res = res->next;
        slow = slow->next;
    }
    
    return res;
}
```
