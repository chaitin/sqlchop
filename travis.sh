#!/usr/bin/env bash

test_cpp() {
  LD_LIBRARY_PATH=./ ./sqlchop_test
}

test_python() {
  python test.py
}

# -------- main --------

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 { cpp | python }"
  exit 1
fi

set -e  # exit immediately on error
set -x  # display all commands
make sqlchop_$1
eval "test_$1"
