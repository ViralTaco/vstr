#!/usr/bin/env bash

does_app_exist() {
	hash $@ >/dev/null 2>&1
}

puts() {
	for line in "$@"; do
		printf "$line\n"
	done
}

CWD=$(pwd)
HEADER_NAME="vstr"
HEADER_EXTN="h"
HEADER_PATH="${CWD}/include/vstr/${HEADER_NAME}.${HEADER_EXTN}"
FORMAT_PATH="${CWD}/include/vstr/clang-formated"
declare -a CLANG_FORMAT_STYLES=(
	"LLVM"
	"Google"
	"Mozilla"
	"Chromium"
	"WebKit"
	"Microsoft")

if does_app_exist clang-format; then
	for arg in "${CLANG_FORMAT_STYLES[@]}"; do
		puts "format: ${arg}"
		clang-format --style="${arg}"                                             \
		             --sort-includes "${HEADER_PATH}"                             \
			           > "${FORMAT_PATH}/${HEADER_NAME}.${arg}.${HEADER_EXTN}"
	done
fi

run() {
	local build=${1:-"Debug"}
	cmake -DCMAKE_BUILD_TYPE=$build                                             \
	      -G "CodeBlocks - Unix Makefiles"                                      \
		    -S "${CWD}"                                                           \
		    -B "${CWD}/cmake-$build"
	exit $?
}

run "$@"