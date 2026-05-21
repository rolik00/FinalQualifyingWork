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
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\arm64-v8a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\arm64-v8a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\armeabi\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\armeabi\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\armeabi-v7a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\armeabi-v7a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\mips\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\mips\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\mips64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\mips64\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\x86\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\x86\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\StaticRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.a %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\x86_64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\DynamicRelease\libE89F37B5194F4F4A8ADE1FFB28028A01.so %ECO_FRAMEWORK%\Eco.IDL1.C\BuildFiles\Android\x86_64\DynamicRelease\
pause
