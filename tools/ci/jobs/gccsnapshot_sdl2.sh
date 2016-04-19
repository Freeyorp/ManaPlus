#!/bin/bash

export CC=gcc
export CXX=g++
export LOGFILE=gcc-snapshot.log
export PATH=/usr/lib/gcc-snapshot/bin:$PATH

source ./tools/ci/scripts/init.sh

aptget_install gcc-snapshot \
    make autoconf automake autopoint gettext libphysfs-dev \
    libxml2-dev libcurl4-gnutls-dev libpng-dev \
    libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev

export CXXFLAGS="-pedantic -ggdb3 -O2 -pipe -Wstrict-aliasing=2 \
-Wstrict-overflow=1 -Wformat=1 -D_FORTIFY_SOURCE=2 \
-std=gnu++1z -Wformat=1"

#export CXXFLAGS="${CXXFLAGS} --all-warnings"
#export CXXFLAGS="${CXXFLAGS} --extra-warnings"
export CXXFLAGS="${CXXFLAGS} -W"
export CXXFLAGS="${CXXFLAGS} -Wabi"
# ignoring
#export CXXFLAGS="${CXXFLAGS} -Wabi-tag"
#export CXXFLAGS="${CXXFLAGS} -Wabi="
export CXXFLAGS="${CXXFLAGS} -Waddress"
# +++ ignoring. may be can be fixed?
#export CXXFLAGS="${CXXFLAGS} -Waggregate-return"
export CXXFLAGS="${CXXFLAGS} -Waggressive-loop-optimizations"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Waliasing"
#export CXXFLAGS="${CXXFLAGS} -Walign-commons"
export CXXFLAGS="${CXXFLAGS} -Wall"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wampersand"
export CXXFLAGS="${CXXFLAGS} -Warray-bounds"
# +++ need try it
export CXXFLAGS="${CXXFLAGS} -Warray-bounds=2"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Warray-temporaries"
#export CXXFLAGS="${CXXFLAGS} -Wassign-intercept"
export CXXFLAGS="${CXXFLAGS} -Wattributes"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wbad-function-cast"
export CXXFLAGS="${CXXFLAGS} -Wbool-compare"
export CXXFLAGS="${CXXFLAGS} -Wbuiltin-macro-redefined"
#export CXXFLAGS="${CXXFLAGS} -Wc++-compat"
#export CXXFLAGS="${CXXFLAGS} -Wc++0x-compat"
#export CXXFLAGS="${CXXFLAGS} -Wc++11-compat"
export CXXFLAGS="${CXXFLAGS} -Wc++14-compat"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wc-binding-type"
#export CXXFLAGS="${CXXFLAGS} -Wc90-c99-compat"
#export CXXFLAGS="${CXXFLAGS} -Wc99-c11-compat"
export CXXFLAGS="${CXXFLAGS} -Wcast-align"
export CXXFLAGS="${CXXFLAGS} -Wcast-qual"
export CXXFLAGS="${CXXFLAGS} -Wchar-subscripts"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wcharacter-truncation"
export CXXFLAGS="${CXXFLAGS} -Wchkp"
export CXXFLAGS="${CXXFLAGS} -Wclobbered"
export CXXFLAGS="${CXXFLAGS} -Wcomment"
export CXXFLAGS="${CXXFLAGS} -Wcomments"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wcompare-reals"
export CXXFLAGS="${CXXFLAGS} -Wconditionally-supported"
# +++ need fix in future
#export CXXFLAGS="${CXXFLAGS} -Wconversion"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wconversion-extra"
export CXXFLAGS="${CXXFLAGS} -Wconversion-null"
export CXXFLAGS="${CXXFLAGS} -Wcoverage-mismatch"
export CXXFLAGS="${CXXFLAGS} -Wcpp"
export CXXFLAGS="${CXXFLAGS} -Wctor-dtor-privacy"
export CXXFLAGS="${CXXFLAGS} -Wdate-time"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wdeclaration-after-statement"
export CXXFLAGS="${CXXFLAGS} -Wdelete-incomplete"
export CXXFLAGS="${CXXFLAGS} -Wdelete-non-virtual-dtor"
export CXXFLAGS="${CXXFLAGS} -Wdeprecated"
export CXXFLAGS="${CXXFLAGS} -Wdeprecated-declarations"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wdesignated-init"
export CXXFLAGS="${CXXFLAGS} -Wdisabled-optimization"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wdiscarded-array-qualifiers"
#export CXXFLAGS="${CXXFLAGS} -Wdiscarded-qualifiers"
export CXXFLAGS="${CXXFLAGS} -Wdiv-by-zero"
# +++ need fix in future
#export CXXFLAGS="${CXXFLAGS} -Wdouble-promotion"
export CXXFLAGS="${CXXFLAGS} -Wduplicated-cond"
# +++ too many warnings. may be used some times
#export CXXFLAGS="${CXXFLAGS} -Weffc++"
export CXXFLAGS="${CXXFLAGS} -Wempty-body"
export CXXFLAGS="${CXXFLAGS} -Wendif-labels"
export CXXFLAGS="${CXXFLAGS} -Wenum-compare"
export CXXFLAGS="${CXXFLAGS} -Werror-implicit-function-declaration"
export CXXFLAGS="${CXXFLAGS} -Wextra"
# +++ need fix in future
#export CXXFLAGS="${CXXFLAGS} -Wfloat-conversion"
# +++ need fix in future
#export CXXFLAGS="${CXXFLAGS} -Wfloat-equal"
export CXXFLAGS="${CXXFLAGS} -Wformat"
export CXXFLAGS="${CXXFLAGS} -Wformat-contains-nul"
export CXXFLAGS="${CXXFLAGS} -Wformat-extra-args"
# +++ ignoring. probably need use some times
#export CXXFLAGS="${CXXFLAGS} -Wformat-nonliteral"
export CXXFLAGS="${CXXFLAGS} -Wformat-security"
export CXXFLAGS="${CXXFLAGS} -Wformat-signedness"
export CXXFLAGS="${CXXFLAGS} -Wformat-y2k"
export CXXFLAGS="${CXXFLAGS} -Wformat-zero-length"
#export CXXFLAGS="${CXXFLAGS} -Wformat="
export CXXFLAGS="${CXXFLAGS} -Wframe-address"
#export CXXFLAGS="${CXXFLAGS} -Wframe-larger-than=<number>"
export CXXFLAGS="${CXXFLAGS} -Wfree-nonheap-object"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wfunction-elimination"
export CXXFLAGS="${CXXFLAGS} -Whsa"
export CXXFLAGS="${CXXFLAGS} -Wignored-qualifiers"
# +++ failing now. Need enable after package updated
#export CXXFLAGS="${CXXFLAGS} -Wignored-attributes"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wimplicit"
#export CXXFLAGS="${CXXFLAGS} -Wimplicit-function-declaration"
#export CXXFLAGS="${CXXFLAGS} -Wimplicit-int"
#export CXXFLAGS="${CXXFLAGS} -Wimplicit-interface"
#export CXXFLAGS="${CXXFLAGS} -Wimplicit-procedure"
#export CXXFLAGS="${CXXFLAGS} -Wincompatible-pointer-types"
export CXXFLAGS="${CXXFLAGS} -Winherited-variadic-ctor"
export CXXFLAGS="${CXXFLAGS} -Winit-self"
# ignoting
#export CXXFLAGS="${CXXFLAGS} -Winline"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wint-conversion"
export CXXFLAGS="${CXXFLAGS} -Wint-to-pointer-cast"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Winteger-division"
#export CXXFLAGS="${CXXFLAGS} -Wintrinsic-shadow"
#export CXXFLAGS="${CXXFLAGS} -Wintrinsics-std"
export CXXFLAGS="${CXXFLAGS} -Winvalid-memory-model"
export CXXFLAGS="${CXXFLAGS} -Winvalid-offsetof"
export CXXFLAGS="${CXXFLAGS} -Winvalid-pch"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wjump-misses-init"
#export CXXFLAGS="${CXXFLAGS} -Wlarger-than-"
#export CXXFLAGS="${CXXFLAGS} -Wlarger-than="
#export CXXFLAGS="${CXXFLAGS} -Wline-truncation"
export CXXFLAGS="${CXXFLAGS} -Wliteral-suffix"
export CXXFLAGS="${CXXFLAGS} -Wlogical-not-parentheses"
export CXXFLAGS="${CXXFLAGS} -Wlogical-op"
export CXXFLAGS="${CXXFLAGS} -Wlong-long"
export CXXFLAGS="${CXXFLAGS} -Wlto-type-mismatch"
export CXXFLAGS="${CXXFLAGS} -Wmain"
export CXXFLAGS="${CXXFLAGS} -Wmaybe-uninitialized"
export CXXFLAGS="${CXXFLAGS} -Wmemset-transposed-args"
export CXXFLAGS="${CXXFLAGS} -Wmisleading-indentation"
export CXXFLAGS="${CXXFLAGS} -Wmissing-braces"
export CXXFLAGS="${CXXFLAGS} -Wmissing-declarations"
export CXXFLAGS="${CXXFLAGS} -Wmissing-field-initializers"
export CXXFLAGS="${CXXFLAGS} -Wmissing-format-attribute"
export CXXFLAGS="${CXXFLAGS} -Wmissing-include-dirs"
export CXXFLAGS="${CXXFLAGS} -Wmissing-noreturn"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wmissing-parameter-type"
#export CXXFLAGS="${CXXFLAGS} -Wmissing-prototypes"
export CXXFLAGS="${CXXFLAGS} -Wmultichar"
# ignoring
#export CXXFLAGS="${CXXFLAGS} -Wmultiple-inheritance"
# ignoring
#export CXXFLAGS="${CXXFLAGS} -Wnamespaces"
export CXXFLAGS="${CXXFLAGS} -Wnarrowing"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wnested-externs"
export CXXFLAGS="${CXXFLAGS} -Wnoexcept"
export CXXFLAGS="${CXXFLAGS} -Wnon-template-friend"
export CXXFLAGS="${CXXFLAGS} -Wnon-virtual-dtor"
export CXXFLAGS="${CXXFLAGS} -Wnonnull"
export CXXFLAGS="${CXXFLAGS} -Wnonnull-compare"
#export CXXFLAGS="${CXXFLAGS} -Wnormalized"
export CXXFLAGS="${CXXFLAGS} -Wnormalized=nfkc"
export CXXFLAGS="${CXXFLAGS} -Wnull-dereference"
export CXXFLAGS="${CXXFLAGS} -Wodr"
# probably need fix it
#export CXXFLAGS="${CXXFLAGS} -Wold-style-cast"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wold-style-declaration"
#export CXXFLAGS="${CXXFLAGS} -Wold-style-definition"
export CXXFLAGS="${CXXFLAGS} -Wopenmp-simd"
export CXXFLAGS="${CXXFLAGS} -Woverflow"
export CXXFLAGS="${CXXFLAGS} -Woverlength-strings"
# disabled because exists some overloaded virtuals
#export CXXFLAGS="${CXXFLAGS} -Woverloaded-virtual"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Woverride-init"
#export CXXFLAGS="${CXXFLAGS} -Woverride-init-side-effects"
export CXXFLAGS="${CXXFLAGS} -Wpacked"
export CXXFLAGS="${CXXFLAGS} -Wpacked-bitfield-compat"
# +++ may be need fix in future?
#export CXXFLAGS="${CXXFLAGS} -Wpadded"
export CXXFLAGS="${CXXFLAGS} -Wparentheses"
export CXXFLAGS="${CXXFLAGS} -Wpedantic"
export CXXFLAGS="${CXXFLAGS} -Wplacement-new"
#export CXXFLAGS="${CXXFLAGS} -Wplacement-new="
export CXXFLAGS="${CXXFLAGS} -Wpmf-conversions"
export CXXFLAGS="${CXXFLAGS} -Wpointer-arith"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wpointer-sign"
#export CXXFLAGS="${CXXFLAGS} -Wpointer-to-int-cast"
export CXXFLAGS="${CXXFLAGS} -Wpragmas"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wproperty-assign-default"
#export CXXFLAGS="${CXXFLAGS} -Wprotocol"
#export CXXFLAGS="${CXXFLAGS} -Wreal-q-constant"
#export CXXFLAGS="${CXXFLAGS} -Wrealloc-lhs"
#export CXXFLAGS="${CXXFLAGS} -Wrealloc-lhs-all"
export CXXFLAGS="${CXXFLAGS} -Wredundant-decls"
export CXXFLAGS="${CXXFLAGS} -Wreorder"
export CXXFLAGS="${CXXFLAGS} -Wreturn-local-addr"
export CXXFLAGS="${CXXFLAGS} -Wreturn-type"
export CXXFLAGS="${CXXFLAGS} -Wscalar-storage-order"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wselector"
export CXXFLAGS="${CXXFLAGS} -Wsequence-point"
export CXXFLAGS="${CXXFLAGS} -Wshadow"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wshadow-ivar"
export CXXFLAGS="${CXXFLAGS} -Wshift-count-negative"
export CXXFLAGS="${CXXFLAGS} -Wshift-count-overflow"
export CXXFLAGS="${CXXFLAGS} -Wshift-negative-value"
export CXXFLAGS="${CXXFLAGS} -Wshift-overflow"
#export CXXFLAGS="${CXXFLAGS} -Wshift-overflow="
export CXXFLAGS="${CXXFLAGS} -Wsign-compare"
# +++ need fix in future
#export CXXFLAGS="${CXXFLAGS} -Wsign-conversion"
export CXXFLAGS="${CXXFLAGS} -Wsign-promo"
export CXXFLAGS="${CXXFLAGS} -Wsized-deallocation"
export CXXFLAGS="${CXXFLAGS} -Wsizeof-array-argument"
export CXXFLAGS="${CXXFLAGS} -Wsizeof-pointer-memaccess"
export CXXFLAGS="${CXXFLAGS} -Wstack-protector"
#export CXXFLAGS="${CXXFLAGS} -Wstack-usage="
export CXXFLAGS="${CXXFLAGS} -Wstrict-aliasing"
#export CXXFLAGS="${CXXFLAGS} -Wstrict-aliasing="
export CXXFLAGS="${CXXFLAGS} -Wstrict-null-sentinel"
# used before
#export CXXFLAGS="${CXXFLAGS} -Wstrict-overflow"
#export CXXFLAGS="${CXXFLAGS} -Wstrict-overflow="
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wstrict-prototypes"
#export CXXFLAGS="${CXXFLAGS} -Wstrict-selector-match"
export CXXFLAGS="${CXXFLAGS} -Wsubobject-linkage"
# +++ ignoring
#export CXXFLAGS="${CXXFLAGS} -Wsuggest-attribute=const"
#export CXXFLAGS="${CXXFLAGS} -Wsuggest-attribute=format"
export CXXFLAGS="${CXXFLAGS} -Wsuggest-attribute=noreturn"
# +++ ignoring
#export CXXFLAGS="${CXXFLAGS} -Wsuggest-attribute=pure"
#export CXXFLAGS="${CXXFLAGS} -Wsuggest-final-methods"
#export CXXFLAGS="${CXXFLAGS} -Wsuggest-final-types"
export CXXFLAGS="${CXXFLAGS} -Wsuggest-override"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wsurprising"
export CXXFLAGS="${CXXFLAGS} -Wswitch"
export CXXFLAGS="${CXXFLAGS} -Wswitch-bool"
# disable for SDL 2 because issue in headers
#export CXXFLAGS="${CXXFLAGS} -Wswitch-default"
export CXXFLAGS="${CXXFLAGS} -Wno-switch-default"
export CXXFLAGS="${CXXFLAGS} -Wswitch-enum"
export CXXFLAGS="${CXXFLAGS} -Wsync-nand"
export CXXFLAGS="${CXXFLAGS} -Wsynth"
# ignoring
#export CXXFLAGS="${CXXFLAGS} -Wsystem-headers"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wtabs"
#export CXXFLAGS="${CXXFLAGS} -Wtarget-lifetime"
export CXXFLAGS="${CXXFLAGS} -Wtautological-compare"
# ignoring
#export CXXFLAGS="${CXXFLAGS} -Wtemplates"
export CXXFLAGS="${CXXFLAGS} -Wterminate"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wtraditional"
#export CXXFLAGS="${CXXFLAGS} -Wtraditional-conversion"
export CXXFLAGS="${CXXFLAGS} -Wtrampolines"
export CXXFLAGS="${CXXFLAGS} -Wtrigraphs"
export CXXFLAGS="${CXXFLAGS} -Wtype-limits"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wundeclared-selector"
export CXXFLAGS="${CXXFLAGS} -Wundef"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wunderflow"
export CXXFLAGS="${CXXFLAGS} -Wuninitialized"
export CXXFLAGS="${CXXFLAGS} -Wunknown-pragmas"
# +++ may be try use in future?
#export CXXFLAGS="${CXXFLAGS} -Wunsafe-loop-optimizations"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wunsuffixed-float-constants"
export CXXFLAGS="${CXXFLAGS} -Wunused"
export CXXFLAGS="${CXXFLAGS} -Wunused-but-set-parameter"
export CXXFLAGS="${CXXFLAGS} -Wunused-but-set-variable"
export CXXFLAGS="${CXXFLAGS} -Wunreachable-code"
export CXXFLAGS="${CXXFLAGS} -Wunused-const-variable=1"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wunused-dummy-argument"
export CXXFLAGS="${CXXFLAGS} -Wunused-function"
export CXXFLAGS="${CXXFLAGS} -Wunused-label"
export CXXFLAGS="${CXXFLAGS} -Wunused-local-typedefs"
export CXXFLAGS="${CXXFLAGS} -Wunused-macros"
export CXXFLAGS="${CXXFLAGS} -Wunused-parameter"
export CXXFLAGS="${CXXFLAGS} -Wunused-result"
export CXXFLAGS="${CXXFLAGS} -Wunused-value"
export CXXFLAGS="${CXXFLAGS} -Wunused-variable"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wuse-without-only"
# +++ need from time to time
#export CXXFLAGS="${CXXFLAGS} -Wuseless-cast"
export CXXFLAGS="${CXXFLAGS} -Wvarargs"
export CXXFLAGS="${CXXFLAGS} -Wvariadic-macros"
export CXXFLAGS="${CXXFLAGS} -Wvector-operation-performance"
export CXXFLAGS="${CXXFLAGS} -Wvirtual-inheritance"
export CXXFLAGS="${CXXFLAGS} -Wvirtual-move-assign"
export CXXFLAGS="${CXXFLAGS} -Wvla"
export CXXFLAGS="${CXXFLAGS} -Wvolatile-register-var"
export CXXFLAGS="${CXXFLAGS} -Wwrite-strings"
export CXXFLAGS="${CXXFLAGS} -Wzero-as-null-pointer-constant"
# not for C++
#export CXXFLAGS="${CXXFLAGS} -Wzerotrip"
#export CXXFLAGS="${CXXFLAGS} -frequire-return-statement"

do_init
run_configure --with-sdl2
run_make
run_check_warnings

source ./tools/ci/scripts/exit.sh

exit 0