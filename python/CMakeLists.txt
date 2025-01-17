if(BUILD_PYTHON_INTERFACE)

  message(STATUS "Will build the python interface")

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
      Boost::numpy
      Python::Python
      ${PROJECT_NAME}
  )

  target_include_directories(${PROJECT_NAME}py PRIVATE ${Python_NumPy_INCLUDE_DIRS})

  set_target_properties(${PROJECT_NAME}py
      PROPERTIES
      PREFIX "lib"
      SUFFIX ".so"
  )


  #--------------------------------#
  # Install Instructions           #
  #--------------------------------#

  # Install target
  install(TARGETS ${PROJECT_NAME}py LIBRARY DESTINATION lib/python)

endif(BUILD_PYTHON_INTERFACE)
