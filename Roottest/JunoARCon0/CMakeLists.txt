CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
#porject name 
PROJECT(JunoARCon)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net RooStats)
include(${ROOT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_CXX_FLAGS})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

ROOT_GENERATE_DICTIONARY(ChiDef.hh LINKDEF Link.hh)

add_library(testlib SHARED JunoARCon.cc )
target_link_libraries(testlib ${ROOT_LIBRARIES})

# Add the executable, link it to the lib
add_executable(JunoARCon JunoARCon.cc ${sources} ${headers})
target_link_libraries(JunoARCon testlib)