// Minimal test framework — self-contained, no external dependencies.
//
// Provides the gtest-compatible macros the blade-test suites actually use
// (TEST, EXPECT_EQ/TRUE/FALSE, ASSERT_EQ/TRUE/FALSE/GE, ADD_FAILURE)
// plus a test_main library that runs every registered test.

#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace blade_test {

// ---- test registry --------------------------------------------------------

struct Test {
    const char* suite;
    const char* name;
    std::function<void()> body;
};

inline std::vector<Test>& GetAllTests() {
    static std::vector<Test> tests;
    return tests;
}

struct AutoRegister {
    AutoRegister(const char* suite, const char* name, std::function<void()> fn) {
        GetAllTests().push_back({suite, name, std::move(fn)});
    }
};

// ---- failure reporting ----------------------------------------------------

inline int g_failures = 0;

inline void RecordFailure(const char* file, int line, const char* expr) {
    g_failures++;
    std::cerr << file << ":" << line << ": Failure" << std::endl;
    std::cerr << "  " << expr << std::endl;
}

inline void RecordFailure(const char* file, int line,
                          const char* expr, const std::string& msg) {
    g_failures++;
    std::cerr << file << ":" << line << ": Failure" << std::endl;
    std::cerr << "  " << expr << std::endl;
    if (!msg.empty())
        std::cerr << "  " << msg << std::endl;
}

class FailureStream {
public:
    FailureStream(const char* file, int line, const char* expr)
        : file_(file), line_(line), expr_(expr) {}

    ~FailureStream() {
        if (!used_) RecordFailure(file_, line_, expr_);
        else        RecordFailure(file_, line_, expr_, ss_.str());
    }

    template <typename T>
    FailureStream& operator<<(const T& val) {
        used_ = true;
        ss_ << val;
        return *this;
    }

    // Required for operator<<(std::endl) and other manipulators.
    FailureStream& operator<<(std::ostream& (*pf)(std::ostream&)) {
        used_ = true;
        ss_ << pf;
        return *this;
    }

    // Allow operator<< with std::string_view (C++17) via implicit conversion.
    FailureStream& operator<<(const char* s) {
        used_ = true;
        ss_ << s;
        return *this;
    }

private:
    const char* file_;
    int line_;
    const char* expr_;
    std::ostringstream ss_;
    bool used_ = false;
};

// ---- test runner (called from test_main) ----------------------------------

inline int RunAllTests() {
    std::cerr << "[==========] Running "
              << GetAllTests().size() << " tests." << std::endl;
    for (const auto& t : GetAllTests()) {
        std::cerr << "[ RUN      ] " << t.suite << "." << t.name << std::endl;
        int before = g_failures;
        t.body();
        int after = g_failures;
        if (after == before)
            std::cerr << "[       OK ] " << t.suite << "." << t.name << std::endl;
        else
            std::cerr << "[  FAILED  ] " << t.suite << "." << t.name << std::endl;
    }
    std::cerr << "[==========] " << GetAllTests().size() << " tests ran." << std::endl;
    std::cerr << "[  PASSED  ] " << (GetAllTests().size() - g_failures) << " tests." << std::endl;
    if (g_failures > 0) {
        std::cerr << "[  FAILED  ] " << g_failures << " tests." << std::endl;
        return 1;
    }
    return 0;
}

}  // namespace blade_test

// ---- macros (gtest-compatible names) ---------------------------------------

#define BLADE_TF_CONCAT_(a, b) a##b
#define BLADE_TF_CONCAT(a, b) BLADE_TF_CONCAT_(a, b)

#define TEST(suite, name)                                        \
    static void BLADE_TF_CONCAT(_blade_test_fn_, __LINE__)();    \
    static ::blade_test::AutoRegister                            \
        BLADE_TF_CONCAT(_blade_test_reg_, __LINE__)(             \
            #suite, #name,                                       \
            BLADE_TF_CONCAT(_blade_test_fn_, __LINE__));         \
    static void BLADE_TF_CONCAT(_blade_test_fn_, __LINE__)()

#define BLADE_TF_EXPECT_(cond) do {                    \
    if (!(cond)) {                                     \
        ::blade_test::RecordFailure(                   \
            __FILE__, __LINE__, "Expected: " #cond);   \
    }                                                  \
} while (0)

#define BLADE_TF_ASSERT_(cond) do {                    \
    if (!(cond)) {                                     \
        ::blade_test::RecordFailure(                   \
            __FILE__, __LINE__, "Expected: " #cond);   \
        return;                                        \
    }                                                  \
} while (0)

#define EXPECT_EQ(a, b)  BLADE_TF_EXPECT_((a) == (b))
#define EXPECT_TRUE(a)   BLADE_TF_EXPECT_(a)
#define EXPECT_FALSE(a)  BLADE_TF_EXPECT_(!(a))

#define ASSERT_EQ(a, b)  BLADE_TF_ASSERT_((a) == (b))
#define ASSERT_TRUE(a)   BLADE_TF_ASSERT_(a)
#define ASSERT_FALSE(a)  BLADE_TF_ASSERT_(!(a))
#define ASSERT_GE(a, b)  BLADE_TF_ASSERT_((a) >= (b))

#define ADD_FAILURE() \
    ::blade_test::FailureStream(__FILE__, __LINE__, "")
