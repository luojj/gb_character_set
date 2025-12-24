// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：Charset.h
// 创建日期：2022-12-19
// 创建人：罗俊杰
// 文件说明：字符集处理
// 相关说明
// 1.Unicode与UTF
// Unicode是一个字符集,它只规定了符号的二进制代码,却没有规定这个二进制代码应该如何存储.比如:汉字"严"的Unicode十六进制数是4E25,转换成二进制数足足有15位(100111000100101),也就是说这个符号的表示至少需要2个字节.
// 表示其它更大的符号,可能需要3个字节或者4个字节,甚至更多.
// 这里就有两个严重的问题:
// 第一个是如何才能区别Unicode和ASCII?计算机怎么知道三个字节表示一个符号,而不是分别表示三个符号呢?
// 第二个是我们已经知道英文字母只用一个字节表示就够了,如果Unicode统一规定,每个符号用三个或四个字节表示,那么每个英文字母前都必然有二到三个字节是0,这对于存储来说是极大的浪费,文本文件的大小会因此大出二三倍,这是无法接受的.
// 它们造成的结果是:
// 1)出现了Unicode的多种存储方式,也就是说有许多种不同的二进制格式,可以用来表示Unicode.
// 2)Unicode在很长一段时间内无法推广,直到互联网的出现.
// 
// 大概来说,Unicode编码系统可分为编码方式和实现方式两个层次.
// 编码方式
// Unicode的编码方式与ISO 10646的通用字符集(Universal Character Set,UCS)概念相对应,目前实际应用的Unicode版本对应于UCS-2,使用16位的编码空间,也就是每个字符占用2个字节.
// 这样理论上一共最多可以表示216即65536个字符,基本满足各种语言的使用.实际上目前版本的Unicode尚未填充满这16位编码,保留了大量空间作为特殊使用或将来扩展.
// 
// 上述16位Unicode字符构成基本多文种平面(Basic Multilingual Plane,简称BMP).最新(但未实际广泛使用)的Unicode版本定义了16个辅助平面,两者合起来至少需要占据21位的编码空间,比3字节略少.
// 但事实上辅助平面字符仍然占用4字节编码空间,与UCS-4保持一致.未来版本会扩充到ISO 10646-1实现级别3,即涵盖UCS-4的所有字符.
// UCS-4是一个更大的尚未填充完全的31位字符集,加上恒为0的首位,共需占据32位,即4字节.理论上最多能表示231个字符,完全可以涵盖一切语言所用的符号.
// 
// BMP字符的Unicode编码表示为U+hhhh,其中每个h代表一个十六进制数位.与UCS-2编码完全相同.与4字节UCS-4编码后两个字节一致,前两个字节的所有位均为0.
// 
// 实现方式
// Unicode的实现方式不同于编码方式.一个字符的Unicode编码是确定的.但是在实际传输过程中,由于不同系统平台的设计不一定一致,以及出于节省空间的目的,对Unicode编码的实现方式有所不同.
// Unicode的实现方式称为Unicode转换格式(Unicode Translation Format,简称为UTF).
// 
// Unicode的实现方式包括UTF-7,Punycode,CESU-8,SCSU,UTF-32等,这些实现方式有些仅在一定的国家和地区使用,有些则属于未来的规划方式.目前通用的实现方式是UTF-16小尾序(BOM),UTF-16大尾序(BOM)和UTF-8.
// 
// 2.UTF系列
// UTF-8,UTF-16,UTF-32都是一种针对Unicode的字符实现方式.因UTF-8是在互联网上使用最广的一种Unicode的实现方式,其它实现方式(UTF-16和UTF-32)在互联网上基本不用,所以这里主要讲下UTF-8.
// UTF-8使用一至四个字节为每个字符编码:
// 1)128个US-ASCII字符只需一个字节编码(Unicode范围由U+0000至U+007F).
// 2)带有附加符号的拉丁文,希腊文,西里尔字母,亚美尼亚语,希伯来文,阿拉伯文,叙利亚文及其它则需要二个字节编码(Unicode范围由U+0080至U+07FF).
// 3)其它基本多文种平面(BMP)中的字符(这包含了大部分常用字)使用三个字节编码.
// 4)其它极少使用的Unicode辅助平面的字符使用四字节编码.
// 
// 注:Unicode在范围D800-DFFF中不存在任何字符,基本多文种平面中约定了这个范围用于UTF-16扩展标识辅助平面(两个UTF-16表示一个辅助平面字符).
// 当然,任何编码都是可以被转换到这个范围,但在Unicode中他们并不代表任何合法的值.
// 
// UTF-8的编码规则很简单,只有二条:
// 1)对于单字节的符号,字节的第一位设为0,后面7位为这个符号的Unicode码.因此对于英语字母,UTF-8编码和ASCII码是相同的.
// 2)对于n字节的符号(n>1),第一个字节的前n位都设为1,第n+1位设为0,后面字节的前两位一律设为10.剩下的没有提及的二进制位,全部为这个符号的Unicode码.
// 
// 下表总结了编码规则,字母x表示可用编码的位.
//	   Unicode符号范围 | UTF-8编码方式
//			(十六进制) | (二进制)
// --------------------+---------------------------------------------
// 0000 0000-0000 007F | 0xxxxxxx
// 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
// 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
// 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
// 
// Unicode规范中定义,每一个文件的最前面分别加入一个表示编码顺序的字符,这个字符的名字叫做"零宽度非换行空格"(ZERO WIDTH NO-BREAK SPACE),也就是常说的BOM(Byte Order Mark).
// UTF-8的BOM为"EF BB BF",UTF-16 BE BOM为"FE FF",UTF-16 LE BOM为"FF FE"(写文件时一定要注意,不要忘记添加).
// 
// UTF系列与Unicode的转换可以通过程序实现.
// 
// 3.GB2312,GBK,GB18030
// 1)GB2312
// 以国家标准局1980年颁布的<<信息交换用汉字编码字符集(基本集)>>(代号为GB2312 80)规定的汉字交换码作为国家标准汉字编码(这就是常说的GB2312).
// GB2312中共有7445个字符符号:汉字符号6763个,一级汉字3755个(按汉语拼音字母顺序排列),二级汉字3008个(按部首笔划顺序排列),非汉字符号682个(包括拉丁字母,希腊字母,日文平假名及片假名字母,俄语西里尔字母).(注:我特意查看了所有汉字,发现是6835个汉字,并非网上所说的6763.可能早期版本是6763,后面有做修改.)
// GB2312规定,所有的国标码汉字及符号组成一个94x94的方阵.在此方阵中,每一行称为一个"区",每一列称为一个"位".这个方阵实际上组成一个有94个区(编号由01到94),每个区有94个位(编号由01到94)的汉字字符集.
// 一个汉字所在的区号和位号的组合就构成了该汉字的"区位码".其中,高两位为区号,低两位为位号.这样区位码可以唯一地确定某一汉字或字符;反之,任何一个汉字或符号都对应一个唯一的区位码,没有重码.
// 
// 区位码分布情况如下:
// 1区:键盘上没有的各种符号
// 2区:各种序号
// 3区:键盘上的各种符号(按中文方式给出)
// 4-5区:日文字母
// 6区:希腊字母
// 7区:俄文字母
// 8区:标识拼音声调的母音及拼音字母名称
// 9区:制表符号
// 10-15区:未用
// 16-55区:一级汉字(按拼音字母顺序排列)
// 56-87区:二级汉字(按部首笔划顺序排列)
// 88-94区:自定义汉字
// 
// 由上可以看出,所有汉字与符号的94个区,可以分为四个组:
// 1-15区:为图形符号区.其中1-9区为标准符号区;10-15区为自定义符号区
// 16-55区:为一级汉字区,包含3755个汉字.这些区中的汉字按汉语拼音顺序排序,同音字按笔画顺序列出.
// 56-87区:为二级汉字区,包含3008个汉字.这些区中的汉字是按部首笔划顺序排序的.
// 88-94区:为自定义汉字区.
// 
// 国标码规定,每个汉字(包括非汉字的一些符号)由2字节代码表示.每个字节的最高位为0,只使用低7位,而低7位的编码中又有34个适用于控制用的,这样每个字节只有128-34=94个编码用于汉字.
// 2个字节就有94x94=8836个汉字编码.在表示一个汉字的2个字节中,高字节对应编码表中的行号,称为区号;低字节对应编码表中的列号,称为位号.
// 
// 在使用GB2312的程序中,通常采用EUC储存方法,以便于兼容ASCII.
// 
// EUC全名为Extended Unix Code,是一个使用8位编码来表示字符的方法.它使用了一些兼容于ISO/IEC 2022区位码的94x94编码表,把每个区位加上0xA0来表示,以便于兼容ASCII.
// 它主要用于表示及储存汉语文字,日语文字及朝鲜文字.
// 
// EUC-CN是GB2312最常用的表示方法.浏览器编码表上的"GB2312",通常都是指"EUC-CN"表示法.
// EUC-JP用来储存日本JIS X 0208(旧称JIS C 6226)及JIS X 0212字集的字符.但是,日语文字较多使用ISO-2022-JP或Shift JIS的方法来表示.
// EUC-JISX0213是一个制定中的EUC规格,用来表示JIS X 0213字集的字符.
// EUC-KR用来储存韩国KS X 1001字集(旧称KS C 5601)的字符.此规格由KS X 2901(旧称KS C 5861)定义.
// EUC-TW本来是台湾使用的其中一个汉字储存方法,以CNS 11643字表为基础.但是台湾普遍使用Big5,EUC-TW甚少使用.(Big5又称为大五码或者五大码,是通行于台湾,香港地区的一个繁体字编码方案.地区标准号为:CNS11643,这就是人们讲的BIG-5码)
// 
// GB2312的出现,基本满足了汉字的计算机处理需要,它所收录的汉字已经覆盖中国大陆99.75%的使用频率.对于人名,古汉语等方面出现的罕用字,GB2312不能处理,这导致了后来GBK及GB18030汉字字符集的出现.
// 
// 2)GBK
// GBK是双字节编码,每个字符用两个字节表示.它的码位空间是0x8140~0xFE7E和0x8180~0xFEFE,一共23940个码位.在这23940个码位上定义了21886个字符,包括21003个汉字和883个图形符号.
// GBK的码位空间可以划分为以下区域:
// 类别			区名		码位范围						码位数		字符数
// 符号区		1区			0xA1A1~0xA9FE					846			717
// 符号区		5区			0xA840~0xA89F和0xA940~0xA99F	192			166
// 汉字区		2区			0xB0A1~0xF7FE					6768		6763
// 汉字区		3区			0x8140~0xA07E和0x8180~0xA0FE	6080		6080
// 汉字区		4区			0xAA40~0xFE7E和0xAA80~0xFEA0	8160		8160
// 用户自定义区	用户区1		0xAAA1~0xAFFE					564
// 用户自定义区	用户区2		0xF8A1~0xFEFE					658
// 用户自定义区	用户区3		0xA140~0xA77E和0xA180~0xA7A0	672
// 
// 在Unicode 5.0的99089个字符中,有71226个字符与汉字有关.它们的分布如下:(目前最新的Unicode为Unicode 17.0,于2025年9月9日发布.)
// Block名称		开始码位	结束码位	字符数
// CJK统一汉字		4E00		9FBB		20924
// CJK统一汉字扩充A	3400		4DB5		6582
// CJK统一汉字扩充B	20000		2A6D6		42711
// CJK兼容汉字		F900		FA2D		302
// CJK兼容汉字		FA30		FA6A		59
// CJK兼容汉字		FA70		FAD9		106
// CJK兼容汉字补充	2F800		2FA1D		542
// 
// 如果不算兼容汉字,Unicode目前支持的汉字总数是20924+6582+42711=70217.
// 这里有一个细节,在早期的Unicode版本中,CJK统一汉字区的范围是0x4E00-0x9FA5,也就是我们经常提到的20902个汉字.当前版本的Unicode增加了22个字符,码位是0x9FA6-0x9FBB.
// 从这里可以发现GBK比Unicode 5.0多了21003-20902=101个汉字.这101个汉字包括:
// a)增补汉字和部首80个,包括28个部首和52个汉字.
// 汉字 GBK编码	PUA编码	非PUA编码
// ⺁	 FE50		E815	2E81
// 	 FE51		E816	20087
// 	 FE52		E817	20089
// 	 FE53		E818	200CC
// ⺄	 FE54		E819	2E84
// 㑳	 FE55		E81A	3473
// 㑇	 FE56		E81B	3447
// ⺈	 FE57		E81C	2E88
// ⺋	 FE58		E81D	2E8B
// 	 FE59		E81E	9FB4
// 㖞	 FE5A		E81F	359E
// 㘚	 FE5B		E820	361A
// 㘎	 FE5C		E821	360E
// ⺌	 FE5D		E822	2E8C
// ⺗	 FE5E		E823	2E97
// 㥮	 FE5F		E824	396E
// 㤘	 FE60		E825	3918
// 	 FE61		E826	9FB5
// 㧏	 FE62		E827	39CF
// 㧟	 FE63		E828	39DF
// 㩳	 FE64		E829	3A73
// 㧐	 FE65		E82A	39D0
// 	 FE66		E82B	9FB6
// 	 FE67		E82C	9FB7
// 㭎	 FE68		E82D	3B4E
// 㱮	 FE69		E82E	3C6E
// 㳠	 FE6A		E82F	3CE0
// ⺧	 FE6B		E830	2EA7
// 	 FE6C		E831	215D7
// 	 FE6D		E832	9FB8
// ⺪	 FE6E		E833	2EAA
// 䁖	 FE6F		E834	4056
// 䅟	 FE70		E835	415F
// ⺮	 FE71		E836	2EAE
// 䌷	 FE72		E837	4337
// ⺳	 FE73		E838	2EB3
// ⺶	 FE74		E839	2EB6
// ⺷	 FE75		E83A	2EB7
// 	 FE76		E83B	2298F
// 䎱	 FE77		E83C	43B1
// 䎬	 FE78		E83D	43AC
// ⺻	 FE79		E83E	2EBB
// 䏝	 FE7A		E83F	43DD
// 䓖	 FE7B		E840	44D6
// 䙡	 FE7C		E841	4661
// 䙌	 FE7D		E842	464C
// 	 FE7E		E843	9FB9
// 䜣	 FE80		E844	4723
// 䜩	 FE81		E845	4729
// 䝼	 FE82		E846	477C
// 䞍	 FE83		E847	478D
// ⻊	 FE84		E848	2ECA
// 䥇	 FE85		E849	4947
// 䥺	 FE86		E84A	497A
// 䥽	 FE87		E84B	497D
// 䦂	 FE88		E84C	4982
// 䦃	 FE89		E84D	4983
// 䦅	 FE8A		E84E	4985
// 䦆	 FE8B		E84F	4986
// 䦟	 FE8C		E850	499F
// 䦛	 FE8D		E851	499B
// 䦷	 FE8E		E852	49B7
// 䦶	 FE8F		E853	49B6
// 	 FE90		E854	9FBA
// 	 FE91		E855	241FE
// 䲣	 FE92		E856	4CA3
// 䲟	 FE93		E857	4C9F
// 䲠	 FE94		E858	4CA0
// 䲡	 FE95		E859	4CA1
// 䱷	 FE96		E85A	4C77
// 䲢	 FE97		E85B	4CA2
// 䴓	 FE98		E85C	4D13
// 䴔	 FE99		E85D	4D14
// 䴕	 FE9A		E85E	4D15
// 䴖	 FE9B		E85F	4D16
// 䴗	 FE9C		E860	4D17
// 䴘	 FE9D		E861	4D18
// 䴙	 FE9E		E862	4D19
// 䶮	 FE9F		E863	4DAE
// 	 FEA0		E864	9FBB
// 
// 在制定GBK时,Unicode中还没有这些字符,所以使用了专用区(PUA)的码位,这80个字符的码位是0xE815-0xE864.后来Unicode将52个汉字收录到"CJK统一汉字扩充A".
// 28个部首中有14个部首被收录到"CJK部首补充区".所以在上表中,这些字符都有两个Unicode编码.
// 
// 上图中淡黄色背景的8个部首被收录到"CJK统一汉字区"的新增区域,即前面提到的0x9FA6-0x9FBB.还有6个淡灰色背景的部首被Unicode收录到"CJK统一汉字扩充B".
// 
// 请注意,淡黄色和淡灰色的14个字符按照GB18030还是应该映射到PUA(Private Use Areas)码位.这14个字符与非PUA码位的映射关系只是网友找出来的,不是标准规定的.
// 如果按照GBK编码,这80个字符应该全部映射到PUA码位.GB18030将其中66个字符映射到了非PUA码位.不过在Windows中,简体中文区域的默认代码页还是GBK,不是GB18030.
// 
// b)CJK兼容汉字区挑选出来的21个汉字.见下表:
// 汉字	GBK编码	Unicode编码
// 郎	FD9C	F92C
// 凉	FD9D	F979
// 秊	FD9E	F995
// 裏	FD9F	F9E7
// 隣	FDA0	F9F1
// 兀	FE40	FA0C
// 嗀	FE41	FA0D
// 﨎	FE42	FA0E
// 﨏	FE43	FA0F
// 﨑	FE44	FA11
// 﨓	FE45	FA13
// 﨔	FE46	FA14
// 礼	FE47	FA18
// 﨟	FE48	FA1F
// 蘒	FE49	FA20
// 﨡	FE4A	FA21
// 﨣	FE4B	FA23
// 﨤	FE4C	FA24
// 﨧	FE4D	FA27
// 﨨	FE4E	FA28
// 﨩	FE4F	FA29
// 
// 3)GB18030
// 在Unicode 5.0的99089个字符中,有71226个字符与汉字有关.它们的分布如下:
// Block名称			开始码位	结束码位	字符数
// CJK统一汉字			4E00		9FBB		20924
// CJK统一汉字扩充A		3400		4DB5		6582
// CJK统一汉字扩充B		20000		2A6D6		42711
// CJK兼容汉字			F900		FA2D		302
// CJK兼容汉字			FA30		FA6A		59
// CJK兼容汉字			FA70		FAD9		106
// CJK兼容汉字补充		2F800		2FA1D		542
// 
// 如果不算兼容汉字,Unicode目前支持的汉字总数是20924+6582+42711=70217.
// 
// GB18030有两个版本:GB18030-2000和GB18030-2005.GB18030-2000是GBK的取代版本,它的主要特点是在GBK基础上增加了CJK统一汉字扩充A的汉字.
// GB18030-2005的主要特点是在GB18030-2000基础上增加了CJK统一汉字扩充B的汉字.(到目前为止应该有三个版本,最新版本为GB18030-2022)
// 
// GB18030是多字节字符集,它的字符可以用一个,两个或四个字节表示.GB18030的码位定义如下:
// 字节数	码位空间						码位数	字符数
// 单字节	0x00~0x7F						128		128
// 双字节	0x8140~0xFEFE					23940	21897
// 四字节	0x81308130~0xFE39FE39			1587600	54531
// 
// GB18030有128+23940+1587600=1611668个码位.Unicode的码位数目是0x110000(1114112),少于GB18030.所以,GB18030有足够的空间映射Unicode的所有码位.
// GB18030的1611668个码位目前定义了128+21897+54531=76556个字符.Unicode 5.0定义了99089个字符.
// 
// GB18030的设计思路可以概括到以下几点:
// a)单字节部分与Unicode一致
// 
// b)双字节部分与GBK兼容.适当调整一些字符与Unicode的映射.这些字符原来因为Unicode没有收录而被映射到PUA,现在因为Unicode已经收录而调整到非PUA的Unicode码位.
// 双字节部分与GBK有两点差异:
// * 在1区增加了11个字符.这样1区就有717+11=728个字符.增加的11个字符是:一个欧元符号(0xA2E3)和10个竖排标点符号(0xA6D9-0xA6DF,0xA6EC-0xA6ED和0xA6F3).
// * 原来因为Unicode没有收录而映射到PUA的字符中的部分字符被新版本的Unicode收录,所以将这些字符映射到非PUA的码位.
// 
// c)将Unicode BMP部分还没有映射的39420个码位顺序映射到从0x81308130开始的四字节部分.
// Unicode的BMP一共有65536个码位.其中代理区(0xD800-0xDFFF)有2048个码位,这2048个码位是不能定义字符的.GB18030的单字节部分映射了128个码位,GB18030的双字节部分映射了23940个码位.还剩下65536-2048-128-23940=39420个码位.
// GB18030将这39420个码位顺序映射到从0x81308130开始的码位空间.
// GB18030双字节部分与Unicode的映射没有规律,只能通过查表方法映射.
// 
// d)将Unicode BMP以外的16个辅助平面映射到从0x90308130开始的四字节部分.
// 其中定义字符的只有两个区域:
// * GB18030用码位0x81308130~0x8439FE39共50400个码位映射该标准单字节和双字节部分没有映射过的39420个Unicode BMP码位(c部分已经介绍过).
// * GB18030用码位0x90308130~0xE339FE39共1058400个码位映射Unicode 16个辅助平面(平面1到平面16)的65536*16=1048576个码位.这部分映射是可以直接用公式计算的.
// 从GB18030编码到Unicode编码的映射方法如下:
// 设GB18030编码的四个字节依次为:b1,b2,b3,b4,则Unicode编码=0x10000+(b1-0x90)*12600+(b2-0x30)*1260+(b3-0x81)*10+b4-0x30
// 
// 从Unicode编码到GB18030编码的映射方法如下:
// U=Unicode编码-0x10000
// m1=U/12600
// n1=U%12600
// m2=n1/1260
// n2=n1%1260
// m3=n2/10
// n3=n2%10
// 第一字节b1=m1+0x90,第二字节b2=m2+0x30,第三字节b3=m3+0x81,第四字节b4=n3+0x30.
// 
// 在GB18030目前定义的76556个字符中,只有24个字符被定义到Unicode的PUA区.这24个字符包括1区的10个竖排标点符号(0xA6D9-0xA6DF,0xA6EC-0xA6ED和0xA6F3)和4区的14个汉字(0xFE51,0xFE52,0xFE53,0xFE59,0xFE61,0xFE66,0xFE67,0xFE6C,0xFE6D,0xFE76,0xFE7E,0xFE90,0xFE91,0xFEA0).
// 4区的14个汉字在Unicode 5.0中其实也可以找到非PUA的编码,详见<<Unicode、GB2312、GBK和GB18030中的汉字>>.但按照GB18030,它们还是应该映射到PUA码位.
// 
// 无论是Windows XP还是Vista,中文(中国)区域对应的默认代码页还是GBK.我们只能设置区域,并不能设置区域对应的默认代码页.
// 所以在Windows世界,只要微软不愿意,GB18030就只是一张普通的代码页.目前的简体中文文档使用的编码主要是Unicode和GBK,应该没有什么文档会用GB18030保存.
// 本文只是出于程序员的好奇而对GB18030编码所作的一些研究,希望能对同样好奇的读者有所助益.
// 
// 4)判断字符串是否UTF8编码
// 网上有很多例子都说可以通过UTF-8的实现方式来判断当前字符串是否为UTF-8(即:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx),但其实这个方法是不准确的,
// GBK里面的一些字符串完全满足这种方式,例如:"蓝色","联通"等,所以像iconv这样的库只有"从xxx字符集转xxx字符集",并没有给出如何判断一个字符串是否为UTF-8的方法.
// 
// 5)如何验证我们的库是否正确
// 因GB18030并未大规模的使用,并且GB系列与Unicode之间的映射关系一直在变化,所以最好的验证方法是用第三方库将GB系列下的字符转为Unicode,在用自己写的库实现一遍,两边结果做对比(Windows和Linux都要做).
// 网页给出的附件里给出了所有GB的编码,所以最好所有字符都验证一遍.
// 
// 以上大部分内容来源:
// http://www.fmddlmyy.cn/text24.html
// http://www.cppblog.com/woaidongmao/archive/2008/11/08/66314.html
// http://www.cppblog.com/woaidongmao/archive/2009/09/10/95867.html (可在此网页下载GBK,GB18030和Unicode的对应表)
// https://www.toolhelper.cn/Encoding/GB2312 (可以查看GB2312的编码表,但GB2312的符号区并不是682个字符,同时汉字区好像是从GBK直接拷贝过来的,每个区的第一个字符应该是没有的,这里也不对)
// https://www.toolhelper.cn/Encoding/GBK (可以查看GBK的编码表)
// http://www.cppblog.com/woaidongmao/archive/2009/09/10/95868.html
// http://www.cppblog.com/woaidongmao/archive/2009/11/17/101195.html
// http://www.cppblog.com/woaidongmao/archive/2012/03/01/166851.html
// 
// UTF系列转换代码来源:
// https://www.cnblogs.com/snowberg/archive/2011/09/30/2468595.html
// https://www.cnblogs.com/mickole/articles/3663924.html
// $_FILEHEADER_END ***********************************************************

