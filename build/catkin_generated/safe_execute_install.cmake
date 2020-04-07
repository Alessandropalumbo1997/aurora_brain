execute_process(COMMAND "/home/masta-p/aurora_test_ws/src/brain/build/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/masta-p/aurora_test_ws/src/brain/build/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
