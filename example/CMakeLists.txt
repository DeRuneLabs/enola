set(COMMON_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/enola/tensor ${PROJECT_SOURCE_DIR}/enola/function
    ${PROJECT_SOURCE_DIR}/enola/function/activation
    ${PROJECT_SOURCE_DIR}/enola/score ${PROJECT_SOURCE_DIR}/enola/activation)

file(GLOB EXAMPLE_SOURCES "*.cc" "neural_network/*.cc" "ops/*.cc" "score/*.cc")

foreach(SOURCE_FILE IN LISTS EXAMPLE_SOURCES)
  get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

  add_executable(${TARGET_NAME} ${SOURCE_FILE})

  target_include_directories(${TARGET_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                             "Clang")
    target_compile_options(${TARGET_NAME} PRIVATE -Wno-non-template-friend
                                                  -Wno-unused-result)
  endif()
endforeach()
