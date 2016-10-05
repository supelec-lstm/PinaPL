# checks the project's code for potential errors undetected at compilation & good code practices
# requires cppcheck package

cppcheck ./ --enable=all --std=posix