#ifndef CHARSET_H
#define CHARSET_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <tuple>
#include "TypeDef.h"

class CCharset
{
public:
	CCharset();
	~CCharset() = default;

public:
	// 因有些系统还未使用c++11,所以这里给出c和c++实现的两套UTF-8/Unicode,UTF-8/UTF-16,UTF-8/UTF-32互转代码
	// 注意:wchar_t在windows下为2字节,而在linux下为4字节
	// UTF-8转Unicode
	std::tuple<bool, std::vector<wchar_t>> UTF8_2_Unicode_Cpp(const char* apUTF8);
	// Unicode转UTF-8
	std::tuple<bool, std::vector<char>> Unicode_2_UTF8_Cpp(const wchar_t* apUnicode);
	// UTF-8转UTF-16
	std::tuple<bool, std::vector<char16_t>> UTF8_2_UTF16_Cpp(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian);
	// UTF-16转UTF-8
	std::tuple<bool, std::vector<char>> UTF16_2_UTF8_Cpp(const char16_t* apUTF16, MyUInt32 aiUTF16Len);
	// UTF-8转UTF-32
	std::tuple<bool, std::vector<char32_t>> UTF8_2_UTF32_Cpp(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian);
	// UTF32转UTF-8
	std::tuple<bool, std::vector<char>> UTF32_2_UTF8_Cpp(const char32_t* apUTF32, MyUInt32 aiUTF32Len);

