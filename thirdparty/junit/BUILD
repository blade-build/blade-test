"""JUnit 4 + Hamcrest, vendored as prebuilt jars.

Both jars were downloaded from Maven Central during workspace setup:
  * junit-4.13.2.jar           (sha1 8ac9e16d933b6fb43bc7f576336b8f4d7eb5ba12)
  * hamcrest-core-1.3.jar      (sha1 42a25dc3219429f0e5d060061f71acb49bf010a0)

Exposing them as prebuilt_java_library lets java_test targets link them via
  deps = ['//thirdparty/junit:junit']
without requiring a local Maven installation.
"""

java_library(
    name = 'hamcrest-core',
    prebuilt = True,
    binary_jar = 'hamcrest-core-1.3.jar',
    visibility = ['PUBLIC'],
)

java_library(
    name = 'junit',
    prebuilt = True,
    binary_jar = 'junit-4.13.2.jar',
    exported_deps = [':hamcrest-core'],
    visibility = ['PUBLIC'],
)
