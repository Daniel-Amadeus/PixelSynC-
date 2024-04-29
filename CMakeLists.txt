cmake_minimum_required(VERSION 3.28.0)

project(PixelSynCPlusPlus)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)
qt_standard_project_setup()

# main executable
add_executable(${PROJECT_NAME}
  main.cpp
  mainwindow.cpp
  glwidget.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Widgets
  Qt6::OpenGLWidgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runUnitTests unitTests.cpp)
target_link_libraries(runUnitTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runUnitTests)