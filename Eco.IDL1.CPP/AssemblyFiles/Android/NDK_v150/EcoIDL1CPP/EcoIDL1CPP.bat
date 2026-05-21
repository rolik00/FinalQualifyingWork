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
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\arm64-v8a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\arm64-v8a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\armeabi\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\armeabi\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\armeabi-v7a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\armeabi-v7a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\mips\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\mips\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\mips64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\mips64\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\x86\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\x86\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\StaticRelease\lib8F45C7FFB8144066BEAFF11296176293.a %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\x86_64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\DynamicRelease\lib8F45C7FFB8144066BEAFF11296176293.so %ECO_FRAMEWORK%\Eco.IDL1.CPP\BuildFiles\Android\x86_64\DynamicRelease\
pause
