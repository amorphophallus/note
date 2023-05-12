# Visual Studio 使用指南

## 配置

## 外观

## 插件

### VCPKG

VCPKG 是 C++ 的包管理工具，VCPKG 配合 CMake 使用可以让 C++ 调库变得更加便捷

安装和配置：
- [vcpkg 官方文档](https://github.com/microsoft/vcpkg/blob/master/README_zh_CN.md)：clone repo，下载脚本
- [vcpkg 换源](https://zhuanlan.zhihu.com/p/383683670)
- [vcpkg 配置](https://zhuanlan.zhihu.com/p/447391308)：设置默认 x64
- [vcpkg+vscode+CMake 工程](https://zhuanlan.zhihu.com/p/430835667)：配置 VSCode CMake 插件，新建 CMake 项目的流程（举了一个例子）
- [vcpkg+vscode 开发环境配置](https://zhuanlan.zhihu.com/p/350194582)：安装库和综合的指令（综合之后可以直接在 VS 中调用）

vcpkg 在 CMake 中的使用：
- 配置 VSCode CMake 插件
	```json
	"cmake.configureSettings": {
		"CMAKE_TOOLCHAIN_FILE": "F:/vcpkg/scripts/buildsystems/vcpkg.cmake",
		"VCPKG_TARGET_TRIPLET": "x64-windows"
	}
	```
	或者在 `CMakeLists.txt` 中包含以下命令
	```cmake
	SET(CMAKE_TOOLCHAIN_FILE "F:/vcpkg/scripts/buildsystems/vcpkg.cmake")
	```
	或者在 CMake 命令中添加参数
	```shell
	cmake \
		-B [build directory] \
		-S . \
		-DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"
	```
	这些方法的效果都是一样的，就是设置 CMake 编译的参数，让 CMake 能找到用 vcpkg 下载的文件
- `vcpkg install xlnt`，如果已经安装过了不会重复安装，会提示在 CMake 文件中要写哪些话，把这些话复制到 `CMakeLists.txt` 中
	```cmake
	find_package(Xlnt CONFIG REQUIRED)
    target_link_libraries(main PRIVATE xlnt::xlnt)
	```
- 在源文件中直接 `#include <xlnt/...>` 会提示补全 xlnt 库包含的头文件