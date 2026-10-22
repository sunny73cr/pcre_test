if test ! -d ./submodules/pcre2; then
    printf "\033[31mpcre_test\033[39m: Missing submodule 'pcre2'; run ./configure first!\n">&2;
    exit 1;
fi

printf "\033[36mpcre_test\033[39m: Building submodules/pcre2...\n";

cd ./submodules/pcre2;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to cd into submodules/pcre2...\n">&2; exit 1; fi;

if test "$1" == "install"; then
    make install;
    if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to build submodules/pcre2... installation might require root!\n">&2; exit 1; fi;
else
    make;
    if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to build submodules/pcre2...\n">&2; exit 1; fi;
fi;

cd ../../;
if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to 'cd' out of submodules/pcre2...\n">&2; exit 1; fi;

printf "\033[32mpcre_test\033[39m: Built submodules/pcre2!\n";