	// UTF-8转Unicode
	std::tuple<bool, std::vector<MyUInt16>> UTF8_2_Unicode_C(const char* apUTF8, MyUInt32 aiUTF8Len);
	// Unicode转UTF-8
	std::tuple<bool, std::vector<char>> Unicode_2_UTF8_C(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen);
	// UTF-8转UTF-16
	std::tuple<bool, std::vector<MyUInt16>> UTF8_2_UTF16_C(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian);
	// UTF-16转UTF-8
	std::tuple<bool, std::vector<char>> UTF16_2_UTF8_C(const MyUInt16* apUTF16, MyUInt32 aiUTF16Len, bool abBigEndian);
	// UTF-8转UTF-32
	std::tuple<bool, std::vector<MyUInt32>> UTF8_2_UTF32_C(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian);
	// UTF32转UTF-8
	std::tuple<bool, std::vector<char>> UTF32_2_UTF8_C(const MyUInt32* apUTF32, MyUInt32 aiUTF32Len, bool abBigEndian);

	// GB2312转Unicode
	std::tuple<bool, std::vector<MyUInt16>> GB2312_2_Unicode(const char* apGB2312, MyUInt32 aiGB2312Len);
	// Unicode转GB2312
	std::tuple<bool, std::vector<char>> Unicode_2_GB2312(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen);

