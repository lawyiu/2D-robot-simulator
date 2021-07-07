#!/bin/bash

if [ -z "$PORT" ]; then
    PORT=8080
fi

cd compile_dir || exit
RACK_ENV=production bundle exec puma -p $PORT ../config.ru
