# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "brain: 1 messages, 1 services")

set(MSG_I_FLAGS "-Ibrain:/home/masta-p/aurora_test_ws/src/brain/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(brain_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" NAME_WE)
add_custom_target(_brain_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "brain" "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" ""
)

get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" NAME_WE)
add_custom_target(_brain_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "brain" "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(brain
  "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/brain
)

### Generating Services
_generate_srv_cpp(brain
  "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/brain
)

### Generating Module File
_generate_module_cpp(brain
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/brain
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(brain_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(brain_generate_messages brain_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" NAME_WE)
add_dependencies(brain_generate_messages_cpp _brain_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" NAME_WE)
add_dependencies(brain_generate_messages_cpp _brain_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(brain_gencpp)
add_dependencies(brain_gencpp brain_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS brain_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(brain
  "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/brain
)

### Generating Services
_generate_srv_eus(brain
  "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/brain
)

### Generating Module File
_generate_module_eus(brain
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/brain
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(brain_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(brain_generate_messages brain_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" NAME_WE)
add_dependencies(brain_generate_messages_eus _brain_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" NAME_WE)
add_dependencies(brain_generate_messages_eus _brain_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(brain_geneus)
add_dependencies(brain_geneus brain_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS brain_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(brain
  "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/brain
)

### Generating Services
_generate_srv_lisp(brain
  "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/brain
)

### Generating Module File
_generate_module_lisp(brain
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/brain
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(brain_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(brain_generate_messages brain_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" NAME_WE)
add_dependencies(brain_generate_messages_lisp _brain_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" NAME_WE)
add_dependencies(brain_generate_messages_lisp _brain_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(brain_genlisp)
add_dependencies(brain_genlisp brain_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS brain_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(brain
  "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/brain
)

### Generating Services
_generate_srv_nodejs(brain
  "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/brain
)

### Generating Module File
_generate_module_nodejs(brain
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/brain
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(brain_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(brain_generate_messages brain_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" NAME_WE)
add_dependencies(brain_generate_messages_nodejs _brain_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" NAME_WE)
add_dependencies(brain_generate_messages_nodejs _brain_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(brain_gennodejs)
add_dependencies(brain_gennodejs brain_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS brain_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(brain
  "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain
)

### Generating Services
_generate_srv_py(brain
  "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain
)

### Generating Module File
_generate_module_py(brain
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(brain_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(brain_generate_messages brain_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/srv/SetHormone.srv" NAME_WE)
add_dependencies(brain_generate_messages_py _brain_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/masta-p/aurora_test_ws/src/brain/msg/hormone_msg.msg" NAME_WE)
add_dependencies(brain_generate_messages_py _brain_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(brain_genpy)
add_dependencies(brain_genpy brain_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS brain_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/brain)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/brain
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(brain_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/brain)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/brain
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(brain_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/brain)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/brain
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(brain_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/brain)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/brain
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(brain_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain
    DESTINATION ${genpy_INSTALL_DIR}
    # skip all init files
    PATTERN "__init__.py" EXCLUDE
    PATTERN "__init__.pyc" EXCLUDE
  )
  # install init files which are not in the root folder of the generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain
    DESTINATION ${genpy_INSTALL_DIR}
    FILES_MATCHING
    REGEX "${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/brain/.+/__init__.pyc?$"
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(brain_generate_messages_py std_msgs_generate_messages_py)
endif()
