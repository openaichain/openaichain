#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/oaccoin.png
ICON_DST=../../src/qt/res/icons/oaccoin.ico
convert ${ICON_SRC} -resize 16x16 oaccoin-16.png
convert ${ICON_SRC} -resize 32x32 oaccoin-32.png
convert ${ICON_SRC} -resize 48x48 oaccoin-48.png
convert oaccoin-16.png oaccoin-32.png oaccoin-48.png ${ICON_DST}

