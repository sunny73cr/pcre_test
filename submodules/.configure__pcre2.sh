printf "\033[36mpcre_test\033[39m: Configuring submodules/pcre2...\n";

git submodule update --checkout submodules/pcre2;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to clone submodules/pcre2...\n">&2; exit 1; fi;

cd ./submodules/pcre2;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to cd into submodules/pcre2...\n">&2; exit 1; fi;

./autogen.sh;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to run 'autogen.sh' in submodules/pcre2, do you have the package 'libtool'?...\n">&2; exit 1; fi;

./configure;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to run 'configure' in submodules/pcre2...\n">&2; exit 1; fi;

cd ../../;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to 'cd' out of submodules/pcre2...\n">&2; exit 1; fi;

printf "\033[32mpcre_test\033[39m: Configured submodules/pcre2!\n";
