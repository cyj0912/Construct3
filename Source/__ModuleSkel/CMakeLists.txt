file(GLOB OpenGL3Render_PRIVATE_SOURCES Private/*.h Private/*.cpp)
file(GLOB OpenGL3Render_PUBLIC_SOURCES Public/*.h)

add_library(OpenGL3Render ${OpenGL3Render_PRIVATE_SOURCES} ${OpenGL3Render_PUBLIC_SOURCES})
target_include_directories(OpenGL3Render PRIVATE Private)
target_include_directories(OpenGL3Render PUBLIC Public)
