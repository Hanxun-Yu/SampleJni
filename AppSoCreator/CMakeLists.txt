
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

cmake_minimum_required(VERSION 3.4.1)

include_directories(./src/main/cpp/ )
#文件夹方式
#AUX_SOURCE_DIRECTORY(./src/main/cpp/ SRC_LIST)
#add_library( # Sets the name of the library.
#             native-lib
#
#             # Sets the library as a shared library.
#             SHARED
#
#             # Provides a relative path to your source file(s).
#             #src/main/cpp/native-lib.cpp
#             #.cpp
#             ${SRC_LIST}
#             )
AUX_SOURCE_DIRECTORY(./src/main/cpp/sqlite sqlite)

add_library( # Sets the name of the library.
             methodTest
             SHARED

             src/main/cpp/methodTest.cpp
             src/main/cpp/ExternalCTest.cpp
             ${sqlite}
             )


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       methodTest

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )