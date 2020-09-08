CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)
#porject name 
set(name tmain)
PROJECT(${name} LANGUAGES CXX CUDA)

# CUDA
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
find_package(CUDA REQUIRED MODULE)
if(CUDA_FOUND)
    message("CUDA FOUND")
endif()

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/cudasrc/
)

#add_subdirectory(src)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.cu)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/*/*.cuh)

cuda_add_library(mylib SHARED ${sources} ${headers})

# Add the executable, link it to the lib
add_executable( ${name} tmain.cpp)
target_link_libraries( ${name} mylib)