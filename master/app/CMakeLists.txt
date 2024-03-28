# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(hello_world ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(hello_world LINK_PRIVATE hal)

# ALSA support
find_package(ALSA REQUIRED)
target_link_libraries(hello_world LINK_PRIVATE asound)

# PTHREAD support
find_package(Threads REQUIRED)
target_link_libraries(hello_world LINK_PRIVATE Threads::Threads)

# mpg123 library
find_library(MPG123_LIBRARY mpg123 HINTS $ENV{HOME}/cmpt433/public/mpg123_lib_BBB)
target_link_libraries(hello_world LINK_PRIVATE ${MPG123_LIBRARY})


# Copy executable to final location (change `hello_world` to project name as needed)
add_custom_command(TARGET hello_world POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:hello_world>"
     "~/cmpt433/public/myApps/hello_world" 
  COMMENT "Copying ARM executable to public NFS directory")

  add_custom_command(TARGET hello_world POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
     "${CMAKE_SOURCE_DIR}/song-files"
     "~/cmpt433/public/myApps/song-files" 
  COMMENT "Copying WAVE files to public NFS directory")