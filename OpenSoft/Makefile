all:
	$(MAKE) opensoft -C build/
	cp build/opensoft

clean:
	$(MAKE) clean -C build/
	$(RM) opensoft

distclean:
	rm -r build/
	$(RM) opensoft

.PHONY: all clean distclean
