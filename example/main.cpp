#include <iostream>

#include "command_line_interface.hpp"

using namespace comlint;

/*
This file shows an example implementation of command line interface using Comlint and basing on well-known git commands.
git status -b develop --verbose --short
git add /file.txt --verbose --interactive
git commit -m "Message" -c Commit --verbose --amend
git merge branch1 branch2 -s recursive/resolve/subtree
*/

void run_add_command(const ParsedCommand &command)
{
    std::cout << "Running add command for file " << command.values.front() << std::endl;

    if (command.flags.at("--verbose")) {
        std::cout << "Being verbose" << std::endl;
    }
    if (command.flags.at("--interactive")) {
        std::cout << "Adding interactively" << std::endl;
    }
}

void run_commit_command(const ParsedCommand &command)
{
    std::cout << "Running commit command!" << std::endl;

    if (command.IsOptionUsed("-m")) {
        std::cout << "Adding message " << command.options.at("-m") << std::endl;
    }
    if (command.IsOptionUsed("-c")) {
        std::cout << "Re-editting commit " << command.options.at("-c") << std::endl;
    }
    if (command.flags.at("--amend")) {
        std::cout << "Amending commit" << std::endl;
    }
    if (command.flags.at("--verbose")) {
        std::cout << "Being verbose" << std::endl;
    }
}

void run_merge_command(const ParsedCommand &command)
{
    std::cout << "Running merge command for branches " << command.values.at(0U) << " and " << command.values.at(1U) 
              << " using strategy " << command.options.at("-s") << std::endl;

    if (command.IsOptionUsed("-m")) {
        std::cout << "Adding message " << command.options.at("-m") << std::endl;
    }
}

void run_status_command(const ParsedCommand &command)
{
    std::cout << "Running status command!" << std::endl;

    if (command.IsOptionUsed("-b")) {
        std::cout << "Showing status for branch " << command.options.at("-b") << std::endl;
    }
    if (command.flags.at("--verbose")) {
        std::cout << "Being verbose" << std::endl;
    }
    if (command.flags.at("--short")) {
        std::cout << "Showing short output" << std::endl;
    }
}

int main(int argc, char** argv)
{
    try {
        CommandLineInterface cli(argc, argv, "ExampleApplication", "Example usage of Comlint library basing on some git commands", false);

        cli.AddCommand("add", "Add files to commit", 1U, {}, {}, {"--verbose", "--interactive"});
        cli.AddCommand("commit", "Commit changes", {"-m", "-c"}, {"--verbose", "--amend"});
        cli.AddCommand("merge", "Merge two branches", 2U, {}, {"-s", "-m"}, {}, {"-s"});
        cli.AddCommand("status", "Show current status", {"-b"}, {"--verbose", "--short"});

        cli.AddOption("-b", "Specify branch name");
        cli.AddOption("-m", "Provide message");
        cli.AddOption("-c", "Provide commit hash");
        cli.AddOption("-s", "Specify merging strategy", {"recursive", "resolve", "subtree"});

        cli.AddFlag("--verbose", "Show verbose output");
        cli.AddFlag("--short", "Show short status output");
        cli.AddFlag("--interactive", "Add files to commit interactively");
        cli.AddFlag("--amend", "Join to previous commit");

        const ParsedCommand parsed_command = cli.Parse();

        if (parsed_command.name == "add") {
            run_add_command(parsed_command);
        }
        if (parsed_command.name == "commit") {
            run_commit_command(parsed_command);
        }
        if (parsed_command.name == "merge") {
            run_merge_command(parsed_command);
        }
        if (parsed_command.name == "status") {
            run_status_command(parsed_command);
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}