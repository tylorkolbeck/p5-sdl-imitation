add_executable(myproj
  main.cpp
  engine/Canvas.cpp
  sketches/ExampleSketch.cpp
)

target_link_libraries(myproj PRIVATE SDL3::SDL3)

set_target_properties(myproj PROPERTIES
  OUTPUT_NAME_DEBUG debug
  OUTPUT_NAME_RELEASE myproj
)

target_include_directories(myproj
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_BINARY_DIR}/../generated"  # version header output
)

myproj_set_warnings(myproj)
