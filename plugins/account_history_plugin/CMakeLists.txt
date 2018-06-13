file(GLOB HEADERS "include/oac/account_history_plugin/*.hpp")
add_library( account_history_plugin
             account_history_plugin.cpp
             ${HEADERS} )

target_link_libraries( account_history_plugin chain_plugin oac_chain appbase )
target_include_directories( account_history_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
