cmake_minimum_required(VERSION 3.10.0)
project(Raytracing VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRC_FILES 
    "src/*.cpp"
    "src/*.h"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E echo "Running Raytracer..."
#     COMMAND ${PROJECT_NAME} >> output.ppm
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )
