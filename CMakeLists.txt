# SET(CMAKE_VERBOSE_MAKEFILE ON)

INCLUDE(cmake/Utils.cmake)

# Mac OS X specific configuration, must be done before the PROJECT directive
IF(APPLE)
	SET(CMAKE_OSX_DEPLOYMENT_TARGET "10.6")
	SET(CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.6.sdk/")
	SET(CMAKE_OSX_ARCHITECTURES "i386;x86_64")
ENDIF()

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(Playground)

# Library configuration
SET(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
SET(LIB_BIN_DIR ${LIB_DIR}/bin)
SET(LIB_INCLUDE_DIR ${LIB_DIR}/include)
SET(LIB_SOURCE_DIR ${LIB_DIR}/src)

INCLUDE(cmake/wxWidgets.cmake)

INCLUDE(cmake/GTest.cmake)
INCLUDE(cmake/GMock.cmake)

# Include directories
# INCLUDE_DIRECTORIES("${SOURCE_DIR}" "${TEST_SOURCE_DIR}")
SET(COMPILER_IS_CLANG FALSE)
SET(COMPILER_IS_GNU FALSE)
SET(COMPILER_IS_MSVC FALSE)

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(COMPILER_IS_CLANG TRUE)
ENDIF()
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(COMPILER_IS_GNU TRUE)
ENDIF()
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    SET(COMPILER_IS_MSVC TRUE)
ENDIF()

# Compiler configuration
IF(COMPILER_IS_CLANG)
    MESSAGE(STATUS "Compiler is Clang")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -pedantic -Wno-format -Wno-variadic-macros -Wno-c++11-long-long -Wno-c99-extensions -Wno-padded -Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-vtables -Wno-float-equal -Wno-used-but-marked-unused -Wno-format-nonliteral -Wno-missing-noreturn")
ELSEIF(COMPILER_IS_GNU)
    MESSAGE(STATUS "Compiler is GNU")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-format -Wno-variadic-macros -Wno-padded -Wno-unused-parameter -Wno-float-equal -Wno-format-nonliteral -Wno-missing-noreturn")
ELSEIF(COMPILER_IS_MSVC)
    MESSAGE(STATUS "Compiler is MSVC")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /EHsc /MP /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /MP")
ELSE()
    MESSAGE(FATAL_ERROR "Unsupported compiler detected.")
ENDIF()

IF(CMAKE_GENERATOR STREQUAL "Xcode")
    # Xcode requires these flags to allow debugging
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0 -fno-inline")

    # Xcode should treat the library header files as system headers
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${LIB_INCLUDE_DIR}")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -isystem ${LIB_INCLUDE_DIR}")
ELSE()
    INCLUDE_DIRECTORIES(SYSTEM "${LIB_INCLUDE_DIR}")
ENDIF()

# Set debug mode directives
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
	ADD_DEFINITIONS(-DWXDEBUG -DDEBUG)
ENDIF()

SET(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

FILE(GLOB_RECURSE SOURCE
    "${SOURCE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

# Set up resource compilation for Windows
IF(WIN32)
    SET(SOURCE ${SOURCE} "${SOURCE_DIR}/Playground.rc")
ENDIF()

INCLUDE_DIRECTORIES(${SOURCE_DIR})

ADD_EXECUTABLE(Playground WIN32 MACOSX_BUNDLE ${SOURCE})
TARGET_LINK_LIBRARIES(Playground ${wxWidgets_LIBRARIES})

IF(APPLE)
    # Configure plist file
    SET_TARGET_PROPERTIES(Playground PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/resources/mac/Playground-Info.plist")

    # Configure the XCode generator project
    SET_XCODE_ATTRIBUTES(Playground)
ENDIF()
