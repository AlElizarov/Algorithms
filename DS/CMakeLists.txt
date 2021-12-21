cmake_minimum_required(VERSION 3.22)

file(GLOB SRC
     "src/*.h"
     "src/*.cpp"
)

include_directories(src)

add_library(DS ${SRC})
add_executable(DS-bin Main.cpp ) 
target_link_libraries(DS-bin DS)
# now we rename resman-bin executable to resman using target properties
set_target_properties(DS-bin
        PROPERTIES OUTPUT_NAME DS)