link_directories(
    ${GTKMM_LIBRARY_DIRS})

include_directories(
    ${GTKMM_INCLUDE_DIRS})

include_directories("${CMAKE_BINARY_DIR}/../include")
file(GLOB fraktal_SRC
    "*.cpp"
)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
add_executable(fraktal_kundschafter ${fraktal_SRC})

target_link_libraries(fraktal_kundschafter PRIVATE Threads::Threads)
target_link_libraries(fraktal_kundschafter
    ${GTKMM_LIBRARIES})
target_link_libraries(fraktal_kundschafter OpenCL::OpenCL)