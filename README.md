# Template Library Extensions

The repository of template stuff that I've created more than once, so now it's here.

## Quickstart

```
include(FetchContent)

FetchContent_Declare(
    template-library-extensions
    GIT_REPOSITORY https://github.com/mgomes0/template-library-extentions.git
    GIT_TAG        main   # or a specific tag/commit SHA
)
FetchContent_MakeAvailable(template-library-extensions)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE tlex::tlex)
```
