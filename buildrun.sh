qmake -r -spec macx-g++
make -w
if [ "$?" == "0" ]; then
	./debug/Turing.app/Contents/MacOS/Turing
fi
