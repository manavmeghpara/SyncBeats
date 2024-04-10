# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(master ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(master LINK_PRIVATE hal)

# ALSA support
find_package(ALSA REQUIRED)
target_link_libraries(master LINK_PRIVATE asound)

# PTHREAD support
find_package(Threads REQUIRED)
target_link_libraries(master LINK_PRIVATE Threads::Threads)

# mpg123 library
find_library(MPG123_LIBRARY mpg123 HINTS $ENV{HOME}/cmpt433/public/mpg123_lib_BBB)
target_link_libraries(master LINK_PRIVATE ${MPG123_LIBRARY})

# LAME library
find_library(LAME_LIBRARY mp3lame HINTS $ENV{HOME}/cmpt433/public/mp3lame_lib_BBB)
target_link_libraries(master LINK_PRIVATE ${LAME_LIBRARY})
    


# Copy executable to final location (change `master` to project name as needed)
add_custom_command(TARGET master POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:master>"
     "~/cmpt433/public/myApps/master" 
  COMMENT "Copying ARM executable to public NFS directory")

  add_custom_command(TARGET master POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
     "${CMAKE_SOURCE_DIR}/song-files"
     "~/cmpt433/public/myApps/song-files" 
  COMMENT "Copying WAVE files to public NFS directory")

  add_custom_command(TARGET master POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
     "${CMAKE_SOURCE_DIR}/project-server"
     "~/cmpt433/public/myApps/project-server-copy" 
  COMMENT "Copying NODE files to public NFS directory")