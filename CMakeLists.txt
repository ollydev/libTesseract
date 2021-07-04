cmake_minimum_required(VERSION 3.2)
project(Tesseract DESCRIPTION "libtesseract")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version" FORCE)

file(GLOB TESSERACT_LIBRARIES
        "libs/*.a"
        "libs/*.lib"
    )

add_library(${PROJECT_NAME} SHARED main.cpp exports.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE headers)

IF(WIN32)
	target_link_libraries(${PROJECT_NAME} -static -static-libgcc -static-libstdc++ -Wl,--whole-archive -Wl,--export-all-symbols ${TESSERACT_LIBRARIES} -Wl,--no-whole-archive ws2_32)
ELSEIF(APPLE)
	target_link_libraries(${PROJECT_NAME} -static -force_load ${TESSERACT_LIBRARIES} pthread)
ELSE()
	target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -Wl,--whole-archive ${TESSERACT_LIBRARIES} -Wl,--no-whole-archive pthread)
ENDIF()

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "tesseract64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "tesseract32")
endif()