#include <gtest/gtest.h>

#include "supportlib/Support.h"
#include <memory>

class SupportTests : public testing::Test {
};

TEST(SupportTests, sample_support_test)
{
    auto s = std::make_unique<AppSupport::Support>();

    EXPECT_TRUE(s->False());
}

