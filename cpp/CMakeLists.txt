add_library(DRAWING_LIB SHARED
        include/drawingDefs.hpp
        include/drawSubpixel.hpp
        src/drawSubpixel.cpp
        )
target_include_directories(DRAWING_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DRAWING_LIB ${OpenCV_LIBS})
