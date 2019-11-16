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
