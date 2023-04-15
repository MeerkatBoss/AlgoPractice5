#!/bin/sh

make remake BUILDTYPE=Release

make run BUILDTYPE=Release TEST_CASE=test_random &&
    git add . && git commit -m "feat: random retest"

make run BUILDTYPE=Release TEST_CASE=test_sorted &&
    git add . && git commit -m "feat: sorted retest"

shutdown
