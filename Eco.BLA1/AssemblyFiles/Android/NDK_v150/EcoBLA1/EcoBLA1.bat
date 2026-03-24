call ndk-build clean
call ndk-build TARGET_LINK=0 NDK_DEBUG=0 CONFIGURATION=StaticRelease
call ndk-build TARGET_LINK=0 NDK_DEBUG=1 CONFIGURATION=StaticDebug
rmdir /s /q libs
rmdir /s /q obj
call ndk-build clean
call ndk-build TARGET_LINK=1 NDK_DEBUG=0 CONFIGURATION=DynamicRelease
call ndk-build TARGET_LINK=1 NDK_DEBUG=1 CONFIGURATION=DynamicDebug
rmdir /s /q libs
rmdir /s /q obj
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\arm64-v8a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\arm64-v8a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\armeabi\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\armeabi\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\armeabi-v7a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\armeabi-v7a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\mips\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\mips\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\mips64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\mips64\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\x86\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\x86\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\StaticRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.a %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\x86_64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\DynamicRelease\lib88DD94592E7C48BAB381EAA0F82A88F6.so %ECO_FRAMEWORK%\Eco.BLA1\BuildFiles\Android\x86_64\DynamicRelease\
pause
