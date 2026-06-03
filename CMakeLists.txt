add_library(DRAWING_LIB SHARED
        include/drawingDefs.hpp
        include/drawSubpixel.hpp
        src/drawSubpixel.cpp
        )
target_include_directories(DRAWING_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DRAWING_LIB ${OpenCV_LIBS})

add_library(DRAW_MEASURING_LIB SHARED
        include/drawHandles.hpp
        include/drawMeasuring.hpp
        include/drawFuzzy.hpp
        src/drawHandles.cpp
        src/drawMeasuring.cpp
        src/drawFuzzy.cpp)
target_include_directories(DRAW_MEASURING_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DRAW_MEASURING_LIB DRAWING_LIB M1D_LIB)

add_library(DRAW_METROLOGY_LIB SHARED
        include/drawMetrology.hpp
        src/drawMetrology.cpp)
target_include_directories(DRAW_METROLOGY_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DRAW_METROLOGY_LIB DRAW_MEASURING_LIB M2D_LIB)

add_library(DRAW_BEAD_LIB SHARED
        include/drawBead.hpp
        src/drawBead.cpp)
target_include_directories(DRAW_BEAD_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DRAW_BEAD_LIB DRAWING_LIB BEAD_LIB)
