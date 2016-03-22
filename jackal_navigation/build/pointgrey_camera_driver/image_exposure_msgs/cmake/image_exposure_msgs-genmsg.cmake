# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "image_exposure_msgs: 3 messages, 0 services")

set(MSG_I_FLAGS "-Iimage_exposure_msgs:/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg;-Istatistics_msgs:/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(image_exposure_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg" NAME_WE)
add_custom_target(_image_exposure_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "image_exposure_msgs" "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg" "statistics_msgs/Stats1D"
)

get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg" NAME_WE)
add_custom_target(_image_exposure_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "image_exposure_msgs" "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg" "image_exposure_msgs/ImageExposureStatistics:statistics_msgs/Stats1D"
)

get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg" NAME_WE)
add_custom_target(_image_exposure_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "image_exposure_msgs" "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg" "std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg"
  "${MSG_I_FLAGS}"
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg/Stats1D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/image_exposure_msgs
)
_generate_msg_cpp(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg"
  "${MSG_I_FLAGS}"
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg;/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg/Stats1D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/image_exposure_msgs
)
_generate_msg_cpp(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/image_exposure_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(image_exposure_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/image_exposure_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(image_exposure_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(image_exposure_msgs_generate_messages image_exposure_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_cpp _image_exposure_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_cpp _image_exposure_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_cpp _image_exposure_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(image_exposure_msgs_gencpp)
add_dependencies(image_exposure_msgs_gencpp image_exposure_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS image_exposure_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg"
  "${MSG_I_FLAGS}"
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg/Stats1D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/image_exposure_msgs
)
_generate_msg_lisp(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg"
  "${MSG_I_FLAGS}"
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg;/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg/Stats1D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/image_exposure_msgs
)
_generate_msg_lisp(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/image_exposure_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(image_exposure_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/image_exposure_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(image_exposure_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(image_exposure_msgs_generate_messages image_exposure_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_lisp _image_exposure_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_lisp _image_exposure_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_lisp _image_exposure_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(image_exposure_msgs_genlisp)
add_dependencies(image_exposure_msgs_genlisp image_exposure_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS image_exposure_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg"
  "${MSG_I_FLAGS}"
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg/Stats1D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs
)
_generate_msg_py(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg"
  "${MSG_I_FLAGS}"
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg;/home/master/jackal_navigation/src/pointgrey_camera_driver/statistics_msgs/msg/Stats1D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs
)
_generate_msg_py(image_exposure_msgs
  "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(image_exposure_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(image_exposure_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(image_exposure_msgs_generate_messages image_exposure_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ImageExposureStatistics.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_py _image_exposure_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/SequenceExposureStatistics.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_py _image_exposure_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/master/jackal_navigation/src/pointgrey_camera_driver/image_exposure_msgs/msg/ExposureSequence.msg" NAME_WE)
add_dependencies(image_exposure_msgs_generate_messages_py _image_exposure_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(image_exposure_msgs_genpy)
add_dependencies(image_exposure_msgs_genpy image_exposure_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS image_exposure_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/image_exposure_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/image_exposure_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(image_exposure_msgs_generate_messages_cpp statistics_msgs_generate_messages_cpp)
add_dependencies(image_exposure_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/image_exposure_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/image_exposure_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(image_exposure_msgs_generate_messages_lisp statistics_msgs_generate_messages_lisp)
add_dependencies(image_exposure_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/image_exposure_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(image_exposure_msgs_generate_messages_py statistics_msgs_generate_messages_py)
add_dependencies(image_exposure_msgs_generate_messages_py std_msgs_generate_messages_py)
