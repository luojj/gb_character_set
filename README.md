##### 1.支持GB2312，GBK，GB18030与Unicode，UTF-8之间的转换
整个程序未使用任何第三方库，实现GB2312，GBK，GB18030与Unicode，UTF-8之间的转换。

```
std::string strGBK = "我是谁";
std::string strUTF8;
CCharset charset;
auto Result = charset.GBK_2_UTF8(strGBK.c_str(), (MyUInt32)strGBK.length());
if (!std::get<0>(Result))
    std::cout << "CharsetTrans Failed" << std::endl;
else
    strUTF8.append(&std::get<1>(Result)[0], std::get<1>(Result).size() - 1);
```
 

##### 2.支持UTF-8与Unicode，UTF-8与UTF-16，UTF-8与UTF-32之间的转换
分别提供了C++和C两种实现方式。C++部分需要c++11的支持。

C++部分
```
auto cpp_unicode_1 = charset.UTF8_2_Unicode_Cpp(strUTF8.c_str()); 
if (!std::get<0>(cpp_unicode_1))
    std::cout << "C++ UTF-8 To Unicode Failed." << std::endl;
else 
    std::cout << "C++ UTF-8 To Unicode:" << CStringUtils::BytesToHex(&std::get<1>(cpp_unicode_1)[0], (MyUInt32)std::get<1>(cpp_unicode_1).size() - 1, true) << std::endl;
```

 C部分
```
auto c_unicode_1 = charset.UTF8_2_Unicode_C(strUTF8.c_str(), (MyUInt32)strUTF8.size());
if (!std::get<0>(c_unicode_1))
    std::cout << "C UTF-8 To Unicode Failed." << std::endl;
else 
    std::cout << "C UTF-8 To Unicode:" << CStringUtils::BytesToHex(&std::get<1>(c_unicode_1)[0], (MyUInt32)std::get<1>(c_unicode_1).size() - 1, true) << std::endl;
```

##### 3.项目提供了Windows和Linux两个平台的编译。
Windows平台使用Visual Studio 2022编译。Linux使用Makefile编译。工程见“gb_character_set/Project/WindowsProject”和“gb_character_set/Project/LinuxProject”部分。

##### 4.为测试结果，在“iconv”下给出了GB2312，GBK，GB18030的所有编码，与libiconv做比较，发现iconv对于GBK有95个字符未能识别，这95个字符位于Unicode的PUA区域。









