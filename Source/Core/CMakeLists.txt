file(GLOB CORE_PRIVATE_SOURCES Private/*.h Private/*.cpp)
file(GLOB CORE_PUBLIC_SOURCES Public/*.h)

add_library(Core ${CORE_PRIVATE_SOURCES} ${CORE_PUBLIC_SOURCES})
target_include_directories(Core PRIVATE Private)
target_include_directories(Core PUBLIC Public)
