CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)
#porject name 
set(name GFCN)
PROJECT(${name})

# CUDA
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
find_package(CUDA)
if(CUDA_FOUND)
    message("CUDA FOUND")
endif()

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
#INCLUDE_DIRECTORIES(
#    ${PROJECT_SOURCE_DIR}/src/
#    ${PROJECT_SOURCE_DIR}/src/cuda/
#)

#add_subdirectory (src)
file(GLOB sources *.cu)
file(GLOB_RECURSE headers *.h)

#cuda_add_library(${name} STATIC ${sources} ${headers})
cuda_add_library(${name} SHARED ${sources} ${headers})

#target_compile_features(mylib PUBLIC cxx_std_11)

#set_target_properties( mylib
    PROPERTIES CUDA_SEPARABLE_COMPILATION ON
)

# Add the executable, link it to the lib
#add_executable( ${name} tmain.cpp)
#set_property(TARGET ${name}
#    PROPERTY CUDA_SEPARABLE_COMPILATION ON    
#)
#target_link_libraries( ${name} PRIVATE mylib)