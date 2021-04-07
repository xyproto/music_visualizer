cmake_minimum_required(VERSION 3.3)

project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17 -D_REENTRANT -DLINUX")

set(SOURCE_FILES
    src/main.cpp
    src/Window.cpp
    src/ShaderConfig.cpp
    src/ShaderPrograms.cpp
    src/Renderer.cpp
    src/AudioStreams/LinuxAudioStream.cpp
    src/AudioStreams/WavAudioStream.cpp
    libs/SimpleFileWatcher/source/FileWatcher.cpp
    libs/SimpleFileWatcher/source/FileWatcherLinux.cpp
)

include_directories(
    .
    src
    libs/SimpleFileWatcher/include
    /usr/include/ffts
)

add_subdirectory(libs/SimpleFileWatcher)

add_executable(main ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(main ffts glfw GLEW GLU GL pulse-simple pulse pthread stdc++fs)
