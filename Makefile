.DEFAULT_GOAL := target

ARCH ?= riscv64
MODE ?= release
CHAPTER ?= 
app_dir = src
elf_dir := build/$(ARCH)
bin_dir := build/bin
out_dir := target
cmake_build_args := -DARCH=$(ARCH) -DCHAPTER=$(CHAPTER)
ifeq ($(MODE), release)
cmake_build_args += -DCMAKE_BUILD_TYPE=Release
else ifeq ($(MODE), debug)
cmake_build_args += -DCMAKE_BUILD_TYPE=Debug
endif

OBJCOPY := $(ARCH)-linux-musl-objcopy
OBJDUMP := $(ARCH)-linux-musl-objdump
CP := cp
CH_TESTS :=  

CH2_BASE_TESTS := ch2b_
CH3_BASE_TESTS := ch3b_ $(CH2_BASE_TESTS)
CH4_BASE_TESTS := $(CH2_BASE_TESTS) ch3b_yield # ch4b_
CH5_BASE_TESTS := ch5b_ $(CH3_BASE_TESTS) usershell
CH6_BASE_TESTS := ch6b_ $(CH5_BASE_TESTS) 
CH7_BASE_TESTS := ch7b_ $(CH5_BASE_TESTS) 
CH8_BASE_TESTS := ch8b_ $(CH6_BASE_TESTS) 


CH2_TESTS := $(CH2_BASE_TESTS)
CH3_TESTS := ch3b_ $(CH2_TESTS) ch3_
CH4_TESTS := $(CH4_BASE_TESTS) ch4_ ch3b_sleep ch3_
CH5_TESTS_BASE := ch5b_ $(CH4_TESTS) ch5_ ch5t_ usershell 
CH5_SCHED_TEST := ch5t_
CH6_TESTS := ch6b_ $(CH5_TESTS_BASE) ch6_
CH7_TESTS := ch7b_ $(CH5_TESTS_BASE) ch7_
CH8_TESTS := $(CH8_BASE_TESTS) ch8_

BASE ?= 0

ifeq ($(BASE), 1)
CH2_TESTS := $(CH2_BASE_TESTS)
CH3_TESTS := $(CH3_BASE_TESTS)
CH4_TESTS := $(CH4_BASE_TESTS)
CH5_TESTS_BASE := $(CH5_BASE_TESTS)
CH6_TESTS := $(CH6_BASE_TESTS)
CH7_TESTS := $(CH7_BASE_TESTS)
CH8_TESTS := $(CH8_BASE_TESTS)
endif

ifeq ($(CHAPTER), 2)
	CH_TESTS := $(CH2_TESTS)
else ifeq ($(CHAPTER), 2_bad)
	CH_TESTS := __ch2_bad_
else ifeq ($(CHAPTER), 3)
	CH_TESTS := $(CH3_TESTS)
else ifeq ($(CHAPTER), 4)
	CH_TESTS := $(CH4_TESTS)
else ifeq ($(CHAPTER), 4_3)
	CH_TESTS := $(CH4_BASE_TESTS) ch3b_sleep ch3_taskinfo
else ifeq ($(CHAPTER), 4_only)
	CH_TESTS := ch4_ ch4b_
else ifeq ($(CHAPTER), 5)
	CH_TESTS := $(CH5_TESTS_BASE)
else ifeq ($(CHAPTER), 5_only)
	CH_TESTS := ch5_ ch5b_ ch5t_
else ifeq ($(CHAPTER), 5t)
	CH_TESTS := $(CH5_SCHED_TEST)
else ifeq ($(CHAPTER), 6)
	CH_TESTS := $(CH6_TESTS)
else ifeq ($(CHAPTER), 6_only)
	CH_TESTS := ch6_ ch6b_
else ifeq ($(CHAPTER), 7)
	CH_TESTS := $(CH7_TESTS)
else ifeq ($(CHAPTER), 7_only)
	CH_TESTS := ch7_ ch7b_
else ifeq ($(CHAPTER), 8)
	CH_TESTS := $(CH8_TESTS)
else ifeq ($(CHAPTER), 8_only)
	CH_TESTS := ch8_
endif

binary:
	@mkdir -p build
	@cd build && CHAPTER=$(CHAPTER) cmake $(cmake_build_args) .. && make -j`nproc`
	@mkdir -p asm
	@$(CP) build/asm/* asm

del:
	@rm -rf $(out_dir)
	@mkdir -p $(out_dir)/bin/
	@mkdir -p $(out_dir)/elf/

target: binary del
	@echo tests=$(CH_TESTS)
	@$(foreach t, $(CH_TESTS), cp $(bin_dir)/$(t)* $(out_dir)/bin/;)
	@$(foreach t, $(CH_TESTS), cp $(elf_dir)/$(t)* $(out_dir)/elf/;)

clean:
	@rm -rf asm build target
