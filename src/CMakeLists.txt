add_executable(myproj
  main.cpp
  engine/Canvas.cpp
  engine/util/Rand.cpp
  sketches/ExampleSketch.cpp
)

target_link_libraries(myproj PRIVATE SDL3::SDL3)

add_library(sdl3_gfx STATIC
  ${CMAKE_SOURCE_DIR}/extern/SDL3_gfx/SDL3_gfxPrimitives.c
  ${CMAKE_SOURCE_DIR}/extern/SDL3_gfx/SDL3_rotozoom.c
  ${CMAKE_SOURCE_DIR}/extern/SDL3_gfx/SDL3_framerate.c
  ${CMAKE_SOURCE_DIR}/extern/SDL3_gfx/SDL3_imageFilter.c
)

target_include_directories(sdl3_gfx PUBLIC
  ${CMAKE_SOURCE_DIR}/extern/SDL3_gfx
)

# Link gfx -> SDL
# (works whether SDL is found via find_package or built as a subproject)
if(TARGET SDL3::SDL3)
  target_link_libraries(sdl3_gfx PUBLIC SDL3::SDL3)
elseif(TARGET SDL3-shared)
  target_link_libraries(sdl3_gfx PUBLIC SDL3-shared)
else()
  message(FATAL_ERROR "Could not find an SDL3 target (SDL3::SDL3 or SDL3-shared)")
endif()

target_link_libraries(sdl3_gfx PUBLIC SDL3::SDL3)

set_target_properties(myproj PROPERTIES
  OUTPUT_NAME_DEBUG debug
  OUTPUT_NAME_RELEASE myproj
)

target_include_directories(myproj
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_BINARY_DIR}/../generated"  # version header output
)

target_link_libraries(myproj PRIVATE sdl3_gfx)

myproj_set_warnings(myproj)
