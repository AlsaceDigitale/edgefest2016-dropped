#!/bin/sh

hash npm 2>/dev/null || { echo >&2 "Please install npm"; exit 1; }
hash bower 2>/dev/null || { echo >&2 "Please install bower"; exit 1; }

npm install &&
bower install &&
npm run webpack-build &&
npm run serve