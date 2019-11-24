### 5.1
```
int f(int N, int M, int i, int j)
{
    for (int k = j; k >= i; k--)
    {
        if (M >> (k - i) & 1 == 1)
            N = N | (1 << k);
        else
            N = N & ~(1 << k);
    }
    
    return N;
}
```

### 5.2
```
string f(double d)
{
    if (d < 0 || d > 1) return "Error";
    
    string res = "";
    d *= 2;
    for (int i = 0; i < 32; i++)
    {
        if (d == 0) 
        {
            while (res.size() < 32)
                res += "0";
            break;
        }
        else if (d < 1) 
        {
            d *= 2;
            res += "0";
        }
        else
        {
            d--;
            res += "1";
        }
    }
    
    return res;
}
```

### 5.3
```
int f(int input)
{
    bool bHasFlipped = false;
    int res = 32;
    for (int i = 0; i < 32; i++)
    {
        if (((input >> i) & 1) == 0)
        {

            if (!bHasFlipped) 
            {
                bHasFlipped = true;
            }
            else
            {
                res = i;
                break;
            }
        }
    }
    
    return res;
}
```

### 5.4
```
int smallest(int input)
{
    int res = input;
    for (int i = 0; i < 31; i++)
    {
        if (((input >> i) & 1) == 1 && ((input >> (i + 1) & 1) == 0))
        {
            res = res & ~(1 << i);
            res = res | (1 << (i + 1));
            break;
        }
    }
            
    return res > 0 ? res : -1;
}
            
int largest(int input)
{
    int count = 0;
    for (int i = 0; i < 32; i++)
    {
        if (((input >> i) & 1) == 0)
        {
            count++; 
        }
    }
    
    if (count == 1) return -1;
    
    return ((~0 << (count - 1)) & ~(1 << 31));
}
```

### 5.6
```
int f(int i1, int i2)
{
    int count = 0;
    
    for (int i = 0; i < 32; i++)
    {
        if (((i1 >> i) & 1) != ((i2 >> i) & 1))
            count++;
    }
    return count;
}
```
