cmake_minimum_required (VERSION 2.8) 

project (DLITE) 

add_subdirectory (sqlite) 
add_subdirectory (antlr) 
add_subdirectory (xmlParser) 

add_subdirectory (dlite) 
add_subdirectory (dlparser) 
add_subdirectory (dltools) 
add_subdirectory (dlutil) 
add_subdirectory (test) 
