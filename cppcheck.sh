#!/bin/sh
# checks the project's code for potential errors undetected at compilation & good code practices
# requires cppcheck package

# suppressions :
# readdirCalled : readdir_r is deprecated now

cppcheck ./ --enable=all --std=posix --suppress=readdirCalled
