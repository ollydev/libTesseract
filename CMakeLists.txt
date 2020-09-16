cmake_minimum_required(VERSION 3.15)
project(Tesseract DESCRIPTION "tesseract")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version" FORCE)

# ----------------------------- LINKER -----------------------------

file(
	GLOB TESSERACT_LIBRARIES
        "libs/*.a"
        "libs/*.lib"
    )

IF(WIN32)
    set(EXTRA_LIBRARIES
            user32
            advapi32
       )
ELSE()
    set(EXTRA_LIBRARIES
            pthread
       )
ENDIF()

# ----------------------------- SOURCES -----------------------------

set(SOURCE_LIST
        main.cpp 
        exports.cpp
   )

set(INCLUDE_DIRECTORIES
        headers
   )

# ---------------------------- COMPILE ----------------------------

add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

IF(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE /MT)
    target_link_libraries(${PROJECT_NAME} ${TESSERACT_LIBRARIES} ${EXTRA_LIBRARIES})
ELSEIF(APPLE)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -fvisibility=hidden)
    target_link_options(${PROJECT_NAME} PRIVATE -s)
    target_link_libraries(${PROJECT_NAME} ${TESSERACT_LIBRARIES} ${EXTRA_LIBRARIES})
ELSE()
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -fvisibility=hidden)
    target_link_options(${PROJECT_NAME} PRIVATE -s)
    target_link_libraries(${PROJECT_NAME} -Wl,--whole-archive ${TESSERACT_LIBRARIES} -Wl,--no-whole-archive ${EXTRA_LIBRARIES})
ENDIF()

# ---------------------------- OUTPUT NAME ------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib")
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".binary")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "tesseract")