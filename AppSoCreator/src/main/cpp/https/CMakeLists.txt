
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(SO_IMPORT_PATH ${PROJECT_SOURCE_DIR}/../../../../../LibJniCppCommon/libs/${ANDROID_ABI})
set(SO_IMPORT_PATH2 ${PROJECT_SOURCE_DIR}/../../jniLibs/${ANDROID_ABI})


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(./include
${PROJECT_SOURCE_DIR}/../../../../../LibJniCppCommon/src/main/cpp/jnihelper/
)

#文件夹方式
#AUX_SOURCE_DIRECTORY(./c/ SRC_LIST)
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

add_library( # Sets the name of the library.
             httpsJni
             SHARED

             httpsJni.cpp
<<<<<<< HEAD

=======
             c/http.c
             c/https.c
             c/socket.c
             c/url.c
>>>>>>> 1eb7af2b6d52a30e4c4921cb9481c4cce3bfa3b8
             //${SRC_LIST}
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
add_library(
        jnicom
        SHARED
        IMPORTED
)

set_target_properties(jnicom
        PROPERTIES IMPORTED_LOCATION
        ${SO_IMPORT_PATH}/libjnihelper.so)

        add_library(
                https
                SHARED
                IMPORTED
        )
        set_target_properties(https
                PROPERTIES IMPORTED_LOCATION
                ${SO_IMPORT_PATH2}/libhttps.so)


target_link_libraries( # Specifies the target library.
                       httpsJni
<<<<<<< HEAD
                       https
                        jnicom
=======
jnicom
#crypto
ssl
>>>>>>> 1eb7af2b6d52a30e4c4921cb9481c4cce3bfa3b8
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )