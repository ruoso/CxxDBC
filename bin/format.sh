#!/usr/bin/env sh

ack --cpp -f | xargs clang-format -i