	// GB2312转UTF-8
	std::tuple<bool, std::vector<char>> GB2312_2_UTF8(const char* apGB2312, MyUInt32 aiGB2312Len);
	// UTF-8转GB2312
	std::tuple<bool, std::vector<char>> UTF8_2_GB2312(const char* apUTF8, MyUInt32 aiUTF8Len);

	// GBK转Unicode
	std::tuple<bool, std::vector<MyUInt16>> GBK_2_Unicode(const char* apGBK, MyUInt32 aiGBKLen);
	// Unicode转GBK
	std::tuple<bool, std::vector<char>> Unicode_2_GBK(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen);

	// GBK转UTF-8
	std::tuple<bool, std::vector<char>> GBK_2_UTF8(const char* apGBK, MyUInt32 aiGBKLen);
	// UTF-8转GBK
	std::tuple<bool, std::vector<char>> UTF8_2_GBK(const char* apUTF8, MyUInt32 aiUTF8Len);

	// GB18030转Unicode
	std::tuple<bool, std::vector<MyUInt16>> GB18030_2_Unicode(const char* apGB18030, MyUInt32 aiGB18030Len);
	// Unicode转GB18030
	std::tuple<bool, std::vector<char>> Unicode_2_GB18030(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen);

	// GB18030转UTF-8
	std::tuple<bool, std::vector<char>> GB18030_2_UTF8(const char* apGB18030, MyUInt32 aiGB18030Len);
	// UTF-8转GB18030
	std::tuple<bool, std::vector<char>> UTF8_2_GB18030(const char* apUTF8, MyUInt32 aiUTF8Len);

private:
	// Unicode转UTF-8
	MyUInt32 Unicode_2_UTF8(MyUInt32 aiUnicode, char* apUTF8);
	// UTF-8转Unicode
	std::tuple<MyUInt32, MyUInt32> UTF8_2_Unicode(const char* apUTF8, MyUInt16* apUnicode);
	// UTF-32转UTF-8
	MyUInt32 UTF32_2_UTF8(MyUInt32 aiUTF32, char* apUTF8);
	// UTF-8转UTF-32
	MyUInt32 UTF8_2_UTF32(const char* apUTF8, MyUInt32& aiUTF32);
	// UTF-32转UTF-16
	MyUInt32 UTF32_2_UTF16(MyUInt32 aiUTF32, MyUInt16* apUTF16);
	// UTF-16转UTF-32
	MyUInt32 UTF16_2_UTF32(const MyUInt16* apUTF16, MyUInt32& aiUTF32);

