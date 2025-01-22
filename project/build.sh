#
#  Copyright 2016 zen.code.ai
#
#  This file is part of dlite.
#
#  dlite is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  dlite is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with dlite.  If not, see <http://www.gnu.org/licenses/>.
#
#

#!/bin/bash

rm -f -r ./build

cd ./dlutil
make CONF=Release clean
make CONF=Release build
cd ..

mkdir ./build
mkdir ./build/include
mkdir ./build/lib
mkdir ./build/bin
mkdir ./build/sample

cp ./shared/*.h 			./build/include/
cp ./dlite/*.h 				./build/include/
cp ./dlparser/dlparser.h 	./build/include/
cp ./dltools/*.h 			./build/include/

cp ./antlr/dist/Release/Cygwin-Windows/libantlr.a 		./build/lib/
cp ./sqlite/dist/Release/Cygwin-Windows/libsqlite.a 	./build/lib/
cp ./dlite/dist/Release/Cygwin-Windows/libdlite.a 		./build/lib/
cp ./dlparser/dist/Release/Cygwin-Windows/libdlparser.a ./build/lib/
cp ./dltools/dist/Release/Cygwin-Windows/libdltools.a 	./build/lib/

cp ./dlutil/dist/Release/Cygwin-Windows/dlutil.exe 		./build/bin/

cp ./sample/* ./build/sample/
