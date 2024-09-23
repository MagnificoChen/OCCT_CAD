cmake_minimum_required(VERSION 3.27)
project(OCCT_CAD)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 20)

#SARibbon
set(SARibbonBar_DIR "C:/Users/85147/Desktop/CodingEnv/SARibbon/bin_qt5.15.2_MSVC_x64/lib/cmake/SARibbonBar")
set(SARibbonBar_BINARY "C:/Users/85147/Desktop/CodingEnv/SARibbon/bin_qt5.15.2_MSVC_x64/bin/SARibbonBard.dll")

set(FREETYPE_BINARY "C:/Users/85147/Desktop/CodingEnv/OpenCascade/3rdParty/freetype-2.5.5-vc14-64/bin/freetype.dll")
set(OpenCASCADE_DIR "C:/Users/85147/Desktop/CodingEnv/OpenCascade/OCCT-install-release/cmake")
set(VTK_DIR "C:/Users/85147/Desktop/CodingEnv/VTK/VTK-install-debug/lib/cmake/vtk-9.1")
set(Qt5_DIR "E:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")


#查找Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core)
if (Qt5_FOUND)
    message("Qt5 Found.")
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # 添加资源文件
endif ()

set(RCC_FILES "${PROJECT_SOURCE_DIR}/image/resource.qrc")


#查找VTK
find_package(VTK REQUIRED)
if(VTK_FOUND)
    message("VTK Found.")
    file(GLOB VTK_BINARY_FILES "${VTK_PREFIX_PATH}/bin/*.dll")
    list(APPEND TOTAL_BINARIES ${VTK_BINARY_FILES})
#    list(APPEND TOTAL_LIBRARIES ${VTK_LIBRARY_FILES})
endif ()


#查找OpenCascade
find_package(OpenCASCADE REQUIRED)
if(OpenCASCADE_FOUND)
    message("OpenCASCADE Found.")
    file(GLOB OCC_BINARYS GLOB "${OpenCASCADE_BINARY_DIR}/*.dll")

    list(APPEND TOTAL_BINARIES ${FREETYPE_BINARY})
    list(APPEND TOTAL_BINARIES ${OCC_BINARYS})
    list(APPEND TOTAL_LIBRARIES ${OpenCASCADE_LIBRARIES})
    list(APPEND TOTAL_LIBRARY_DIR ${OpenCASCADE_LIBRARY_DIR})
    list(APPEND TOTAL_INCLUDE_DIR ${OpenCASCADE_INCLUDE_DIR})
endif ()

#查找SARibbon
find_package(SARibbonBar REQUIRED)
if(SARibbonBar_FOUND)
    message("SARibbonBar Found.")
    #list(APPEND TOTAL_BINARIES ${SARibbonBar_BINARIES})
    #SARibbon dll的导入有问题
    list(APPEND TOTAL_BINARIES ${SARibbonBar_BINARY})
    list(APPEND TOTAL_LIBRARIES ${SARibbonBar_LIBRARIES})
    list(APPEND TOTAL_LIBRARY_DIR ${SARibbonBar_LIBRARY_DIR})
    list(APPEND TOTAL_INCLUDE_DIR ${SARibbonBar_INCLUDE_DIR})
endif ()


file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Dialog/*.h
        ${PROJECT_SOURCE_DIR}/src/Dialog/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Dialog/Components/*.h
        ${PROJECT_SOURCE_DIR}/src/Dialog/Components/*.cpp
        ${PROJECT_SOURCE_DIR}/src/ModelTree/*.h
        ${PROJECT_SOURCE_DIR}/src/ModelTree/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Feature/*.h
        ${PROJECT_SOURCE_DIR}/src/Feature/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Render/*.h
        ${PROJECT_SOURCE_DIR}/src/Render/*.cpp
)

add_executable(OCCT_CAD ${SOURCES} ${RCC_FILES})
target_link_directories(OCCT_CAD PRIVATE ${TOTAL_LIBRARY_DIR})
target_link_libraries(OCCT_CAD Qt5::Widgets Qt5::Core Qt5::Gui SARibbonBar ${TOTAL_LIBRARIES} ${VTK_LIBRARIES})

target_include_directories(OCCT_CAD PRIVATE ${TOTAL_INCLUDE_DIR})

add_custom_command(TARGET OCCT_CAD  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TOTAL_BINARIES}
        ${PROJECT_SOURCE_DIR}/cmake-build-debug)
add_custom_command(TARGET OCCT_CAD  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TOTAL_BINARIES}
        ${PROJECT_SOURCE_DIR}/out/build)

