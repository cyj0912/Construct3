file(GLOB Resource_PRIVATE_SOURCES Private/*.h Private/*.cpp)
file(GLOB Resource_PUBLIC_SOURCES Public/*.h)

add_library(Resource ${Resource_PRIVATE_SOURCES} ${Resource_PUBLIC_SOURCES})
c3_config_module(Resource Core)
target_include_directories(Resource PRIVATE Private)
target_include_directories(Resource PUBLIC Public)
target_link_libraries(Resource PRIVATE assimp)
target_link_libraries(Resource PRIVATE glm)
