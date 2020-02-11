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

### 7. mfc
```
BEGIN_MESSAGE_MAP(CFreqDeptMatSetupOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_PWL, OnFilterChange)
END_MESSAGE_MAP()
```

```
protected:
	int m_iCheck;

void CFreqDeptMatSetupOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_PWL, m_iSelection);
	DDX_Check(pDX, IDC_SET_SPATIAL_DEP_CHK, m_iCheck);
}
```

```
public:
  CButton m_DataPoints;
private:
  afx_msg void OnFilterChange();

void CFreqDeptMatSetupOptionDlg::OnFilterChange()
{
  BOOL bEnableSpatial = (BST_CHECKED == m_DataPoints.GetCheck()) ? TRUE : FALSE;
  // m_chkPhysicsEM.EnableWindow(bEnablePhysics);

  CWnd * wnd = this->GetDlgItem(IDC_SET_SPATIAL_DEP_CHK);
  wnd->EnableWindow(bEnableSpatial);
}
```

### 8. errorMsg
```
AnsoftMessage am = AnsoftMessage(kFatalMessage, kLIBID_GLOBAL, IDS_FILE_FORMAT_NOT_SUPPORTED, -1);
am.AddArg(fileExt, 0);
::GetMessageManager()->AddAnsoftMessage(am);
```

### 9. No instance of overloaded function matches the specified type
```
#include "CoreInterfaces/IDesignInstance.h"
```

### 10. Unresolved external symbol in object files(Error LNK 2019 & 2021)
```
class AB_DLL_API CChild : public CBase
{
  //...
};
```
> ref: https://stackoverflow.com/questions/31485095/linker-errors-dll-and-inheritance


### 11. Port to Linux 
```
#ifdef PC_ANSOFT
    exePath.append("\\ansysedt.exe\" ");
#else
    exePath.append("/ansysedt\" ");
#endif
```
### 12. Dlg not open in .dll
```
AFX_MANAGE_STATE(AfxGetAppModuleState());
```
> ref: https://stackoverflow.com/questions/9062034/what-does-afx-manage-stateafxgetstaticmodulestate-do-exactly/9443848

### 13. std::transform
```
std::transform(vars.begin(), vars.end(), varNames.begin(), [](const Variable& var)
{
    return var.GetName();
});
```
> ref: https://stackoverflow.com/questions/31064749/what-is-the-difference-between-stdtransform-and-stdfor-each

### 14. runtime error: member access within misaligned address 0xbebebebebebebebe for type 'struct Node', which requires 8 byte alignment
* 0xbebebebebebebebe: note: pointer points here <memory cannot be printed>
```
Node* root; // = NULL;
if (root == NULL)
{
    // it won't go into here
}
```
