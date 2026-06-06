# Smoke test for Windows DLL export of C++ vtable/RTTI and global data.
#
# `:foo` exports a polymorphic class and a global variable through the
# FOO_EXPORT macro, which defaults to empty -- on Windows Blade auto-generates
# the .def (no dllexport needed), and the vtable/RTTI symbols are kept in it so
# a dllimport consumer can link. `dynamic_link=True` forces `:foo` to be built
# as a shared library, so foo_test actually consumes it across the DLL boundary
# (defining FOO_EXPORT=__declspec(dllimport) on Windows; empty elsewhere).
#
# Runs on every platform: on Linux/macOS the macro stays empty and imports
# resolve through the GOT.

cc_library(
    name = 'foo',
    srcs = 'foo.cc',
    hdrs = 'foo.h',
    visibility = 'PUBLIC',
)

cc_test(
    name = 'foo_test',
    srcs = 'foo_test.cc',
    deps = ':foo',
    dynamic_link = True,
)
