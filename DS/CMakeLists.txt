cmake_minimum_required(VERSION 3.22)

file(GLOB SRC
     "src/*.h"
     "src/*.cpp"
)

include_directories(src)

add_library(DS ${SRC})
add_executable(DS_Test Main.cpp ) 
target_link_libraries(DS_Test DS)
# now we rename resman-bin executable to resman using target properties
set_target_properties(DS_Test
    PROPERTIES OUTPUT_NAME DS)