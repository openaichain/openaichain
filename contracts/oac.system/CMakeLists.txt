file(GLOB ABI_FILES "*.abi")
configure_file("${ABI_FILES}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

add_wast_executable(TARGET oac.system
  INCLUDE_FOLDERS ${STANDARD_INCLUDE_FOLDERS}
  LIBRARIES libc++ libc oaclib oac.token
  DESTINATION_FOLDER ${CMAKE_CURRENT_BINARY_DIR}
)
