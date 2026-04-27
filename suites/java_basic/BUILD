# Smoke suite for the Java toolchain wiring (java_library + java_test).
#
# This suite intentionally mirrors cc_basic / py_basic: a trivial library
# with one pure function plus a test that exercises two behaviors. It
# protects the contract between blade-build/v3 and java_library / java_test —
# any regression in javac invocation, classpath assembly, or JUnit runner
# launch surfaces here before it reaches real users.
#
# Note on the explicit junit dep below: BLADE_ROOT declares
# java_test_config(junit_libs=['//thirdparty/junit:junit']), which is
# *intended* to auto-inject JUnit into every java_test. As of blade-build
# v3 HEAD that config key is still inert (declared in the schema but not
# consumed by JavaTest), so we list '//thirdparty/junit:junit' explicitly
# here to keep this suite honest-red/honest-green in CI. Once blade-build
# grows real auto-injection, a follow-up commit will drop the explicit
# dep and this suite will then double as the end-to-end test for that
# wiring.

java_library(
    name = 'greeter',
    srcs = glob('src/main/java/**/*.java'),
    visibility = 'PUBLIC',
)

java_test(
    name = 'greeter_test',
    srcs = glob('src/test/java/**/*.java'),
    deps = [
        ':greeter',
        '//thirdparty/junit:junit',
    ],
)
