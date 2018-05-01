### 1. vector iterators incompatible
```
vector<int> v;
v.push_back(18);
v.push_back(7);
v.push_back(22);
v.push_back(10);
v.push_back(69);

const vector<int> emptyV;
for (vector<int>::iterator it = v.begin(); it != emptyV.end(); it++) {
  cout << *it << endl;
}
```

### 2. fatal error C1010
unexpected end of file while looking for precompiled header directive
Properties -> Precompiled Headers -> Not Using Precompiled headers
> ref: https://blog.csdn.net/ziren235/article/details/1428869
