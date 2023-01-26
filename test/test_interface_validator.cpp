#include <gtest/gtest.h>

#include <interface_validator.hpp>

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForSingleCharacterCommandName) {
  EXPECT_TRUE(cli::InterfaceValidator::IsCommandNameValid("a"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForRegulartCommandName) {
  EXPECT_TRUE(cli::InterfaceValidator::IsCommandNameValid("some_command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForCommandNameContainingAllAlphanumericalCharacters) {
  EXPECT_TRUE(cli::InterfaceValidator::IsCommandNameValid("abcdefghijklmnoprstuwxyz0123456789"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForCommandNameWithDashInTheMiddle) {
  EXPECT_TRUE(cli::InterfaceValidator::IsCommandNameValid("some-command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForCommandNameWithDoubleDashInTheMiddle) {
  EXPECT_TRUE(cli::InterfaceValidator::IsCommandNameValid("some--command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsFalseForEmptyCommandName) {
  EXPECT_FALSE(cli::InterfaceValidator::IsCommandNameValid(""));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsFalseForCommandNameWithOptionPrefix) {
  EXPECT_FALSE(cli::InterfaceValidator::IsCommandNameValid("-command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsFalseForCommandNameWithFlagPrefix) {
  EXPECT_FALSE(cli::InterfaceValidator::IsCommandNameValid("--command"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsTrueForSingleCharacterOptionName) {
  EXPECT_TRUE(cli::InterfaceValidator::IsOptionNameValid("-a"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsTrueForRegularOptionName) {
  EXPECT_TRUE(cli::InterfaceValidator::IsOptionNameValid("-option"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsTrueForOptionNameContainingAllAlphanumericalCharacters) {
  EXPECT_TRUE(cli::InterfaceValidator::IsOptionNameValid("-abcdefghijklmnoprstuwxyz0123456789"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsFalseForEmptyOptionName) {
  EXPECT_FALSE(cli::InterfaceValidator::IsOptionNameValid(""));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsFalseForOptionNameWithNoOptionPrefix) {
  EXPECT_FALSE(cli::InterfaceValidator::IsOptionNameValid("option"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsFalseForOptionNameWithFlagPrefix) {
  EXPECT_FALSE(cli::InterfaceValidator::IsOptionNameValid("--option"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsTrueForSingleCharacterFlagName) {
  EXPECT_TRUE(cli::InterfaceValidator::IsFlagNameValid("--a"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsTrueForRegularFlagName) {
  EXPECT_TRUE(cli::InterfaceValidator::IsFlagNameValid("--flag"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsTrueForFlagNameContainingAllAlphanumericalCharacters) {
  EXPECT_TRUE(cli::InterfaceValidator::IsFlagNameValid("--abcdefghijklmnoprstuwxyz0123456789"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsFalseForEmptyFlagName) {
  EXPECT_FALSE(cli::InterfaceValidator::IsFlagNameValid(""));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsFalseForOptionNameWithNoFlagPrefix) {
  EXPECT_FALSE(cli::InterfaceValidator::IsFlagNameValid("flag"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsFalseForOptionNameWithOptionPrefix) {
  EXPECT_FALSE(cli::InterfaceValidator::IsFlagNameValid("-flag"));
}