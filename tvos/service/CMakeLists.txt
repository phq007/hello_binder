file(GLOB project_c *.c*)
file(GLOB_RECURSE project_h *.h)

#add_library(service STATIC ${project_c} ${project_h})

if(${SERVICE_BUILD} STREQUAL "1")
	add_executable(service ${project_c} ${project_h})
	target_link_libraries(service  mdroid)
else()
	add_executable(client ${project_c} ${project_h})
	target_link_libraries(client  mdroid)
endif()



