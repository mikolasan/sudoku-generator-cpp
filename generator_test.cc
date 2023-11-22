#include <gtest/gtest.h>

extern "C" {
    #include "your_c_file.h" // Replace with the actual filename containing your C code
}

TEST(MakeArrayTest, SetsAllElementsToGivenValue) {
    const int length = 10;
    const int value = 42;

    int arr[length];
    makeArray(arr, length, value);

    for (int i = 0; i < length; ++i) {
        EXPECT_EQ(arr[i], value);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
