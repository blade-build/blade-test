# Smoke suite for blade's resource_library rule.
#
# resource_library bundles arbitrary data files into the binary as
# C arrays (via xxd -i) plus an index table. The generator contract
# (see src/blade/builtin_tools.py:_generate_resource_index) exposes,
# for each source file, the following symbols:
#
#     extern const char     RESOURCE_<regular_name>[<size>];
#     extern const unsigned RESOURCE_<regular_name>_len;
#
# and for the library as a whole:
#
#     struct BladeResourceEntry { const char* name;
#                                 const char* data;
#                                 unsigned int size; };
#     extern const struct BladeResourceEntry RESOURCE_INDEX_<full>[];
#     extern const unsigned                  RESOURCE_INDEX_<full>_len;
#
# where <regular_name> is the source path with every non
# [A-Za-z0-9_] character replaced by '_', and <full> is the same
# transform applied to <path>/<name>.
#
# This suite links these raw symbols directly; we intentionally do
# not rely on the STATIC_RESOURCE() convenience macro because that
# lives in the external (poppy) tree, not in blade-build itself.

resource_library(
    name = 'greetings',
    srcs = [
        'data/greeting.txt',
        'data/config.json',
        'subdir/banner.txt',
    ],
)

cc_test(
    name = 'greeter_test',
    srcs = 'greeter_test.cc',
    deps = ':greetings',
    # Stage the raw source files next to the test binary so we can
    # compare the embedded bytes against what is on disk. Blade runs
    # cc_test in <binary>.runfiles/ with pkg-relative paths preserved.
    testdata = [
        'data/greeting.txt',
        'data/config.json',
        'subdir/banner.txt',
    ],
)
