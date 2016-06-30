BUILD_TYPE=Debug

rm -rf bin
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
