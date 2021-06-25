if(BUILD_PYTHON_INTERFACE)

  message(STATUS "Will build the python interface")
  if(BUILD_USE_PYTHON3)
      set(PYCMD "python3")
      message(STATUS "Will use python 3")
  else(BUILD_USE_PYTHON3)
      set(PYCMD "python2")
      message(STATUS "Will use python 2")
  endif(BUILD_USE_PYTHON3)

  # Python needs row major matrices (for convenience)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEIGEN_DEFAULT_TO_ROW_MAJOR")


  #--------------------------------#
  # Includes                       #
  #--------------------------------#

  find_package(Boost COMPONENTS ALL REQUIRED)

  find_package(Python 3 REQUIRED COMPONENTS Development Interpreter NumPy)    

  #--------------------------------#
  # Library Build Instructions     #
  #--------------------------------#

  add_library(${PROJECT_NAME}py SHARED
    ${PYTHON_SOURCE_DIR}/libclusterpy.h
    ${PYTHON_SOURCE_DIR}/libclusterpy.cpp
  )

  target_link_libraries(${PROJECT_NAME}py
      Boost::python
      Python::Python
      ${PROJECT_NAME}
  )

  set_target_properties(${PROJECT_NAME}py
      PROPERTIES
      PREFIX ""
      SUFFIX ".so"
  )


  #--------------------------------#
  # Install Instructions           #
  #--------------------------------#

  # Install target
  install(TARGETS ${PROJECT_NAME}py LIBRARY DESTINATION lib/python)

endif(BUILD_PYTHON_INTERFACE)
