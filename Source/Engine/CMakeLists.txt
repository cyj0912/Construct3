file(GLOB ENGINE_PRIVATE_SOURCES Private/*.h Private/*.cpp)
file(GLOB ENGINE_PUBLIC_SOURCES Public/*.h)

add_library(Engine ${ENGINE_PRIVATE_SOURCES} ${ENGINE_PUBLIC_SOURCES})
target_include_directories(Engine PRIVATE Private)
target_include_directories(Engine PUBLIC Public)
target_link_libraries(Engine PRIVATE glm)
target_link_libraries(Engine PRIVATE Core)
