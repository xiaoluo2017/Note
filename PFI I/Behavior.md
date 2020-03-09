# Behavior

## Behavior QA
### 1. Introduction
* Hi, my name is .... I graduated from Tianjin University with a Bachelor of Science degree in Electrical Engineering, and graduated from the George Washington University with a Masters degree in Electrical and Computer Engineering.
* During my graduate studies, I had a good understanding of data structures, algorithms, and object-oriented design, and completed some Java-based projects. After graduation, I implemented a presonal project, a Voting Web Application, based on React, Node.js and MongoDB. From April, 2018, I joined ... as a software engineer.
* Let me first introduce my current company. ... is the world's largest engineering simulation software company, it is included in S&P 500 and Nasdaq 100.
* My team, EBU R&D product team, develops a variety of basic software components and provides interfaces to our product team, for electrical simulation products.
* For me, I mainly used C ++ and MFC to design and implement projects on Windows, or implemented features and APIs for some core functionality areas, for example, Maxwell standalone system coupling project; In "Material" field, adding Spatial Modifer; In "Dataset" field, the 3D dataset UI enhancement. In "Definition libraries" field, providing capability to export parametric table, import/export of Project/design variables. And I Implemented undo/redo and script record/playback of various operations, etc.
* I also wrote Test Plan, regression tests and Code Change Proposal, and did Enhancements/bug fixes in these areas.

### 2. 3rd-person Introduction
* I am glad to refer my friend, ..., to work at ... as a Software Engineer. He graduated from ... University with a Bachelor of Science degree in Electrical Engineering, and graduated from the ... University with a Masters degree in Electrical and Computer Engineering. From April, 2018, he joined ... as a software engineer.
* I have known ... for almost 10 years. I have always admired his diligence and commitment in what he does. He has great passion in technology, and his attention to detail makes him a good engineer. I believe he could be a good fit for our company, and would be able to contribute great value.
* Technically, during his work, he designed, developed, and maintained various software components in a highly collaborative team environment. He has acquired deep technical knowledge in software development methodologies and has extensive experience in project planning and implementation. He has the ability to get quality work done as planned. He has extensive experience in developing and debugging code on Windows, using C++ and MFC.
* Please consider ... for the position. Thank you.

## Project
### 1. Maxwell standalone system coupling
* Establishing connection with EDT and System Coupling Engine
    * Client(initially): SC Engine
    * Server(initially): participants, eg. DEFAULT, CFX, FLUENT, MAPDL, AEDT
      * When a participant serves RPC requests, it is in the server mode. The participant will continue to serve requests, one at a time, until some special request comes in.

* RPC requests: commands & queries
    * Queries: Ans::Rpc::Response needs to be filled in with some information and sent back to SC Engine
      * eg. SyncProcess::GetAllSyncPoints
    * Commands: SC engine is not expecting a response, but rather signals to the participant to take appropriate action. This is typically done to coordinate the coupling solve process
      * eg. SyncProcess::AssignToken, SyncProcess::Shutdown

```
void SyncProcess::GetAllSyncPoints(const Ans::Rpc::Request& request, Ans::Rpc::Response& response)
{
    static Ans::Rpc::MessageArrayArg<std::string> syncPoints;

    std::vector<std::string> values;
    values.push_back("Initial Synchronization");
    values.push_back("Analysis Initialization");
    // ...

    syncPoint.Values = values;
    response.AddSharedArg(&syncPoints);
}
```

```
// These two variables are defined outside SyncProcess::AssignToken scope but are accessible by it
bool continueExecution = true;
std::string lastCommand;

void SyncProcess::AssignToken(const Ans::Rpc::Request& request, Ans::Rpc::Response& response)
{
    continueExecution = false; // note - this modifies the state
    lastCommand = "SyncProcess::AssignToken";
    return;
}

// --------------------------------

// this loop can be implemented elsewhere, but it must have access to continueExecution
while (continueExecution) {
    // ...
    int timeout = 0
    ansRpcServer.ServeOneRequest(timeout);
}

// can issue RPC Requests now via ansRpcClient outside SyncProcess::AssignToken
If (lastCommand == "SyncProcess::AssignToken") {
    // issue RPC requests, eg. SyncManager::YieldToken
}
```

* Synchronization Points
    * co-simulation workflow spans multiple independent applications, their synchronization must be carefully controlled in order to avoid deadlocks
    * server-client roles are changed multiple times during cosimulation
    
