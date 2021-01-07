# add the main library
add_library(MathFunctions MathFunctions.cxx)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
# state that we depend on our binary dir to find Table.h
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)
   target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
   add_executable(MakeTable MakeTable.cxx)

   # add the command to generate the source code
   add_custom_command(
	     OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	     COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	     DEPENDS MakeTable
	     )

  add_library(SqrtLibrary STATIC
	  mysqrt.cxx
	  ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	  )
  target_include_directories(SqrtLibrary PRIVATE 
	  ${CMAKE_CURRENT_BINARY_DIR}
	  )
  set_target_properties(SqrtLibrary PROPERTIES 
	  POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
	  )
  target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()
target_compile_definitions(MathFunctions PRIVATE "EXPORING_MYMATH")

# install rules
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
