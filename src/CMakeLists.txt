link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )


file(GLOB fraktal_SRC
    "*.cpp"
)

add_executable(fraktal_kundschafter ${fraktal_SRC})


target_link_libraries(my_app PRIVATE Threads::Threads)
target_link_libraries(example 
    ${GTKMM_LIBRARIES}  )