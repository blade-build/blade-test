# A C++ cc_library exposing an extern "C" entry point -- the only shape cgo (C
# ABI) can call. Exercises Blade adding the C++ runtime to the cgo link.
cc_library(
    name = 'greeter_cxx',
    srcs = ['greeter_cxx.cc'],
    hdrs = ['greeter_cxx.h'],
    visibility = ['PUBLIC'],
)
