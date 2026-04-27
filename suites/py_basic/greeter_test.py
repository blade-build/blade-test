# Copyright (c) 2026 The Blade Authors.
# All rights reserved.
#
# Author: chen3feng <chen3feng@gmail.com>

"""Smoke tests for ``suites.py_basic.greeter``.

Uses the standard library ``unittest`` runner so the test has zero
third-party dependencies — anything extra would obscure whether a
regression is in blade's py_test wiring or in the test harness.
"""

from __future__ import annotations

import unittest

from suites.py_basic.greeter import greet


class GreetTest(unittest.TestCase):
    """Mirrors ``suites/cc_basic/hello_test.cc::HelloTest``."""

    def test_greets_by_name(self) -> None:
        self.assertEqual("Hello, blade!", greet("blade"))

    def test_empty_name_falls_back_to_world(self) -> None:
        self.assertEqual("Hello, world!", greet(""))


if __name__ == "__main__":
    unittest.main()
