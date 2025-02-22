# toolchain-linux.cmake
# Target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)  # Optional: Specify the target architecture

# Specify the cross-compiler
set(CMAKE_C_COMPILER x86_64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER x86_64-linux-gnu-g++)

# Specify the root directory for the target environment
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-linux-gnu)

# Adjust the default behavior of FIND_XXX() commands
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  # Look for programs in the host system
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)   # Look for libraries in the target system
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)   # Look for headers in the target system

# Optional: Add compiler and linker flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=x86-64 -mtune=generic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64 -mtune=generic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
