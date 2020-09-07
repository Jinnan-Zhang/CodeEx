CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)
#porject name 
set(name HelloWorld)
PROJECT(${name} LANGUAGES CXX CUDA)

# CUDA
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
find_package(CUDA REQUIRED MODULE)
if(CUDA_FOUND)
    message("CUDA FOUND")
endif()

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/
)

#add_subdirectory (src)
file(GLOB sources ${PROJECT_SOURCE_DIR}/HelloWorld.cu)
file(GLOB headers ${PROJECT_SOURCE_DIR}/HelloWorld.cuh)

# Add the executable, link it to the lib
cuda_add_executable( ${name} ${sources} ${headers})
#target_link_libraries( ${name} ${CUDA_cudadevrt_LIBRARY})