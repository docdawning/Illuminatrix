#!/bin/bash
VERSION_NAME=Illuminatrix-$1

if [ "$#" -ne 1 ]; then
	echo "Missing an argument. Run example: $0 20160620-r0"
	exit 1
fi

zip -r Illuminatrix-octoprint-releases/$VERSION_NAME Illuminatrix-octoprint-plugin
echo "Made $VERSION_NAME"
