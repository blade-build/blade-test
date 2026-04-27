// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

package org.blade.greeter;

/**
 * Minimal greeter used by the java_basic smoke suite.
 *
 * Mirrors the behavior of py_basic's greeter.py so the two suites stay
 * easy to compare when debugging toolchain regressions: null/empty names
 * fall back to "world", and the format is "Hello, <name>!".
 */
public final class Greeter {

    private Greeter() {
        // utility class
    }

    public static String greet(String name) {
        String target = (name == null || name.isEmpty()) ? "world" : name;
        return "Hello, " + target + "!";
    }
}
