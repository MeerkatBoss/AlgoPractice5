#!/bin/sh

make remake BUILDTYPE=Release

make run BUILDTYPE=Release TEST_CASE=test_random &&\
    git add . && git commit -m "feat: random test results" && git push

make run BUILDTYPE=Release TEST_CASE=test_sorted &&\
    git add . && git commit -m "feat: sorted test results" && git push

shutdown
