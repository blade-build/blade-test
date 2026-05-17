// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Smoke test for blade's resource_library rule.
//
// The resource_library target `:greetings` declares three source
// files. blade's generator (src/blade/builtin_tools.py) exposes each
// of them as a pair of raw C symbols
//     const char     RESOURCE_<var>[<size>];
//     const unsigned RESOURCE_<var>_len;
// plus an index table
//     const BladeResourceEntry RESOURCE_INDEX_<full>[];
//     const unsigned           RESOURCE_INDEX_<full>_len;
// where <var>  = regular_variable_name(source_path) and
//       <full> = regular_variable_name("<pkg_path>/<target_name>").
//
// The tests below lock down that contract without going through the
// external STATIC_RESOURCE() macro (which lives in poppy, not in
// blade-build itself).

#include "suites/resource_basic/greetings.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <sys/stat.h>

#include "suites/test_framework/test_framework.h"

namespace {

// Slurp the entire contents of `path` into a std::string, or return
// an empty string and fail the current test on I/O error.
std::string ReadFileFromDisk(const char* path) {
    FILE* fp = std::fopen(path, "rb");
    if (fp == nullptr) {
        ADD_FAILURE() << "failed to open " << path;
        return {};
    }
    std::fseek(fp, 0, SEEK_END);
    long size = std::ftell(fp);
    std::fseek(fp, 0, SEEK_SET);
    std::string out;
    out.resize(static_cast<size_t>(size));
    if (size > 0) {
        size_t got = std::fread(&out[0], 1, static_cast<size_t>(size), fp);
        EXPECT_EQ(got, static_cast<size_t>(size));
    }
    std::fclose(fp);
    return out;
}

off_t StatSize(const char* path) {
    struct stat st{};
    if (::stat(path, &st) != 0) {
        ADD_FAILURE() << "failed to stat " << path;
        return -1;
    }
    return st.st_size;
}

}  // namespace

// Case 1 — bytes embedded in the binary match the source file on disk.
//
// The test binary runs with its cwd set to <exe>.runfiles, where
// blade stages the `testdata` entries declared in BUILD. Entries use
// pkg-relative destinations (no `suites/resource_basic/` prefix).
TEST(ResourceBasic, TextResourceMatchesSourceFile) {
    const std::string on_disk = ReadFileFromDisk("data/greeting.txt");
    ASSERT_FALSE(on_disk.empty());

    const std::string embedded(
            RESOURCE_suites_resource_basic_data_greeting_txt,
            RESOURCE_suites_resource_basic_data_greeting_txt
                    + sizeof(RESOURCE_suites_resource_basic_data_greeting_txt));
    EXPECT_EQ(embedded, on_disk);
}

// Case 2 — the companion *_len symbol matches the real file size.
TEST(ResourceBasic, ResourceLengthExposed) {
    const off_t size = StatSize("data/greeting.txt");
    ASSERT_GE(size, 0);
    EXPECT_EQ(RESOURCE_suites_resource_basic_data_greeting_txt_len,
              static_cast<unsigned>(size));
    EXPECT_EQ(sizeof(RESOURCE_suites_resource_basic_data_greeting_txt),
              static_cast<size_t>(size));
}

// Case 3 — a source file in a subdirectory is still exposed, with
// '/' flattened to '_' in the variable name (regular_variable_name).
TEST(ResourceBasic, SubdirResourcePathIsFlattened) {
    const std::string on_disk = ReadFileFromDisk("subdir/banner.txt");
    ASSERT_FALSE(on_disk.empty());

    const std::string embedded(
            RESOURCE_suites_resource_basic_subdir_banner_txt,
            RESOURCE_suites_resource_basic_subdir_banner_txt
                    + RESOURCE_suites_resource_basic_subdir_banner_txt_len);
    EXPECT_EQ(embedded, on_disk);
}

// Case 4 — the generated index table enumerates every source, each
// entry's data pointer + size agrees with the corresponding raw
// symbols, and the *_len count matches the number of srcs in BUILD.
TEST(ResourceBasic, IndexTableEnumeratesAllEntries) {
    // 3 srcs declared in BUILD.
    ASSERT_EQ(RESOURCE_INDEX_suites_resource_basic_greetings_len, 3u);

    // Build a map-free lookup: walk the table and assert every
    // expected entry is present exactly once with matching bytes.
    struct Expected {
        const char* name;
        const char* data;
        unsigned size;
    };
    const Expected expected[] = {
        {"data/greeting.txt",
         RESOURCE_suites_resource_basic_data_greeting_txt,
         RESOURCE_suites_resource_basic_data_greeting_txt_len},
        {"data/config.json",
         RESOURCE_suites_resource_basic_data_config_json,
         RESOURCE_suites_resource_basic_data_config_json_len},
        {"subdir/banner.txt",
         RESOURCE_suites_resource_basic_subdir_banner_txt,
         RESOURCE_suites_resource_basic_subdir_banner_txt_len},
    };

    for (const auto& e : expected) {
        bool found = false;
        for (unsigned i = 0;
             i < RESOURCE_INDEX_suites_resource_basic_greetings_len;
             ++i) {
            const BladeResourceEntry& row =
                    RESOURCE_INDEX_suites_resource_basic_greetings[i];
            if (std::strcmp(row.name, e.name) == 0) {
                EXPECT_FALSE(found) << "duplicate entry: " << e.name;
                found = true;
                EXPECT_EQ(row.data, e.data);
                EXPECT_EQ(row.size, e.size);
            }
        }
        EXPECT_TRUE(found) << "missing entry: " << e.name;
    }
}
