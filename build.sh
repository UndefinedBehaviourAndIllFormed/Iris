find . -name ".DS_Store" -type f -delete
clang++ -flto=thin test.cpp -fomit-frame-pointer -fno-strict-aliasing -fno-rtti -fno-exceptions -Wall -Wextra -Werror -pedantic-errors -Ofast -std=c++20 -o testarm -target arm64-apple-macos12.5.1
clang++ -flto=thin test.cpp -fomit-frame-pointer -fno-strict-aliasing -fno-rtti -fno-exceptions -Wall -Wextra -Werror -pedantic-errors -Ofast -std=c++20 -o testx86 -target x86_64-apple-macos12.5.1
lipo -create -output testc testx86 testarm
rm -f testx86
rm -f testarm
clang++ -D aura_mac -flto=thin iris.cpp -I "$PWD" -fomit-frame-pointer -fno-strict-aliasing -fno-rtti -fno-exceptions -Ofast -std=c++20 -o irisx64 -target x86_64-apple-macos12.5.1
clang++ -D aura_mac -flto=thin iris.cpp -I "$PWD" -fomit-frame-pointer -fno-strict-aliasing -fno-rtti -fno-exceptions -Ofast -std=c++20 -o irisarm64 -target arm64-apple-macos12.5.1
lipo -create -output irisc irisx64 irisarm64
rm -f irisx64
rm -f irisarm64
cd ..
"$irisc" compile lucy
cd Iris