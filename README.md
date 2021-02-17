# CoffeeChat-Windows

CoffeeChat windows(c++,nim_duilib) client open source project

## build

1. 安装VS2017。PS：“语言包”中记得勾选“英语”选项，即安装English language pack包
2. 安装vcpkg
   ```bash
   $ git clone https://github.com/Microsoft/vcpkg.git
   $ cd vcpkg
   $ # vcpkg目录加入到环境变量，如F:\github\vcpkg
   $ bootstrap-vcpkg.bat # PS: 如果安装失败，请直接在release页面下载源码。
   $ vcpkg integrate install
   ```
3. 集成vcpkg到vs2017（https://zhuanlan.zhihu.com/p/103334720）
```bash
$ vcpkg integrate install # vs2017感知工具
$ vcpkg integrate project # 集成到工程
# 在 Visual Studio 中，点击菜单 “工具->选项”, 选择"NuGet包管理器->程序包源"
# 添加新的可用程序包源, 选择 vcpkg 目录下的 “scripts\buildsystems” 目录，然后点击右侧的 “更新” 按钮。
```
4. 三方库安装
   ```bash
   $ vcpkg install spdlog           # c++log库, see: https://github.com/gabime/spdlog
   $ vcpkg install protobuf         # 3.14.0（如果版本变了，请重新生成protobuf文件）, see: https://github.com/protocolbuffers/protobuf
   $ vcpkg install evpp             # c++跨平台通信库, see: https://github.com/Qihoo360/evpp
   $ vcpkg install restclient-cpp   # c++ wraps libcurl for HTTP requests, see: https://github.com/mrtazz/restclient-cpp
   $ vcpkg install toml11           # toml解析库，header only, see: https://github.com/ToruNiina/toml11
   $ vcpkg install crossguid        # 跨平台guid，see: https://github.com/graeme-hill/crossguid
   #$ vcpkg install jsoncpp         # json解析库（使用老版本API，新版API有崩溃）
   $ vcpkg install sqlitecpp        # sqlite3的封装库，see: https://github.com/SRombauts/SQLiteCpp
   ```
5. git clone
```bash
$ git clone https://github.com/xmcy0011/CoffeeChat-Win.git
$ cd CoffeeChat-Win
$ git submodule update --init # 拉子模块
```

常见错误：
1. 找不到“evpp/xxx”或者"spdlog"或者"google/protobuf"等等，先确认vcpkg安装了上述依赖
2. 安装了依赖还是找不到，这个时候可能项目配置错误。把工程如chatkit.vcxproj以文本打开，删除多出来的vcpkg的xml项
3. 电脑启动不了，提示缺少msvcp140.dll，需要下载安装vc++2015运行环境。

## 编译

使用VS 2017打开all.sln，切换到release，然后编译即可。