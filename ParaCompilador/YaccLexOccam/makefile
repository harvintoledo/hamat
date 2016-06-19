YFLAGS = -d	# force creation of y.tab.h
OBJS = occam.o code.o init.o math.o symbol.o  # abbrebiation

occam:	$(OBJS)
	cc $(OBJS) -lm -o occam

occam.o code.o init.o symbol.o:	occam.h

code.o init.o symbol.o:	x.tab.h

x.tab.h:	y.tab.h

	-cmp -s x.tab.h y.tab.h || cp y.tab.h x.tab.h

pr:
	@pr occam.y occam.h code.c init.c math.c symbol.c makefile
	@pr $?
	@touch pr
clean:
	rm -f $(OBJS) [xy].tab.[ch]
