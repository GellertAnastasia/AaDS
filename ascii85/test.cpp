#include <gtest/gtest.h>
#include "./encoder.h"
#include "./decoder.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//encode
TEST(Ascii85Test, Encode) {
    std::stringstream in("1234");
    std::stringstream out;
    encode(in, out);
    EXPECT_EQ(out.str(), "0etOA");
}

TEST(Ascii85Test, EncodeEmpty) {
    std::stringstream in("");
    std::stringstream out;
    encode(in, out);
    EXPECT_TRUE(out.str().empty());
}

TEST(Ascii85Test, EncodeHello) {
    std::stringstream in("hello");
    std::stringstream out;
    encode(in, out);
    EXPECT_EQ(out.str(), "BOu!rDZ");
}

//decode
TEST(Ascii85Test, DecodeEmpty) {
    std::stringstream in("");
    std::stringstream out;
    decode(in, out);
    EXPECT_TRUE(out.str().empty());
}

TEST(Ascii85Test, DecodeHello) {
    std::stringstream in("BOu!rDZ");
    std::stringstream out;
    decode(in, out);
    EXPECT_EQ(out.str(), "hello");
}

//test length
TEST(Ascii85Test, Encode1Byte) {
    std::string input("A");
    std::stringstream in(input);
    std::stringstream out;
    encode(in, out);
    EXPECT_EQ(out.str().length(), 2);
}

TEST(Ascii85Test, Encode3Bytes) {
    std::string input("123");
    std::stringstream in(input);
    std::stringstream out;
    encode(in, out);
    EXPECT_EQ(out.str().length(), 4);
}

//encode and decode
TEST(Ascii85Test, EncodeDecode) {
    const std::string original = "Test data 123!@#";
    std::stringstream in1(original);
    std::stringstream encoded;
    encode(in1, encoded);
    std::stringstream in2(encoded.str());
    std::stringstream decoded;
    decode(in2, decoded);
    EXPECT_EQ(original, decoded.str());
}

TEST(Ascii85Test, MultipleSpaces) {
    const std::string original = "a  b   c    d";
    std::stringstream in1(original);
    std::stringstream encoded;
    encode(in1, encoded);
    std::stringstream in2(encoded.str());
    std::stringstream decoded;
    decode(in2, decoded);
    EXPECT_EQ(original, decoded.str());
}

TEST(Ascii85Test, EncodeDecodeZ) {
    const std::string original = "z@<5q";
    std::stringstream in1(original);
    std::stringstream encoded;
    encode(in1, encoded);
    std::stringstream in2(encoded.str());
    std::stringstream decoded;
    decode(in2, decoded);
    EXPECT_EQ(original, decoded.str());
}