* Communication Sequence
    * Write out scService.scs file(with port/host information)
    * Connect all
    * [Reach 'Initial Synchronization']
    * [Reach 'Analysis Initialization']
    * Coupling step/iteration loop
      * [Reach 'Solution']
      * Import mesh & Calculate mapping weights
      * [Reach 'Data Transfer’]
      * Interpolate
      * [Reach 'Solve']
      * [Reach 'Check Convergence']
    * [Reach 'Shutdown']
    * Disconnect all

* General process flow between two synchronization points
    * At the beginning of sync. point, SC Engine always has control, and participants are listening for incoming requests from SC Engine
    * SyncProcess::ContinueFromSyncPoint
      * This signals to participants that they can now execute some local code. Participant is not allowed to send any requests to SC Engine(SC Engine is not listening for requests). After executing some local code, the participant must go back into the listen mode
    * SyncProcess::AssignToken
      * SC Engine is yielding control to EDT and is listening for RPC requests. Participant can execute local code and make RPC requests to SC Engine
    * SyncManager::PausedAtSyncPoint
      * Notify SC Engine that it has reached the sync point, pass the name of the sync point
    * SyncManager::YieldToken
      * Yield control token back to SC Engine and go into the listen mode
      
### 2. Import/export of Project/design variable
* Variable type
    * ProjectNonIndexedVariables, ProjectVariables, NonIndexedVariables, PostProcessVariables, LocalVariables
* For ImportVariables, import data from file into a block, read block into clipboard, then reuse 'paste' logic to paste variables from clipboard to target Project/Design
* For ExportVariables, get project/local variables and push into a vector, then reuse 'copy' logic to copy variables into clipboard, write clipboard into block, at last write block into file

```
$a = $arr[$b];
$b = $c + 1;
$c = 0;
$d = $e;
$arr = [1mm, 2mm, 3mm];
```

### 3. Undo/redo and script record/playback
* class ...Cmd : public AnsoftCommand
    * Implement GetScriptCommand, GetScriptArguments and DoIt
* class ...Item : public io::CStreamio_block_object
    * Implement DoDataExchange(io::CBlock& block, bool do_read)
* class ...CmdInfo : public AnsoftCommandInfo

```
OptimetricsCmdInfo* OptimetricsModule::GetOrCreateCommandInfo(
                                       IAnsoftCommand* icmd, 
                                       AnsoftCommandInfo::InfoType info,
                                       AnsoftCommandInfo::InfoSubType subInfo,
                                       bool bSetDesignDoesntSupportSC) const
{
    id::InfoSource infoSourceID = id::kOptimetrics;
    OptimetricsCmdInfo* theInfo = dynamic_cast<OptimetricsCmdInfo*>(icmd->GetInfo(infoSourceID));
    if (!theInfo)
    {
        theInfo = new OptimetricsCmdInfo();
        icmd->AddInfo(infoSourceID, theInfo);
    }
    theInfo->AddInfoType(info);
    theInfo->AddInfoSubType(subInfo);
    theInfo->setDesignContentDoesntSupportSC(bSetDesignDoesntSupportSC);
    return theInfo;
}
```

### 4. AutoClose Dialog feature
* class UIRESOURCES_API CDlgAutoClose : public IAutoCloseWnd
    * Implement HandleFocusChange

```
bool CDlgAutoClose::HandleFocusChange(HWND hWndNewFocus)
{
    // focus being changed to window that's not a child of us
    // destroy us
    if(hWndNewFocus == NULL || 
        (hWndNewFocus != m_hWnd) && !::IsChild(m_hWnd,hWndNewFocus)
        && m_hWnd != NULL)
    {
        TRACE("Focus changing to %x\n", hWndNewFocus);
        if(GetAllowDestroyWindow())
        {
            PostMessage(WM_DLGAUTOCLOSE_DESTROY_ME);
        }
    }       
    return false;
}
```

## Bug
### 1. Messages show up under the wrong project
* In CMainFrame::OnWindowCloseAll(), it will call SendMessage(WM_CLOSE) for each MDIChild. However, WM_CLOSE msg will first call Destroy() on current child, then call Activate() on next child. The one that was originally opened will be the latest closed, the latest closed will also be the last UI activated, which is different from the current active window.
* In CMainFrame::OnWindowCloseAll(), call SendMessage(WM_CLOSE) for each MDIChild in reverse order. The one that is currently opened will be the latest closed,which will also be the last UI activated, which is actually the current active window.

### 2. Disable close button, most top-right close button 'x' and the accelerator(Alt+F4)
* crash of EDT on validation and geometry check
    * Override the OnClose function, if it's still in validation just don't close, this will work both for the most top-right close button 'x' and the accelerator(Alt+F4) in Validation Check
* Maxwell Crashes when running Fluent-Maxwell case and closing Maxwell UI while SC run
    * In CDesktopApp::InitInstance, disable the close button; In mainfrm::OnSysCommand, prevent the 'Alt+F4' command
> ref: http://computer-programming-forum.com/82-mfc/84cd318f33e24bca.htm

```
if (!GetDesktopApp()->IsInSystemCouplingMode()) 
{
    // prevent the accelerator(Alt+F4) in system coupling mode
    CBCGPMDIFrameWnd::OnSysCommand(nID, lParam);
}
```

```
void CSystemCouplingUIHelper::ModifyMenu(CMenu& menu, HWND hWnd)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState())
    if (GetDesktopApp()->IsInSystemCouplingMode())
    {
        // Disable the most top-right close button 'x' of the Ansysedt window
        ::EnableMenuItem(::GetSystemMenu(hWnd, FALSE),
            SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    }
}
```

## QA
### 1. 技术
* 组里做什么(大组 小组)
* 组里技术栈
* 组里人员组成(小组)
* 我进去后, 我做什么
### 2. 工作
* 会议 eg. standup, iteration meeting
* 与美国方面交流多吗, 平常使用英语多吗
* 入职是否有培训
### 3. 生活
* 上班时间, 几点上班, 几点下班
* 是否有食堂
* 活动多吗
* 是否出差
