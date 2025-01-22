include_directories (${DLITE_SOURCE_DIR}/shared) 
include_directories (${DLITE_SOURCE_DIR}/sqlite) 

add_library (dlite abox.cpp  factory.cpp  log.cpp  node.cpp  reasoner.cpp  store.cpp  symtable.cpp  tbox.cpp)