	// UTF-8转Unicode(字符串)
	MyUInt32 UTF8_2_Unicode(const char* apUTF8, MyUInt32 aiUTF8Len, MyUInt16* apUnicode);
	// Unicode转UTF-8(字符串)
	MyUInt32 Unicode_2_UTF8(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen, char* apUTF8);
	// UTF-8转UTF-16(字符串)
	MyUInt32 UTF8_2_UTF16(const char* apUTF8, MyUInt32 aiUTF8Len, MyUInt16* apUTF16);
	// UTF-16转UTF-8(字符串)
	MyUInt32 UTF16_2_UTF8(const MyUInt16* apUTF16, MyUInt32 aiUTF16Len, char* apUTF8);
	// UTF-8转UTF-32(字符串)
	MyUInt32 UTF8_2_UTF32(const char* apUTF8, MyUInt32 aiUTF8Len, MyUInt32* apUTF32);
	// UTF-32转UTF-8(字符串)
	MyUInt32 UTF32_2_UTF8(const MyUInt32* apUTF32, MyUInt32 aiUTF32Len, char* apUTF8);

private:
	// 初始化GB编码表
	void InitGBTable();

private:
	// GB2312到Unicode编码表
	std::unordered_map<MyUInt16, MyUInt16> m_GB2312_2_Unicode_Tables;
	// Unicode到GB2312编码表
	std::unordered_map<MyUInt16, MyUInt16> m_Unicode_2_GB2312_Tables;

	// GBK到Unicode编码表
	std::unordered_map<MyUInt16, MyUInt16> m_GBK_2_Unicode_Tables;
	// Unicode到GBK编码表
	std::unordered_map<MyUInt16, MyUInt16> m_Unicode_2_GBK_Tables;

	// GB18030双字节部分到Unicode编码表
	std::unordered_map<MyUInt16, MyUInt16> m_GB18030_2Byte_2_Unicode_Tables;
	// Unicode到GB18030双字节部分编码表
	std::unordered_map<MyUInt16, MyUInt16> m_Unicode_2_GB18030_2Byte_Tables;
	// GB18030四字节部分到Unicode编码表
	std::unordered_map<MyUInt32, MyUInt16> m_GB18030_4Byte_2_Unicode_Tables;
	// Unicode到GB18030四字节部分编码表
	std::unordered_map<MyUInt16, MyUInt32> m_Unicode_2_GB18030_4Byte_Tables;
};

#endif