#include <gtest/gtest.h>

#include "comlint/interface_validator.hpp"

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForSingleCharacterCommandName) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsCommandNameValid("a"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForRegulartCommandName) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsCommandNameValid("some_command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForCommandNameContainingAllAlphanumericalCharacters) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsCommandNameValid("abcdefghijklmnoprstuwxyz0123456789"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForCommandNameWithDashInTheMiddle) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsCommandNameValid("some-command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsTrueForCommandNameWithDoubleDashInTheMiddle) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsCommandNameValid("some--command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsFalseForEmptyCommandName) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsCommandNameValid(""));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsFalseForCommandNameWithOptionPrefix) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsCommandNameValid("-command"));
}

TEST(TestInterfaceValidator, IsCommandNameValidReturnsFalseForCommandNameWithFlagPrefix) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsCommandNameValid("--command"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsTrueForSingleCharacterOptionName) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsOptionNameValid("-a"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsTrueForRegularOptionName) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsOptionNameValid("-option"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsTrueForOptionNameContainingAllAlphanumericalCharacters) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsOptionNameValid("-abcdefghijklmnoprstuwxyz0123456789"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsFalseForEmptyOptionName) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsOptionNameValid(""));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsFalseForOptionNameWithNoOptionPrefix) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsOptionNameValid("option"));
}

TEST(TestInterfaceValidator, IsOptionNameValidReturnsFalseForOptionNameWithFlagPrefix) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsOptionNameValid("--option"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsTrueForSingleCharacterFlagName) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsFlagNameValid("--a"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsTrueForRegularFlagName) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsFlagNameValid("--flag"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsTrueForFlagNameContainingAllAlphanumericalCharacters) {
  EXPECT_TRUE(comlint::InterfaceValidator::IsFlagNameValid("--abcdefghijklmnoprstuwxyz0123456789"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsFalseForEmptyFlagName) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsFlagNameValid(""));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsFalseForFlagNameWithNoFlagPrefix) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsFlagNameValid("flag"));
}

TEST(TestInterfaceValidator, IsFlagNameValidReturnsFalseForFlagNameWithOptionPrefix) {
  EXPECT_FALSE(comlint::InterfaceValidator::IsFlagNameValid("-flag"));
}