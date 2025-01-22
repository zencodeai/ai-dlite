include_directories (${DLITE_SOURCE_DIR}/antlr) 
include_directories (${DLITE_SOURCE_DIR}/antlr/include) 
include_directories (${DLITE_SOURCE_DIR}/shared) 
include_directories (${DLITE_SOURCE_DIR}/dlite) 
include_directories (${DLITE_SOURCE_DIR}/dltools) 

set(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})
set(CYGWIN nodosfilewarning)

add_library (dlparser OntologyLexer.c OntologyParser.c context.cpp dlparser.cpp)
