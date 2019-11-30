### 12.2
```
void f(char* str)
{
    int le = 0, ri = 0;
    while (str[ri] != '\0')
    {
        ri++;
    }
    ri--;
    
    while (le < ri)
    {
        char tmp = str[le];
        str[le++] = str[ri];
        str[ri--] = tmp;
    }
}

int main() {
    char str[] = "hello world";
    f(str);
    cout << str << endl;
}
```
