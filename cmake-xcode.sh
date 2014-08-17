BUILD_TYPE=Debug

rm -rf bin-xcode
mkdir bin-xcode
cd bin-xcode
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G Xcode ../src/
