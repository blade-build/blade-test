# Copyright (c) 2026 The Blade Authors.
# All rights reserved.
#
# Author: chen3feng <chen3feng@gmail.com>

"""Trivial greeting helpers.

Kept intentionally minimal — this module exists so the py_basic suite
can exercise blade-build's py_library + py_test wiring end-to-end, not
to provide production logic.
"""

from __future__ import annotations


def greet(name: str) -> str:
    """Return ``"Hello, <name>!"`` for non-empty names, else ``"Hello, world!"``.

    Mirrors ``suites/cc_basic/hello.cc::Greet`` so the two suites stay
    symmetrical and easy to compare when diagnosing cross-language
    regressions.
    """
    target = name if name else "world"
    return f"Hello, {target}!"
