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
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\arm64-v8a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\arm64-v8a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\armeabi\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\armeabi\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\armeabi-v7a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\armeabi-v7a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\mips\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\mips\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\mips64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\mips64\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\x86\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\x86\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\StaticRelease\libC26F52E0372D4051A290C1BD286DCE90.a %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\x86_64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\DynamicRelease\libC26F52E0372D4051A290C1BD286DCE90.so %ECO_FRAMEWORK%\Eco.IDL1.Java\BuildFiles\Android\x86_64\DynamicRelease\
pause
