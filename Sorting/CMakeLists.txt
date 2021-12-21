cmake_minimum_required(VERSION 3.22)

file(GLOB SRC
     "src/*.h"
     "src/*.cpp"
)

include_directories(src
                    ../DS/src)

add_executable(Sorting ${SRC})
target_link_libraries(Sorting DS)