#!/usr/bin/env bash

set -euo pipefail

msg() {
    echo -e "[+] ${1-}" >&2
}

die() {
    echo -e "[!] ${1-}" >&2
    exit 1
}

check_depends() {
    for cmd in "$@"; do
        if ! command -v "$cmd" >/dev/null 2>&1; then
            die "'$cmd' not found"
        fi
    done
}

usage() {
    cat <<EOF
[!] Usage: $(basename "${BASH_SOURCE[0]}") [options]

    Options:
    -h, --help          Print this message and exit
    -f, --overwrite     Overwrite the original source files
EOF
}

parse_params() {
    while :; do
        case "${1-}" in
        -h | --help)
            usage
            exit
            ;;
        -f | --overwrite)
            OVERWRITE=1
            ;;
        -?*) die "Unknown option: $1\n$(usage)" ;;
        *) break ;;
        esac
        shift
    done
}

main() {
    OVERWRITE=0
    parse_params "$@"

    CLANG_FORMAT=clang-format
    check_depends "$CLANG_FORMAT"

    SCRIPT_DIR="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
    SRC_DIR="$(realpath "${SCRIPT_DIR}"/../src)"
    TARGET_DIRS=("$SRC_DIR")

    if [[ $OVERWRITE -eq 0 ]]; then
        # C++: clang-format
        find "${TARGET_DIRS[@]}" -type f -regex '.*\.\(c\|h\|cpp\|hpp\)' \
            -exec $CLANG_FORMAT --Werror --dry-run {} +
        msg "Coding style is compliant"
    else
        # C++: clang-format
        find "${TARGET_DIRS[@]}" -type f -regex '.*\.\(c\|h\|cpp\|hpp\)' \
            -exec $CLANG_FORMAT --Werror -i {} +
    fi
}

main "$@"

# vim: set ts=4 sw=4 et:
