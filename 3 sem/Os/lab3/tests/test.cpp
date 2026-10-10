#include <catch2/catch_test_macros.hpp>
#include <cstring>

extern "C" {
#include "mmemory.h"
}

TEST_CASE("write/read across page boundary") {
    REQUIRE(_init(16, 64) == MM_OK);
    VA p;
    REQUIRE(_malloc(&p, 200) == MM_OK);

    char w[100], r[100];
    for (int i = 0; i < 100; i++) w[i] = (char)i;
    REQUIRE(_write(p + 30, w, 100) == MM_OK);
    REQUIRE(_read(p + 30, r, 100) == MM_OK);
    REQUIRE(std::memcmp(w, r, 100) == 0);
    mm_destroy();
}

TEST_CASE("errors") {
    REQUIRE(_init(16, 64) == MM_OK);
    VA p;
    REQUIRE(_malloc(&p, 100) == MM_OK);
    char buf[200];
    REQUIRE(_read(p, buf, 200) == MM_ERR_PARAM);   
    REQUIRE(_free(p) == MM_OK);
    REQUIRE(_free(p) == MM_ERR_PARAM);             
    mm_destroy();
}

TEST_CASE("prefetch reduces faults on sequential access") {
    REQUIRE(_init(64, 64) == MM_OK);
    REQUIRE(mm_config(8, 3) == MM_OK);
    VA p;
    REQUIRE(_malloc(&p, 64 * 64) == MM_OK);
    char c;
    for (int i = 0; i < 64; i++) REQUIRE(_read(p + i * 64, &c, 1) == MM_OK);
    mm_stats s;
    mm_get_stats(&s);
    REQUIRE(s.page_faults == 16);                  
    mm_destroy();
}