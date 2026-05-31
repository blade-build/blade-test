# Example of `export_map`: control which symbols a shared library exports.
#
# `api.map` keeps only the public API (mylib::Create and mylib::Api) in the
# shared library's dynamic symbol table; the external-linkage helper
# mylib::Decorate is hidden by its `local: *;` clause.
#
# `export_map` is a GNU-ld feature (`--version-script`), so the filtering
# applies on Linux (and MinGW). On the MSVC toolchain the attribute is
# currently ignored -- exports are driven by a generated `.def` instead. See
# blade-build #1182 (the attribute) and #1181 (the Windows DLL path).

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
