file(GLOB HEADERS "include/oac/wallet_plugin/*.hpp")
add_library( wallet_plugin
             wallet.cpp
             wallet_plugin.cpp
             wallet_manager.cpp
             ${HEADERS} )

target_link_libraries( wallet_plugin oac_chain appbase )
target_include_directories( wallet_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
