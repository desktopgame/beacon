#!/bin/bash
make
make test ARGS='-V'
if [ ! -e lcov.info ]; then
	touch lcov.info
else
	:
fi
lcov -c -d ./CMakeFiles/beacon.dir -o lcov.info
genhtml -o lcov lcov.info