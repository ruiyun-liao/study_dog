sudo gcc -I arch/inc -I instance/inc -I common/inc -o ./build/test user/*.c arch/src/*.c instance/src/*.c common/src/*.c -lwiringPi
