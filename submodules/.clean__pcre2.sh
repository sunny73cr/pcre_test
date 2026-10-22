printf "\033[36mpcre_test\033[39m: Clenaing submodules/pcre2...\n";

if test -d ./submodules/pcre2; then
    make -C ./submodules/pcre2/ clean;
    if test $? -ne 0; then printf "\033[31mpcre_test\033[39m: Failed to clean submodules/pcre2...\n">&2; exit 1; fi;
fi

printf "\033[32mpcre_test\033[39m: Cleaned submodules/pcre2!\n";
