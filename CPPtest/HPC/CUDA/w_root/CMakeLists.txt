CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)
#porject name 
set(name tmain)
PROJECT(${name} LANGUAGES CXX CUDA)
add_compile_options(-O2)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# CUDA
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
find_package(CUDA REQUIRED MODULE)
if(CUDA_FOUND)
    message("CUDA FOUND")
endif()

#--
#Set omp
#--
FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS} -lfftw3")
endif()


# ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net RooStats MathMore)
if(ROOT_FOUND)
    message("ROOT FOUND")
    include(${ROOT_USE_FILE})
    include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
    add_definitions(${ROOT_CXX_FLAGS})
endif()

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/cudasrc/
)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.cu)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/*/*.cuh)

cuda_add_library(mylib SHARED ${sources} ${headers})

target_compile_features(mylib PUBLIC cxx_std_14)

set_target_properties( mylib
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON
)

# Add the executable, link it to the lib
add_executable( ${name} tmain.cpp)
set_target_properties(${name} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries( ${name} mylib ${ROOT_LIBRARIES} -lcublas)