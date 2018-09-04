set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (NOT ENVFILE)
  if (DEFINED ENV{ENVFILE})
    set(ENVFILE $ENV{ENVFILE})
  else()
    set(ENVFILE "/.env")
  endif()
endif()

configure_file(
  reactnativeconfig.cpp.in
  ${CMAKE_CURRENT_SOURCE_DIR}/reactnativeconfig.cpp
)

set(REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_TYPE_NAMES ${REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_TYPE_NAMES}
                                                     \"ReactNativeConfig\" PARENT_SCOPE)

set(REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_SRC ${REACT_NATIVE_DESKTOP_EXTERNAL_MODULES_SRC}
                                              ${CMAKE_CURRENT_SOURCE_DIR}/reactnativeconfig.cpp PARENT_SCOPE)
