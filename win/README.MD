# win

## 开发环境

1. 安装VS2017
2. 安装vcpkg
   ```bash
   $ git clone https://github.com/Microsoft/vcpkg.git
   $ cd vcpkg
   $ bootstrap-vcpkg.bat
   $ vcpkg integrate install
   ```
3. 三方库安装
   ```bash
   $ vcpkg install spdlog   # 安装
   $ vcpkg install protobuf # 3.13.0
   $ vcpkg install evpp     # c++跨平台通信库
   $ vcpkg install jsoncpp  # json解析库
   ```

## 编译

使用VS 2017打开all.sln，切换到release，然后编译即可。