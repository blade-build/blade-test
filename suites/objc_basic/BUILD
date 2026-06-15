# Objective-C / Objective-C++ smoke (macOS only). blade compiles .m/.mm through
# the same cc/cxx rules; this builds a cc_library mixing .m + .mm and links the
# Foundation framework into the test.
#
# Gated on the darwin toolchain so the suite is inert on Linux/Windows -- the
# shared //suites/... run and blade-build's e2e-smoke would otherwise try to
# compile Objective-C there. The dedicated macOS `objc` CI job builds it.
if blade.cc_toolchain.target_os == 'darwin':
    cc_library(
        name='greeting',
        hdrs=['greeting.h'],
        srcs=['greeting_objc.m', 'greeting_objcxx.mm'],
        visibility='PUBLIC',
    )

    cc_test(
        name='greeting_test',
        srcs=['greeting_test.cc'],
        deps=[':greeting'],
        # ObjC objects pull in the Foundation framework at link time.
        extra_linkflags=['-framework', 'Foundation'],
    )
