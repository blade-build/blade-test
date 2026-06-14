// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// vcpkg#openssl:crypto smoke -- compute a known SHA-256 via the EVP API
// (non-deprecated, works on OpenSSL 1.1 and 3.x alike).

#include <openssl/evp.h>

#include <string>

#include "suites/test_framework/test_framework.h"

namespace blade_test::vcpkg_basic {

namespace {

std::string Sha256Hex(const std::string& input) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, input.data(), input.size());
    EVP_DigestFinal_ex(ctx, digest, &len);
    EVP_MD_CTX_free(ctx);

    static const char* kHex = "0123456789abcdef";
    std::string out;
    out.reserve(len * 2);
    for (unsigned int i = 0; i < len; ++i) {
        out += kHex[digest[i] >> 4];
        out += kHex[digest[i] & 0x0f];
    }
    return out;
}

}  // namespace

TEST(VcpkgOpenssl, Sha256OfAbc) {
    // The canonical SHA-256("abc") test vector.
    EXPECT_EQ("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
              Sha256Hex("abc"));
}

TEST(VcpkgOpenssl, Sha256OfEmpty) {
    EXPECT_EQ("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
              Sha256Hex(""));
}

}  // namespace blade_test::vcpkg_basic
