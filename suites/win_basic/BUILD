if blade.cc_toolchain.tool('rc') is not None:
    windows_resources(
        name = 'hello_res',
        rc_files = ['hello_gui.rc'],
        resources = ['blade-build-128.ico'],
    )
    cc_binary(
        name = 'hello_gui',
        srcs = 'hello_gui.c',
        extra_linkflags = ['/SUBSYSTEM:WINDOWS', 'user32.lib'],
        deps = [':hello_res'],
    )
