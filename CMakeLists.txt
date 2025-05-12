cmake_minimum_required(VERSION 3.10)
project(MyWxApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WIN32_EXECUTABLE TRUE)


find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})


# source files
add_executable(MyWxApp 
                src/main.cpp
                src/MainFrame.h
                src/MainFrame.cpp
                src/SidePanel.h
                src/SidePanel.cpp
                src/MyGLCanvas.h
                src/MyGLCanvas.cpp
                src/OverlayButton.h
                src/OverlayButton.cpp
            )

# Link to executable
target_link_libraries(MyWxApp ${wxWidgets_LIBRARIES})

set_target_properties(MyWxApp PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>" 
)

add_custom_command(
    TARGET MyWxApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            $<TARGET_FILE_DIR:MyWxApp>/resources
)

file(GLOB RUNTIME_LIBS "${wxWidgets_LIB_DIR}/*.dll")

foreach(lib ${RUNTIME_LIBS})
    add_custom_command(TARGET MyWxApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${lib}"
                $<TARGET_FILE_DIR:MyWxApp>
        COMMENT "Copying ${lib}"
    )
endforeach()
