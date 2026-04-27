// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

package org.blade.greeter;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

/**
 * Smoke tests for {@link Greeter}.
 *
 * Two cases by design, matching py_basic's greeter_test.py:
 *   1) default branch (null/empty -> "world")
 *   2) explicit name branch
 *
 * This protects the java_test wiring contract (javac invocation,
 * classpath assembly from java_library deps + explicit junit dep)
 * end-to-end.
 */
public class GreeterTest {

    @Test
    public void testGreetWithName() {
        assertEquals("Hello, Blade!", Greeter.greet("Blade"));
    }

    @Test
    public void testGreetDefaultsToWorld() {
        assertEquals("Hello, world!", Greeter.greet(null));
        assertEquals("Hello, world!", Greeter.greet(""));
    }
}
