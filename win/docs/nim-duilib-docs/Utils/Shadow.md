# Shadow����Ӱ��

| �������� | ��; |
| :--- | :--- |
| [SetShadowAttached](#SetShadowAttached) | �����Ƿ񸽼���ӰЧ�� |
| [IsShadowAttached](#IsShadowAttached) | �ж��Ƿ��Ѿ���������Ӱ |
| [SetShadowCorner](#SetShadowCorner) | ������Ӱ�ľŹ������� |
| [GetShadowCorner](#GetShadowCorner) | ��ȡ��Ӱ�ľŹ������� |
| [ResetShadowBox](#ResetShadowBox) | ���ݳ�ʼ������Ӱ��Χ������Ӱ�߿� |
| [SetShadowImage](#SetShadowImage) | ������ӰͼƬ |
| [GetShadowImage](#GetShadowImage) | ��ȡ��ӰͼƬλ�� |
| [AttachShadow](#AttachShadow) | ����Ӱ���ӵ����� |
| [MaximizedOrRestored](#MaximizedOrRestored) | ���ô�����󻯻��ǻ�ԭ״̬ |
| [GetRoot](#GetRoot) | ��ȡ������Ӱ�������ָ�� |
| [ClearImageCache](#ClearImageCache) | ����ͼƬ���� |
| [SetPadding](#SetPadding) | ������Ӱ�ڱ߾� |

### SetShadowAttached

�����Ƿ񸽼���ӰЧ��

```cpp
void SetShadowAttached(bool bShadowAttached)
```

 - ��&emsp;����  
    - `bShadowAttached` ���� true Ϊ�ǣ�false Ϊ��
 - ����ֵ����

### IsShadowAttached

�ж��Ƿ��Ѿ���������Ӱ

```cpp
bool IsShadowAttached()
```

 - ��&emsp;������  
 - ����ֵ������ true ��ʾ�Ѿ����ӣ�����Ϊ false

### SetShadowCorner

����Ӧ�õľŹ�������

```cpp
void SetShadowCorner(const UiRect &rect)
```

 - ��&emsp;����  
    - `rect` Ҫ���õľŹ�������
 - ����ֵ����

### GetShadowCorner

��ȡ��Ӱ�ľŹ�������

```cpp
UiRect GetShadowCorner()
```

 - ��&emsp;������  
 - ����ֵ��������Ӱ�ľŹ�������

### ResetShadowBox

���ݳ�ʼ������Ӱ��Χ������Ӱ�߿�

```cpp
void ResetShadowBox()
```

 - ��&emsp;������  
 - ����ֵ����

### SetShadowImage

������ӰͼƬ

```cpp
void SetShadowImage(const std::wstring &image)
```

 - ��&emsp;����  
    - `image` ͼƬ·��
 - ����ֵ����

### GetShadowImage

��ȡ��ӰͼƬλ��

```cpp
std::wstring GetShadowImage()
```

 - ��&emsp;������  
 - ����ֵ��������ӰͼƬλ��

### AttachShadow

����Ӱ���ӵ�����

```cpp
Box* AttachShadow(Box* pRoot)
```

 - ��&emsp;����  
    - `pRoot` ���ڵĶ�������
 - ����ֵ�����ظ�����Ӱ�������ָ��

### MaximizedOrRestored

���ô�����󻯻��ǻ�ԭ״̬

```cpp
void MaximizedOrRestored(bool isMaximized)
```

 - ��&emsp;����  
    - `isMaximized` ����Ϊ true ��ʾ��󻯣�false Ϊ��ԭ��ʼ״̬
 - ����ֵ����

### GetRoot

��ȡ������Ӱ�������ָ��

```cpp
Control* GetRoot()
```

 - ��&emsp;������  
 - ����ֵ����������ָ��

### ClearImageCache

����ͼƬ����

```cpp
void ClearImageCache()
```

 - ��&emsp;������  
 - ����ֵ����

### SetPadding

������Ӱ�ڱ߾�

```cpp
void SetPadding()
```

 - ��&emsp;������  
 - ����ֵ����

