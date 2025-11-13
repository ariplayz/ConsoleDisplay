project('ConsoleDisplay', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_MESON_LIBRARY']

shared_library('ConsoleDisplay', 'library.cpp',
               install : true,
               cpp_args : lib_args
)

# Install public headers so downstream projects can include them.
install_headers('library.h', subdir: 'ConsoleDisplay')

# Install manual page (section 3, library functions)
install_man('ConsoleDisplay.3')