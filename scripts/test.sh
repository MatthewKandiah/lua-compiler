cd build
ctest --output-on-failure | tee ../test-output.txt
cat ../test-output.txt
cd ..

