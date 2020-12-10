# CefControl��Cef �ؼ���

`CefControl` �� `CefNativeControl` �̳��� `Control` �ؼ����Ժͷ���������������Ժͷ�����ο���[Control](Control.md) �ؼ�

 - CefControl ��������Ⱦģʽ�� CEF �ؼ�
 - CefNativeControl ���洰��ģʽ�� CEF �ؼ������д��ھ����

CEF �ؼ�ʹ�������֧�� XP �� 2623 �汾���ؼ����� CEF �Ѿ�����õĶ������ļ����� bin Ŀ¼�� cef �� cef_x64���� CEF �� C++ ��װ�� `third_party\\cef_wrapper`��
���ʹ�õ��� `CefControl` �� `CefNativeControl`����Ҫ����Ӧ�汾�� cef Ŀ¼���Ƶ���ִ���ļ���ͬĿ¼���� `third_party\\cef_wrapper` Ŀ¼����Ϊ����ͷĿ¼��������ο� samples Ŀ¼�µ� cef ʾ���� multi_browser ʾ����

| �������� | ��; |
| :--- | :--- |
| [LoadURL](#LoadURL) | ����һ����ַ |
| [LoadString](#LoadString) | ��ָ����ַ���һ���ַ�����Դ |
| [GoBack](#GoBack) | ���� |
| [GoForward](#GoForward) | ǰ�� |
| [CanGoBack](#CanGoBack) | �ж��Ƿ���Ժ��� |
| [CanGoForward](#CanGoForward) | �ж��Ƿ����ǰ�� |
| [Refresh](#Refresh) | ˢ�� |
| [StopLoad](#StopLoad) | ֹͣ���� |
| [IsLoading](#IsLoading) | �Ƿ������ |
| [StartDownload](#StartDownload) | ��ʼһ���������� |
| [SetZoomLevel](#SetZoomLevel) | ����ҳ�����ű��� |
| [GetURL](#GetURL) | ��ȡҳ�� URL |
| [GetUTF8URL](#GetUTF8URL) | ��ȡ UTF8 ��ʽ URL |
| [GetMainURL](#GetMainURL) | ��ȡ��ַ # ��ǰ�ĵ�ַ |
| [RegisterCppFunc](#RegisterCppFunc) | ע��һ�� C++ �����ṩǰ�˵��� |
| [UnRegisterCppFunc](#UnRegisterCppFunc) | ��ע��һ�� C++ ���� |
| [CallJSFunction](#CallJSFunction) | ����һ��ǰ���Ѿ�ע��õķ��� |
| [CallJSFunction](#CallJSFunction) | ����һ��ǰ���Ѿ�ע��õķ��� |
| [AttachDevTools](#AttachDevTools) | �󶨿����߹��ߵ�һ�� CefControl �ؼ��� |
| [DettachDevTools](#DettachDevTools) | ��󿪷��߹��� |
| [IsAttachedDevTools](#IsAttachedDevTools) | �ж��Ƿ��Ѿ��󶨿����߹��ߵ�һ�� CefControl |
| [RepairBrowser](#RepairBrowser) | �޸������ |
| [AttachBeforeContextMenu](#AttachBeforeContextMenu) | ��һ���ص��������ڼ����Ҽ��˵����� |
| [AttachMenuCommand](#AttachMenuCommand) | ��һ���ص��������ڼ���ѡ�����ĸ��Ҽ��˵� |
| [AttachTitleChange](#AttachTitleChange) | ��һ���ص��������ڼ���ҳ�� Title �ı� |
| [AttachUrlChange](#AttachUrlChange) | ��һ���ص��������ڼ���ҳ���� frame URL ��ַ�ı� |
| [AttachMainURLChange](#AttachMainURLChange) | ��һ���ص��������ڼ�����ҳ�� URL ��ַ�ı� |
| [AttachBeforeNavigate](#AttachBeforeNavigate) | ��һ���ص��������ڼ���ҳ����Դȫ��������� |
| [AttachLinkClick](#AttachLinkClick) | ��һ���ص��������ڼ���һ���������ڵ�����֪ͨ |
| [AttachLoadingStateChange](#AttachLoadingStateChange) | ��һ���ص��������ڼ���ҳ�����״̬�ı� |
| [AttachLoadStart](#AttachLoadStart) | ��һ���ص��������ڼ���ҳ�濪ʼ����֪ͨ |
| [AttachLoadEnd](#AttachLoadEnd) | ��һ���ص��������ڼ���ҳ��������֪ͨ |
| [AttachLoadError](#AttachLoadError) | ��һ���ص��������ڼ���������ش���֪ͨ |
| [AttachDevToolAttachedStateChange](#AttachDevToolAttachedStateChange) | ��һ���ص��������ڼ��������߹���״̬�ı�֪ͨ |

### LoadURL

����һ����ַ

```cpp
void LoadURL(const CefString& url)
```

 - ��&emsp;����  
    - `url` ��վ��ַ
 - ����ֵ����

### LoadString

��ָ����ַ���һ���ַ�����Դ

```cpp
void LoadString(const CefString& stringW, const CefString& url)
```

 - ��&emsp;����  
    - `stringW` �ַ�����Դ
    - `url` ��ַ
 - ����ֵ����

### GoBack

����

```cpp
void GoBack()
```

 - ��&emsp;������  
 - ����ֵ����

### GoForward

ǰ��

```cpp
void GoForward()
```

 - ��&emsp;������  
 - ����ֵ����

### CanGoBack

�ж��Ƿ���Ժ���

```cpp
bool CanGoBack()
```

 - ��&emsp;������  
 - ����ֵ������ true ��ʾ���ԣ�false ��ʾ������

### CanGoForward

�ж��Ƿ����ǰ��

```cpp
bool CanGoForward()
```

 - ��&emsp;������  
 - ����ֵ������ true ��ʾ���ԣ�false ��ʾ������

### Refresh

ˢ��

```cpp
void Refresh()
```

 - ��&emsp;������  
 - ����ֵ����

### StopLoad

ֹͣ����

```cpp
void StopLoad()
```

 - ��&emsp;������  
 - ����ֵ����

### IsLoading

�Ƿ������

```cpp
bool IsLoading()
```

 - ��&emsp;������  
 - ����ֵ������ true ��ʾ�����У�����Ϊ false

### StartDownload

��ʼһ����������

```cpp
void StartDownload(const CefString& url)
```

 - ��&emsp;����  
    - `url` Ҫ���ص��ļ���ַ
 - ����ֵ����

### SetZoomLevel

����ҳ�����ű���

```cpp
void SetZoomLevel(float zoom_level)
```

 - ��&emsp;����  
    - `zoom_level` ����ֵ
 - ����ֵ����

### GetURL

��ȡҳ�� URL

```cpp
CefString GetURL()
```

 - ��&emsp;������  
 - ����ֵ������ URL ��ַ

### GetUTF8URL

��ȡ UTF8 ��ʽ URL

```cpp
std::string GetUTF8URL()
```

 - ��&emsp;������  
 - ����ֵ������ URL ��ַ

### GetMainURL

��ȡ��ַ # ��ǰ�ĵ�ַ

```cpp
CefString GetMainURL(const CefString& url)
```

 - ��&emsp;����  
    - `url` Ҫ��ȡ��������ַ
 - ����ֵ�����ؽ�ȡ��ĵ�ַ

### RegisterCppFunc

ע��һ�� C++ �����ṩǰ�˵���

```cpp
bool RegisterCppFunc(const std::wstring& function_name, nim_cef::CppFunction function, bool global_function = false)
```

 - ��&emsp;����  
    - `function_name` ��������
    - `function` ����������
    - `global_function` �Ƿ���һ��ȫ�ַ���
 - ����ֵ������ true ��ʾע��ɹ���false �����Ѿ�ע��

### UnRegisterCppFunc

��ע��һ�� C++ ����

```cpp
void UnRegisterCppFunc(const std::wstring& function_name)
```

 - ��&emsp;����  
    - `function_name` ��������
 - ����ֵ����

### CallJSFunction

����һ��ǰ���Ѿ�ע��õķ���

```cpp
bool CallJSFunction(const std::wstring& js_function_name, const std::wstring& params, nim_cef::CallJsFunctionCallback callback, const std::wstring& frame_name = L"")
```

 - ��&emsp;����  
    - `js_function_name` ǰ���ṩ�ķ�����
    - `params` ���� JSON �ַ�����ʽ�Ĳ���
    - `callback` ǰ��ִ����ɺ�Ļص�����
    - `frame_name` Ҫ�����ĸ����� frame �µķ�����Ĭ��ʹ���� frame
 - ����ֵ������ true ��ʾ�ɹ����ã�false ��ʾ����ʧ�ܣ��������ܲ�����

### CallJSFunction

����һ��ǰ���Ѿ�ע��õķ���

```cpp
bool CallJSFunction(const std::wstring& js_function_name, const std::wstring& params, nim_cef::CallJsFunctionCallback callback, int frame_id)
```

 - ��&emsp;����  
    - `js_function_name` ǰ���ṩ�ķ�����
    - `params` ���� JSON �ַ�����ʽ�Ĳ���
    - `callback` ǰ��ִ����ɺ�Ļص�����
    - `frame_id` Ҫ�����ĸ� ID frame �µķ�����Ĭ��ʹ���� frame
 - ����ֵ������ true ��ʾ�ɹ����ã�false ��ʾ����ʧ�ܣ��������ܲ�����

### AttachDevTools

�󶨿����߹��ߵ�һ�� CefControl �ؼ���

```cpp
virtual bool AttachDevTools(CefControl* view)
```

 - ��&emsp;����  
    - `view` һ�� CefControl �ؼ�ʵ��
 - ����ֵ���ɹ����� true��ʧ�ܷ��� false

### DettachDevTools

��󿪷��߹���

```cpp
virtual void DettachDevTools()
```

 - ��&emsp;������  
 - ����ֵ����

### IsAttachedDevTools

�ж��Ƿ��Ѿ��󶨿����߹��ߵ�һ�� CefControl

```cpp
virtual bool IsAttachedDevTools()
```

 - ��&emsp;������  
 - ����ֵ������ true ��ʾ�Ѿ��󶨣�false Ϊδ��

### RepairBrowser

�޸������

```cpp
virtual void RepairBrowser()
```

 - ��&emsp;������  
 - ����ֵ����

### AttachBeforeContextMenu

��һ���ص��������ڼ����Ҽ��˵�����

```cpp
void AttachBeforeContextMenu(const OnBeforeMenuEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnBeforeMenuEvent ����
 - ����ֵ����

### AttachMenuCommand

��һ���ص��������ڼ���ѡ�����ĸ��Ҽ��˵�

```cpp
void AttachMenuCommand(const OnMenuCommandEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnMenuCommandEvent ����
 - ����ֵ����

### AttachTitleChange

��һ���ص��������ڼ���ҳ�� Title �ı�

```cpp
void AttachTitleChange(const OnTitleChangeEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnTitleChangeEvent ����
 - ����ֵ����

### AttachUrlChange

��һ���ص��������ڼ���ҳ���� frame URL ��ַ�ı�

```cpp
void AttachUrlChange(const OnUrlChangeEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnUrlChangeEvent ����
 - ����ֵ����

### AttachMainURLChange

��һ���ص��������ڼ�����ҳ�� URL ��ַ�ı�

```cpp
void AttachMainURLChange(OnMainURLChengeEvent cb)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnMainURLChengeEvent ����
 - ����ֵ����

### AttachBeforeNavigate

��һ���ص��������ڼ���ҳ����Դȫ���������

```cpp
void AttachBeforeNavigate(const OnBeforeResourceLoadEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnBeforeResourceLoadEvent ����
 - ����ֵ����

### AttachLinkClick

��һ���ص��������ڼ���һ���������ڵ�����֪ͨ

```cpp
void AttachLinkClick(const OnLinkClickEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnLinkClickEvent ����
 - ����ֵ����

### AttachLoadingStateChange

��һ���ص��������ڼ���ҳ�����״̬�ı�

```cpp
void AttachLoadingStateChange(const OnLoadingStateChangeEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnLoadingStateChangeEvent ����
 - ����ֵ����

### AttachLoadStart

��һ���ص��������ڼ���ҳ�濪ʼ����֪ͨ

```cpp
void AttachLoadStart(const OnLoadStartEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnLoadStartEvent ����
 - ����ֵ����

### AttachLoadEnd

��һ���ص��������ڼ���ҳ��������֪ͨ

```cpp
void AttachLoadEnd(const OnLoadEndEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnLoadEndEvent ����
 - ����ֵ����

### AttachLoadError

��һ���ص��������ڼ���������ش���֪ͨ

```cpp
void AttachLoadError(const OnLoadErrorEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnLoadErrorEvent ����
 - ����ֵ����

### AttachDevToolAttachedStateChange

��һ���ص��������ڼ��������߹���״̬�ı�֪ͨ

```cpp
void AttachDevToolAttachedStateChange(const OnDevToolAttachedStateChangeEvent& callback)
```

 - ��&emsp;����  
    - `callback` һ���ص��������ο� OnDevToolAttachedStateChangeEvent ����
 - ����ֵ����
