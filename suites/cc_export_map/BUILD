# Example of `export_map`: control which symbols a shared library exports.
#
# `api.map` keeps only the public API (mylib::Create and mylib::Api) in the
# shared library's dynamic symbol table; the external-linkage helper
# mylib::Decorate is hidden by its `local: *;` clause.
#
# On Linux `export_map` is a GNU-ld `--version-script`. On MSVC there is no
# such option, so Blade applies the map by filtering the auto-generated `.def`
# (matching each symbol's demangled name); name-only demangling means overloads
# collapse and quoted signatures match by name only. See blade-build #1182 (the
# attribute), #1181 (the Windows DLL path) and #1194 (the MSVC translation).

cc_library(
    name = 'api',
    srcs = 'api.cc',
    hdrs = 'api.h',
    export_map = 'api.map',
    visibility = 'PUBLIC',
)

# dynamic_link forces `:api` to be built as a shared library, so export_map is
# actually exercised; the test then loads it and calls the public API.
cc_test(
    name = 'api_test',
    srcs = 'api_test.cc',
    deps = ':api',
    dynamic_link = True,
)
