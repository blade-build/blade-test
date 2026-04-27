# blade-test

End-to-end regression workspace for [blade-build]
(https://github.com/blade-build/blade-build), exercising each
supported toolchain (C/C++, proto, thrift, Java, Python, Go, ...)
from a real user's perspective.

This repo is organized as a sibling checkout of `blade-build`:

```
parent/
├── blade-build/   (the build tool)
└── blade-test/    (this repo)
```

Override the discovery path with `BLADE_BUILD_DIR=/path/to/blade-build`
if you keep them elsewhere.

## Host requirements

See the comments at the top of [`blade.sh`](./blade.sh) for the full
list. The essentials:

* `python3 >= 3.10` on `PATH`. If your default `python3` is older, set
  `BLADE_PYTHON_INTERPRETER` to a newer one in your shell:

  ```bash
  export BLADE_PYTHON_INTERPRETER=/opt/homebrew/bin/python3.12
  ```

  (The blade-build launcher honors this env var since the v3 bugfix.)
* A C/C++ toolchain (clang on macOS, gcc on Linux) plus `ninja`.
* `googletest` installed under the brew/system prefix referenced in
  [`BLADE_ROOT`](./BLADE_ROOT) (`brew install googletest` on macOS;
  `apt install libgtest-dev` on Ubuntu, then build and install the
  static archives).
* For individual suites: `protoc`, `thrift`, `swig`, `mvn`, `scalac`,
  `javac`, `go` as their `BUILD` files require. Only install what a
  suite you actually want to run needs.

## Running a suite

```bash
./blade.sh test //suites/cc_basic/...
```

Expected tail:

```
[  PASSED  ] 2 tests.
Blade(notice): All 1 tests passed!
```

## Layout

* `BLADE_ROOT` — toolchain config for the whole workspace (gtest,
  protobuf, thrift, JUnit wiring).
* `blade.sh` — thin wrapper that execs the sibling blade-build
  launcher.
* `suites/` — one directory per toolchain/feature area. Current:
  * `suites/cc_basic/` — minimal C/C++ + gtest smoke.

  More suites (proto/thrift/java/py/go/...) will land in follow-up
  PRs.
* `thirdparty/` — vendored third-party artifacts (currently JUnit
  jars for the Java suites).
