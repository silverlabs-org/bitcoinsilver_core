.PHONY: FORCE
all: FORCE
	$(MAKE) -C .. bitcoinsilver_qt test_bitcoinsilver_qt
clean: FORCE
	$(MAKE) -C .. bitcoinsilver_qt_clean test_bitcoinsilver_qt_clean
check: FORCE
	$(MAKE) -C .. test_bitcoinsilver_qt_check
bitcoinsilver-qt bitcoinsilver-qt.exe: FORCE
	 $(MAKE) -C .. bitcoinsilver_qt
apk: FORCE
	$(MAKE) -C .. bitcoinsilver_qt_apk
