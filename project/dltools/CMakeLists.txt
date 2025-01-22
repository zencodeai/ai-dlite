include_directories (${DLITE_SOURCE_DIR}/antlr) 
include_directories (${DLITE_SOURCE_DIR}/antlr/include) 
include_directories (${DLITE_SOURCE_DIR}/shared) 
include_directories (${DLITE_SOURCE_DIR}/dlite) 
include_directories (${DLITE_SOURCE_DIR}/dlparser) 

add_library (dltools fmtinfix.cpp session.cpp)
