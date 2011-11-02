pushd ../Qt4
qmake -r -spec macx-g++
make -w
if [ "$?" == "0" ]; then
  cp -R qscintilla2.app ../build
	popd
	./qscintilla2.app/Contents/MacOS/qscintilla2
else
	popd
fi
