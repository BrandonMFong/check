##
# author: brando
# date: 11/15/24
#

### Dependencies

LIBS_BIN_PATH = bin/libs
OPENSSL_BIN_PATH = bin/openssl

build: build-libs build-openssl

clean: clean-libs clean-openssl
	rm -rfv bin

## Libs

clean-libs:
	rm -rfv $(LIBS_BIN_PATH)

setup-libs:
	mkdir -p $(LIBS_BIN_PATH)

LIBS = bflibc bftest
LIBS_ASSETS = libs/bin/debug libs/bin/release
build-libs: setup-libs $(LIBS)
	cp -afv $(LIBS_ASSETS) $(LIBS_BIN_PATH)

$(LIBS):
	cd libs && make $@

## OpenSSL

SETUP_OPENSSL_DIRS = \
	$(OPENSSL_BIN_PATH)-arm $(OPENSSL_BIN_PATH)-intel \
	$(OPENSSL_BIN_PATH)-uni $(OPENSSL_BIN_PATH)
setup-openssl: $(SETUP_OPENSSL_DIRS)
$(SETUP_OPENSSL_DIRS):
	mkdir -p $@

clean-openssl:
	rm -rfv $(SETUP_OPENSSL_DIRS)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
build-openssl: \
	setup-openssl build-openssl-arm build-openssl-intel \
	$(OPENSSL_BIN_PATH)-uni/libssl.a \
	$(OPENSSL_BIN_PATH)-uni/libcrypto.a

$(OPENSSL_BIN_PATH)-uni/libssl.a: 
	lipo -create $(OPENSSL_BIN_PATH)-arm/libssl.a \
	$(OPENSSL_BIN_PATH)-intel/libssl.a -output $@
	
$(OPENSSL_BIN_PATH)-uni/libcrypto.a: 
	lipo -create $(OPENSSL_BIN_PATH)-arm/libcrypto.a \
	$(OPENSSL_BIN_PATH)-intel/libcrypto.a -output $@

build-openssl-arm:
	cd $(OPENSSL_BIN_PATH)-arm \
	&& ../../openssl/Configure darwin64-arm64 \
	CPPFLAGS="-target arm64-apple-macos11" && make
build-openssl-intel:
	cd $(OPENSSL_BIN_PATH)-intel \
	&& ../../openssl/Configure darwin64-x86_64 \
	CPPFLAGS="-target x86_64-apple-macos10.12" && make

else # ($(UNAME_S),???)
build-openssl: setup-openssl
	cd $(OPENSSL_BIN_PATH) && ../../openssl/Configure && make
	cd $(OPENSSL_BIN_PATH) && cp -afv ../../openssl/include .
endif # ($(UNAME_S),???)


