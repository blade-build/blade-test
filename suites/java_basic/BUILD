# Smoke suite for the Java toolchain wiring (java_library + java_test).
#
# This suite intentionally mirrors cc_basic / py_basic: a trivial library
# with one pure function plus a test that exercises two behaviors. It
# protects the contract between blade-build/v3 and java_library / java_test —
# any regression in javac invocation, classpath assembly, or JUnit runner
# launch surfaces here before it reaches real users.
#
# Double duty as the cross-repo e2e for blade-build#1101:
# BLADE_ROOT declares
#   java_test_config(junit_libs=['//thirdparty/junit:junit'])
# and blade-build v3 auto-injects every label in that list into each
# java_test's implicit deps (see JavaTest._apply_junit_libs_from_config
# in blade-build's src/blade/java_targets.py). The `greeter_test`
# target below therefore omits '//thirdparty/junit:junit' from its
# `deps` on purpose — if the auto-injection ever regresses, javac
# here will fail with "cannot find symbol: class Assert" and the
# Suites-smoke workflow turns red. That is precisely what this suite
# is meant to catch, so please do not "fix" the red by re-adding the
# explicit dep; fix it in blade-build instead.

java_library(
    name = 'greeter',
    srcs = glob('src/main/java/**/*.java'),
    visibility = 'PUBLIC',
)

java_test(
    name = 'greeter_test',
    srcs = glob('src/test/java/**/*.java'),
    # JUnit is auto-injected via java_test_config.junit_libs; see the
    # top-of-file comment for the rationale.
    deps = [
        ':greeter',
    ],
)
