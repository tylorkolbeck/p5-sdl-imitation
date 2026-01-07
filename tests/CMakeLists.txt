add_executable(smoke_test smoke_test.cpp)
myproj_set_warnings(smoke_test)

add_test(NAME smoke_test COMMAND smoke_test)
