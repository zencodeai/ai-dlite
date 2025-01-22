set(CYGWIN nodosfilewarning)

include_directories (
${DLITE_SOURCE_DIR}/antlr 
${DLITE_SOURCE_DIR}/antlr/include 
${DLITE_SOURCE_DIR}/shared
${DLITE_SOURCE_DIR}/dlite 
${DLITE_SOURCE_DIR}/dlparser 
${DLITE_SOURCE_DIR}/dltools 
)

add_executable(test main.cpp)

target_link_libraries(test dltools dlparser antlr dlite sqlite)
