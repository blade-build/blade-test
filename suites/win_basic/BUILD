if blade.path.sep == '\\':
    _res = blade.path.join(blade.current_source_dir(), 'hello_gui.res')
    cc_binary(
        name = 'hello_gui',
        srcs = 'hello_gui.c',
        extra_linkflags = ['/SUBSYSTEM:WINDOWS', 'user32.lib', _res],
    )
