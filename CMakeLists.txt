cmake_minimum_required(VERSION 4.1)

project(MyIsaac)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)

source_group("Header Files" FILES ${HEADER_FILES})
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Force static build" FORCE)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.2.20
)

FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_IMAGE
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-3.2.0
)

FetchContent_MakeAvailable(SDL3_IMAGE)

add_compile_definitions(SDL3_STATIC)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)