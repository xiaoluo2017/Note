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

### 3. io
```
AString regionDisplayName = theHelper.GetBodyName(objs[i]);
io::CBlock_func displayNameFunc("DisplayName");
displayNameFunc << regionDisplayName;
oneRegionBlock << displayNameFunc;
```

### 4. ui
```
BEGIN
  MENUITEM "E&nable Setup",               ID_SETUP_ENABLE
END
```

```
CONTROL         "",IDC_FRAME,"Static",SS_BLACKFRAME | SS_SUNKEN,187,21,180,140
```


### 5. IsInScripting()
need to be inherited from io::CStreamio_block_object

### 6. const
pass in vectors/AString/map as const& would be efficient here
```
const std::vector<id::BasicID>& simSetups = GetSimSetups();
const AString& datasetFileFullPath;
```

if return an object to an outside Value, const is not needed
```
virtual AString GetProductInfoForSystemCoupling() const = 0;
```

