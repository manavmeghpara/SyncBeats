# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(slave ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(slave LINK_PRIVATE hal)


# PTHREAD support
find_package(Threads REQUIRED)
target_link_libraries(slave LINK_PRIVATE Threads::Threads)


# Copy executable to final location (change `hello_world` to project name as needed)
add_custom_command(TARGET slave POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:slave>"
     "~/cmpt433/public/myApps/slave" 
  COMMENT "Copying ARM executable to public NFS directory")
