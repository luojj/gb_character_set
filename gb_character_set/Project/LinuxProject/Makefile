#项目路径
INCLUDE_PATH := ../../Include
SRC_PATH := ../../Src

#项目的输出路径
OUTPUT_PATH := .

#根据Debug或Release生成的项目名称
DEBUG_NAME = $(OUTPUT_PATH)/TestD
RELEASE_NAME = $(OUTPUT_PATH)/Test

#使用的编译器
export CC = g++

#Debug或Release默认编译器选项
export DEBUG_FLAGS = -O0 -g -Wall -fmessage-length=0 -DDEBUG -std=c++20 -Wl,--no-as-needed -fconstexpr-loop-limit=1000000
#-O3:最高级别优化
export RELEASE_FLAGS = -O3 -g -Wall -fmessage-length=0 -DNDEBUG -std=c++20 -Wl,--no-as-needed -fconstexpr-loop-limit=1000000

#根据Debug或Release调整生成的项目名称和编译器选项
ifeq ($(CFLAG), DEBUG)
PROJECT_NAME := $(DEBUG_NAME)
CLEAN_NAME := $(DEBUG_NAME)
CFLAGS := $(DEBUG_FLAGS)
else
PROJECT_NAME := $(RELEASE_NAME)
CLEAN_NAME := $(RELEASE_NAME)
CFLAGS := $(RELEASE_FLAGS)
endif

#项目需要引用的其他文件所在的目录
INCLUDE_PATH := -I. -I$(INCLUDE_PATH) -I$(SRC_PATH)

#递归遍历5级子目录
DIRS := $(shell find $(SRC_PATH) -maxdepth 5 -type d)
#循环遍历目录的cpp/cc文件
CPP_FILES = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp)) ./main.cpp
CC_FILES = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cc))
#替换文件后缀,也可以写成 OBJS = $(CPP_FILES:%.cpp=%.o)
#目标文件
OBJS = $(patsubst %.cpp,%.o,$(CPP_FILES)) $(patsubst %.cc,%.o,$(CC_FILES))
#依赖文件
DEPS = $(patsubst %.cpp,%.d,$(CPP_FILES)) $(patsubst %.cc,%.d,$(CC_FILES))
#项目需要生成的链接文件
PROJECT_OBJ := $(OBJS)

#开始编写Makefile脚本
#"all"的执行顺序是从左到右
all : $(PROJECT_NAME)

#生成程序
$(PROJECT_NAME) : $(PROJECT_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -o $(PROJECT_NAME) $^

#添加依赖关系
-include $(DEPS)

#生成.o规则
#-M:生成文件的依赖关系,同时也把一些标准库的头文件包含进来.
#-MF:把依赖关系写入名为"File"的文件中.若同时使用了"-MD"或"-MMD",会覆写输出的依赖文件名称.
#-MD:等同于"-M -MF File",但默认关闭了"-E"选项.不会像"-M"那样阻止正常的编译任务.
#-MMD:类似"-MD",但输出的依赖文件中不包括标准头文件.
#-MP:在生成的.d文件中为每个头文件添加一个空的伪目标规则.(用于头文件修改后可以重新编译)
#通过"-MMD -MF -MP"实现头文件及源文件修改后的增量编译.
%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@ $(USER_MACRO) -MMD -MF $*.d -MP

%.o : %.cc
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@ $(USER_MACRO) -MMD -MF $*.d -MP

.PHONY : clean
clean :
	rm -f $(CLEAN_NAME) $(OBJS) $(DEPS)