# WindowImplBase

| �������� | ��; |
| :--- | :--- |
| [InitWindow](#InitWindow) | �����յ����ڴ�����Ϣʱ������ |
| [OnFinalMessage](#OnFinalMessage) | �����յ�����������Ϣʱ������ |
| [GetStyle](#GetStyle) | ��ȡ������ʽ |
| [GetClassStyle](#GetClassStyle) | ��ȡ��������ʽ |
| [GetResourceType](#GetResourceType) | ������ |
| [GetResourceID](#GetResourceID) | ������ |
| [CreateControl](#CreateControl) | ��Ҫ�����Ŀؼ����Ǳ�׼�Ŀؼ�����ʱ����øú��� |
| [MessageHandler](#MessageHandler) | ����������Ϣ |
| [OnClose](#OnClose) | ���յ����ڹر���Ϣʱ������ |
| [OnDestroy](#OnDestroy) | ���յ����ڱ�������Ϣʱ������ |
| [OnNcActivate](#OnNcActivate) | ���յ����ǻ״̬��Ϣʱ������ |
| [OnNcCalcSize](#OnNcCalcSize) | ���յ�Ҫ����ͻ������С��Ϣʱ��WM_NCCALCSIZE�������� |
| [OnWindowPosChanging](#OnWindowPosChanging) | ����λ�û� Z �������ı�ʱ������ |
| [OnNcPaint](#OnNcPaint) | �����յ����Ʊ�����������Ϣʱ������ |
| [OnNcLButtonDbClick](#OnNcLButtonDbClick) | �����յ�����������˫����Ϣʱ������ |
| [OnNcHitTest](#OnNcHitTest) | �����յ� WM_NCHITTEST ��Ϣʱ������ |
| [OnGetMinMaxInfo](#OnGetMinMaxInfo) | �����յ� WM_GETMINMAXINFO ��Ϣʱ������ |
| [OnMouseWheel](#OnMouseWheel) | �����յ����������Ϣʱ������ |
| [OnMouseHover](#OnMouseHover) | �����յ����ڴ�С�ı���Ϣʱ������ |
| [OnSize](#OnSize) | �����յ����ڴ�С�ı���Ϣʱ������ |
| [OnChar](#OnChar) | �����յ��ַ�������Ϣʱ��WM_CHAR�������� |
| [OnSysCommand](#OnSysCommand) | ���մ��ڿ���������Ϣʱ��WM_SYSCOMMAND�������� |
| [OnKeyDown](#OnKeyDown) | ���ռ��̰���������Ϣʱ������ |
| [OnKillFocus](#OnKillFocus) | ����ʧȥ������Ϣʱ������ |
| [OnSetFocus](#OnSetFocus) | ���ջ�ȡ������Ϣʱ������ |
| [OnLButtonDown](#OnLButtonDown) | ���յ�������������Ϣʱ������ |
| [OnLButtonUp](#OnLButtonUp) | ���յ�������������Ϣʱ������ |
| [OnMouseMove](#OnMouseMove) | ���յ�����ƶ���Ϣʱ������ |
| [OnDpiChanged](#OnDpiChanged) | �����յ�DPI�ı���Ϣʱ�����ã�ֻ���� Startup ��ָ������ DPI �����Żᴥ���� |
| [HandleMessage](#HandleMessage) | ������Ϣ���ɷ����� |
| [ActiveWindow](#ActiveWindow) | ����� |
| [SetTaskbarTitle](#SetTaskbarTitle) | ���ô��ڱ��� |
| [ToTopMost](#ToTopMost) | �ö����� |
| [GetSkinFolder](#GetSkinFolder) | ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ��Ŀ¼ |
| [GetSkinFile](#GetSkinFile) | ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ�� XML �����ļ� |
| [GetWindowClassName](#GetWindowClassName) | ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ψһ�������� |
| [OnCreate](#OnCreate) | �յ����ڴ�����Ϣʱ�����ã���ʹ�� InitWindow �ӿ���ʵ���Զ������� |
| [OnButtonClick](#OnButtonClick) | ���ڹ��ܰ�ť�����ʱ���� |


### InitWindow

�����յ����ڴ�����Ϣʱ������

```cpp
virtual void InitWindow()
```

 - ��&emsp;������  
 - ����ֵ����

### OnFinalMessage

�����յ�����������Ϣʱ������

```cpp
virtual void OnFinalMessage( HWND hWnd )
```

 - ��&emsp;����  
    - `hWnd` Ҫ���ٵĴ��ھ��
 - ����ֵ����

### GetStyle

��ȡ������ʽ

```cpp
virtual LONG GetStyle()
```

 - ��&emsp;������  
 - ����ֵ�����ش�����ʽ

### GetClassStyle

��ȡ��������ʽ

```cpp
virtual UINT GetClassStyle()
```

 - ��&emsp;������  
 - ����ֵ�����ش�������ʽ

### GetResourceType

������

```cpp
virtual UILIB_RESOURCETYPE GetResourceType()
```

 - ��&emsp;����  
    - `������
 - ����ֵ��������

### GetResourceID

������

```cpp
virtual std::wstring GetResourceID()
```

 - ��&emsp;����  
    - `������
 - ����ֵ��������

### CreateControl

��Ҫ�����Ŀؼ����Ǳ�׼�Ŀؼ�����ʱ����øú���

```cpp
virtual Control* CreateControl(const std::wstring& pstrClass)
```

 - ��&emsp;����  
    - `pstrClass` �ؼ�����
 - ����ֵ������һ���Զ���ؼ�ָ�룬һ������¸��� pstrClass ���������Զ���Ŀؼ�

### MessageHandler

����������Ϣ

```cpp
virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
	- `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnClose

���յ����ڹر���Ϣʱ������

```cpp
virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnDestroy

���յ����ڱ�������Ϣʱ������

```cpp
virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnNcActivate

���յ����ǻ״̬��Ϣʱ������

```cpp
virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnNcCalcSize

���յ�Ҫ����ͻ������С��Ϣʱ��WM_NCCALCSIZE��������

```cpp
virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnWindowPosChanging

����λ�û� Z �������ı�ʱ������

```cpp
virtual LRESULT OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnNcPaint

�����յ����Ʊ�����������Ϣʱ������

```cpp
virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnNcLButtonDbClick

�����յ�����������˫����Ϣʱ������

```cpp
virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnNcHitTest

�����յ� WM_NCHITTEST ��Ϣʱ������

```cpp
virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnGetMinMaxInfo

�����յ� WM_GETMINMAXINFO ��Ϣʱ������

```cpp
virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnMouseWheel

�����յ����������Ϣʱ������

```cpp
virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnMouseHover

�����յ����ڴ�С�ı���Ϣʱ������

```cpp
virtual LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnSize

�����յ����ڴ�С�ı���Ϣʱ������

```cpp
virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnChar

�����յ��ַ�������Ϣʱ��WM_CHAR��������

```cpp
virtual LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnSysCommand

���մ��ڿ���������Ϣʱ��WM_SYSCOMMAND��������

```cpp
virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnKeyDown

���ռ��̰���������Ϣʱ������

```cpp
virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnKillFocus

����ʧȥ������Ϣʱ������

```cpp
virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnSetFocus

���ջ�ȡ������Ϣʱ������

```cpp
virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnLButtonDown

���յ�������������Ϣʱ������

```cpp
virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnLButtonUp

���յ�������������Ϣʱ������

```cpp
virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### OnMouseMove

���յ�����ƶ���Ϣʱ������

```cpp
virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������
 
### OnDpiChanged

�����յ�DPI�ı���Ϣʱ�����ã�ֻ���� Startup ��ָ������ DPI �����Żᴥ����

```cpp
virtual LRESULT OnDpiChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### HandleMessage

������Ϣ���ɷ�����

```cpp
virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
```

 - ��&emsp;����  
    - `uMsg` ��Ϣ����
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ���� true ������ɷ�����Ϣ���������ɷ�����Ϣ
 - ����ֵ��������Ϣ������

### ActiveWindow

�����

```cpp
virtual void ActiveWindow()
```

 - ��&emsp;������  
 - ����ֵ��void �޷���ֵ

### SetTaskbarTitle

���ô��ڱ���

```cpp
virtual void SetTaskbarTitle(const std::wstring &title)
```

 - ��&emsp;����  
    - `title` ���ڱ���
 - ����ֵ��void �޷���ֵ

### ToTopMost

�ö�����

```cpp
void ToTopMost(bool forever)
```

 - ��&emsp;����  
    - `forever` �Ƿ�һֱ�ö�
 - ����ֵ��void �޷���ֵ

### GetSkinFolder

��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ��Ŀ¼

```cpp
virtual std::wstring GetSkinFolder()
```

 - ��&emsp;������  
 - ����ֵ��������ʵ�ֲ����ش���Ƥ��Ŀ¼

### GetSkinFile

��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ�� XML �����ļ�

```cpp
virtual std::wstring GetSkinFile()
```

 - ��&emsp;������  
 - ����ֵ��������ʵ�ֲ����ش���Ƥ�� XML �����ļ�

### GetWindowClassName

��������ʱ�����ã�������ʵ�����Ի�ȡ����Ψһ��������

```cpp
virtual std::wstring GetWindowClassName(void)
```

 - ��&emsp;������  
 - ����ֵ��������ʵ�ֲ����ش���Ψһ��������

### OnCreate

�յ����ڴ�����Ϣʱ�����ã���ʹ�� InitWindow �ӿ���ʵ���Զ�������

```cpp
LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
```

 - ��&emsp;����  
    - `uMsg` ��ϢID
    - `wParam` ��Ϣ���Ӳ���
    - `lParam` ��Ϣ���Ӳ���
    - `bHandled` ��Ϣ�Ƿ��Ѿ�������
 - ����ֵ��������Ϣ������

### OnButtonClick

���ڹ��ܰ�ť�����ʱ����

```cpp
bool OnButtonClick(EventArgs* param)
```

 - ��&emsp;����  
    - `param` Я���Ĳ���
 - ����ֵ��ʼ�շ��� true

