# Prelude

C++ project template. Currently requires CMake 3.15+. Default standard is C++23.

```sh
# Add to empty Git repository.
git init
git submodule add https://github.com/bridgekat/prelude extern/prelude

# Copy initial files (not necessary; or directly include CMake scripts from `cmake/`.)
sh extern/prelude/misc/init.sh

# Edit `CMakeLists.txt`.
```

See: [https://cliutils.gitlab.io/modern-cmake/](https://cliutils.gitlab.io/modern-cmake/)

```sh
# Configure and build.
cmake -S . -B build
cmake --build build -j 4
```
