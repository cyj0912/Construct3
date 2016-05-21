set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)

file(GLOB EDITOR_SOURCES *.h *.cpp *.ui)
add_executable(Editor ${EDITOR_SOURCES})
if(WIN32)
	set_target_properties(Editor PROPERTIES WIN32_EXECUTABLE ON)
endif()

target_link_libraries(Editor PRIVATE Qt5::Widgets)
target_link_libraries(Editor PRIVATE Core)
target_link_libraries(Editor PRIVATE Engine)
target_link_libraries(Editor PRIVATE OpenGL3Render)
target_link_libraries(Editor PRIVATE glm)
target_link_libraries(Editor PRIVATE glad)
