# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(GlutProjectColisions)

# Set C standard (optional)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find GLEW and FreeGLUT using CMake's find_package
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Add include directories
include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/libraries/stb  # Relative path to stb
)

# Add source files
set(SOURCES
    main.c
    commands.c
    drawStuff.c
    physics.c
    readFile.c
    renderStuff.c
    stb.c
)

# Create an executable target
add_executable(GlutProjectColisions ${SOURCES})

# Link GLEW, FreeGLUT, and OpenGL libraries
target_link_libraries(GlutProjectColisions PRIVATE
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    m  # Link the math library
)

# Automatically copy parameterFile.txt and PNG files to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/parameterFile.txt DESTINATION ${CMAKE_BINARY_DIR})

# Copy 10 PNG files (replace "image1.png", "image2.png", etc., with your actual file names)
set(PNG_FILES
    chineseBaloon.jpg
    cover5.jpg
    hqdefault.jpg
    johnXina.jpeg
    images.jpeg
    maxresdefault.jpg
    prigozhin.jpeg
    prigozhin2.jpeg
    socialCredit.jpeg
    socialCredits.png
    Winnie.jpeg
    zelensky2.jpg
    PRC.png
)

foreach(PNG_FILE ${PNG_FILES})
    file(COPY ${CMAKE_SOURCE_DIR}/${PNG_FILE} DESTINATION ${CMAKE_BINARY_DIR})
endforeach()