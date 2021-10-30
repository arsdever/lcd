# 2. Developer guide

If you want to contribute to the repository, here is a guide to help you in preparing your
working environment.

### 2.1 Windows

- [git](https://git-scm.com/download/)
- [CMake](https://cmake.org/download/)
- [vcpkg](https://vcpkg.io/en/getting-started.html) (have `git` installed before this one)
  - `vcpkg install spdlog:x64-windows`
  - `vcpkg install qt5-base:x64-windows` for gui development
  - `vcpkg install boost-test:x64-windows` for testing

On windows, you might want to use one or some of the following IDEs
- Visual Studio (Recommended) ([2022 Preview](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=community&ch=pre&rel=17), [2019](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16#))
- [Visual Studio Code](https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user)
- [Sublime Text](https://download.sublimetext.com/Sublime%20Text%20Build%203211%20x64%20Setup.exe)
- [Atom](https://atom.io/download/windows_x64)
- or whatever you find more convenient for you

#### 2.1.1 Visual Studio
If you have `Visual Studio` installed then the `CMake` configuration should be automated.
Just make sure to update the `CMake toolchain file` property in the `CMakeSettings.json`.

#### 2.1.2 Others
```
cd <repo_folder>
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE:FILEPATH="<path_to_vcpkg_repo>/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE:STRING="<configuration>" -G "Ninja" -DBUILD_TESTS:BOOL="True" .. 
```