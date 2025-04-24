find_package(Git)
execute_process(
  COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE NEW_GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/enola/util/version_git.hpp)
  file(READ ${CMAKE_CURRENT_SOURCE_DIR}/enola/util/version_git.hpp
       OLD_GITVERSION_CONTENTS)
  string(REGEX REPLACE ".*return \enola git-([0-9a-f]+)\".*" "\\1"
                       OLD_GIT_REVISION {$_OLD_GITVERSION_CONTENTS})
else()
  set(OLD_GIT_REVISION "notfound")
endif()

if("${OLD_GIT_VERSION}" STREQUAL "${NEW_GIT_REVISION}")
  message(STATUS "version_git.hpp update!")
else()
  file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/enola/util/version_git.hpp)
  file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/enola/util/version_git.hpp
       "return \"enola git-${NEW_GIT_REVISION}\;\n")
  message(STATUS "updated version_git.hpp")
endif()
