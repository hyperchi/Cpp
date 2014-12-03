#
# The compiler and its flags
#
CPP= g++ 
INCLUDE=-I./
       
CPPFLAGS=-g -O3 -w $(INCLUDE)
LIBS=  -lpthread              \
       -L/usr/local/lib 

#
# Sources and objects
#
srcpath=  .
workdir=  ../workdir

COMMON= 

PROGRAM= AmoiensisNQ

SRC=\
    $(srcpath)/ConfFileRead.cpp		\
    $(srcpath)/BasicConfigure.cpp	\
    $(srcpath)/Connection.cpp		\
    $(srcpath)/CommandHandle.cpp	\
    $(srcpath)/CommandQuene.cpp		\
    $(srcpath)/Communication.cpp	\
    $(srcpath)/Predicate.cpp		\
    $(srcpath)/Matrix.cpp		\
    $(srcpath)/Geometry.cpp		\
    $(srcpath)/WorldModel.cpp		\
    $(srcpath)/WorldModelInit.cpp	\
    $(srcpath)/WorldModelUpdate.cpp	\
    $(srcpath)/WorldModelParse.cpp	\
    $(srcpath)/Situation.cpp	\
    $(srcpath)/SitUnitSquare.cpp	\
    $(srcpath)/SitDribble.cpp	\
    $(srcpath)/SitKick.cpp	\
    $(srcpath)/SitPass.cpp	\
    $(srcpath)/SitRun.cpp	\
    $(srcpath)/Formation.cpp	\
    $(srcpath)/Attitude.cpp		\
    $(srcpath)/Logger.cpp		\
    $(srcpath)/Timer.cpp		\
    $(srcpath)/JointControl.cpp	\
    $(srcpath)/Action.cpp		\
    $(srcpath)/HumanoidControl.cpp	\
    $(srcpath)/BasicWalk.cpp	\
    $(srcpath)/Kinematics.cpp	\
    $(srcpath)/Dribble.cpp		\
    $(srcpath)/Kick.cpp			\
    $(srcpath)/ActionTurn.cpp	\
    $(srcpath)/ActionTrans.cpp	\
    $(srcpath)/Motion.cpp		\
    $(srcpath)/MotionGoto.cpp	\
    $(srcpath)/SmartGoto.cpp	\
    $(srcpath)/MotionDribble.cpp	\
    $(srcpath)/MotionKick.cpp	\
    $(srcpath)/MotionPass.cpp	\
    $(srcpath)/HumanGoto.cpp	\
	$(srcpath)/Obstacle.cpp		\
    $(srcpath)/HandleBall.cpp	\
    $(srcpath)/RunPosition.cpp	\
    $(srcpath)/Brain.cpp		\
    $(srcpath)/BrainGoalie.cpp	\
    $(srcpath)/BrainNormal.cpp	\
    $(srcpath)/coach.cpp		\
    $(srcpath)/Vision.cpp		\
	$(srcpath)/Hear.cpp			\
	$(srcpath)/Say.cpp			\
    $(srcpath)/AgentInfo.cpp	\
    $(srcpath)/Agent.cpp		\
    $(srcpath)/main.cpp
    

OBJ=$(SRC:.cpp=.o)

all : $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ) $(LIBS)

clean:
	@echo "Removing objects..."
	rm -f $(PROGRAMS) *.o *~ core 

install: $(PROGRAM)
	cp -f $(PROGRAM) $(workdir)/

ConfFileRead.o: ConfFileRead.cpp ConfFileRead.h /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h
BasicConfigure.o: BasicConfigure.cpp BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc
Connection.o: Connection.cpp Connection.h /usr/include/arpa/inet.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/netinet/in.h /usr/include/stdint.h \
 /usr/include/bits/wchar.h /usr/include/sys/socket.h \
 /usr/include/sys/uio.h /usr/include/sys/types.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/time.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/uio.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm-generic/socket.h \
 /usr/include/asm/sockios.h /usr/include/asm-generic/sockios.h \
 /usr/include/bits/in.h stdinc.h /usr/include/c++/4.4/cstdlib \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/xlocale.h /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/c++/4.4/cmath /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/postypes.h \
 /usr/include/c++/4.4/cwchar /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/sched.h \
 /usr/include/signal.h /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc /usr/include/string.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/bits/locale_classes.h \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc Timer.h \
 /usr/include/c++/4.4/iomanip /usr/include/sys/time.h Logger.h \
 /usr/include/sys/wait.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h \
 /usr/include/sys/resource.h /usr/include/bits/resource.h \
 /usr/include/netdb.h /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
CommandHandle.o: CommandHandle.cpp CommandHandle.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h EnumType.h /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h Connection.h \
 /usr/include/arpa/inet.h /usr/include/netinet/in.h /usr/include/stdint.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/uio.h /usr/include/bits/socket.h \
 /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
 /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h \
 /usr/include/asm-generic/sockios.h /usr/include/bits/in.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/c++/4.4/cmath /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/string.h \
 /usr/include/c++/4.4/fstream /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/vector /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc Timer.h \
 /usr/include/c++/4.4/iomanip /usr/include/sys/time.h CommandQuene.h
CommandQuene.o: CommandQuene.cpp CommandQuene.h /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_multimap.h EnumType.h \
 /usr/include/c++/4.4/string /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/basic_string.tcc Logger.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/bits/locale_classes.h \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc
Communication.o: Communication.cpp Communication.h \
 /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/postypes.h \
 /usr/include/c++/4.4/cwchar /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc
Predicate.o: Predicate.cpp stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 Predicate.h stdinc.h /usr/include/c++/4.4/cstdlib \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/c++/4.4/cstdio /usr/include/c++/4.4/cmath \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/postypes.h \
 /usr/include/c++/4.4/cwchar /usr/include/bits/wchar.h \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/sched.h \
 /usr/include/signal.h /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc /usr/include/string.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/bits/locale_classes.h \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc Geometry.h FloatMath.h Object.h \
 BasicConfigure.h EnumType.h Hear.h Encryption.h Logger.h
Matrix.o: Matrix.cpp stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h Matrix.h \
 stdinc.h /usr/include/c++/4.4/cstdlib \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/c++/4.4/cstdio /usr/include/c++/4.4/cmath \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/postypes.h \
 /usr/include/c++/4.4/cwchar /usr/include/bits/wchar.h \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/sched.h \
 /usr/include/signal.h /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc /usr/include/string.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/bits/locale_classes.h \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/memory.h FloatMath.h \
 Logger.h
Geometry.o: Geometry.cpp stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h Geometry.h \
 FloatMath.h /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef /usr/include/bits/wchar.h \
 /usr/include/xlocale.h /usr/include/c++/4.4/exception \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc
WorldModel.o: WorldModel.cpp WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
WorldModelInit.o: WorldModelInit.cpp stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 WorldModel.h BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef /usr/include/bits/wchar.h \
 /usr/include/xlocale.h /usr/include/c++/4.4/exception \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/c++/4.4/cmath /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/string.h \
 /usr/include/c++/4.4/fstream /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
WorldModelUpdate.o: WorldModelUpdate.cpp WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
WorldModelParse.o: WorldModelParse.cpp WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
Situation.o: Situation.cpp Situation.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/algorithm \
 /usr/include/c++/4.4/bits/stl_algo.h /usr/include/c++/4.4/cstdlib \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/xlocale.h /usr/include/sys/types.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/time.h /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/alloca.h /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Geometry.h \
 FloatMath.h Logger.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/sched.h \
 /usr/include/signal.h /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc WorldModel.h BasicConfigure.h \
 stdinc.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 ConfFileRead.h Predicate.h Object.h EnumType.h Hear.h Encryption.h \
 Matrix.h /usr/include/memory.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Formation.h SitUnitSquare.h \
 SitDribble.h SitKick.h SitPass.h SitRun.h coach.h
SitUnitSquare.o: SitUnitSquare.cpp SitUnitSquare.h WorldModel.h \
 BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
SitDribble.o: SitDribble.cpp SitDribble.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc AgentInfo.h SitUnitSquare.h
SitKick.o: SitKick.cpp SitKick.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc AgentInfo.h SitUnitSquare.h
SitPass.o: SitPass.cpp SitPass.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc AgentInfo.h SitUnitSquare.h
SitRun.o: SitRun.cpp SitRun.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc AgentInfo.h SitUnitSquare.h
Formation.o: Formation.cpp Formation.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
Attitude.o: Attitude.cpp
Logger.o: Logger.cpp Logger.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h /usr/include/c++/4.4/cstdio \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc
Timer.o: Timer.cpp Timer.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/iomanip \
 /usr/include/sys/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h
JointControl.o: JointControl.cpp JointControl.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc EnumType.h /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h WorldModel.h BasicConfigure.h \
 stdinc.h /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/c++/4.4/cmath /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/string.h \
 /usr/include/c++/4.4/fstream /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 ConfFileRead.h Predicate.h Geometry.h FloatMath.h Object.h Hear.h \
 Encryption.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h
Action.o: Action.cpp Action.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h JointControl.h \
 ActionData.h ActionKickData.h ActionKickNew.h ActionGetUpData.h \
 HumanoidControl.h BasicWalk.h Kinematics.h
ActionTurn.o: ActionTurn.cpp Action.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h JointControl.h \
 ActionData.h ActionKickData.h ActionKickNew.h ActionGetUpData.h \
 HumanoidControl.h BasicWalk.h Kinematics.h
ActionTrans.o: ActionTrans.cpp Action.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h JointControl.h \
 ActionData.h ActionKickData.h ActionKickNew.h ActionGetUpData.h \
 HumanoidControl.h BasicWalk.h Kinematics.h
HumanoidControl.o: HumanoidControl.cpp stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 HumanoidControl.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc Matrix.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/c++/4.4/cstdio /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/c++/4.4/string /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/sched.h \
 /usr/include/signal.h /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/basic_string.tcc /usr/include/string.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/bits/locale_classes.h \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/memory.h \
 FloatMath.h Logger.h JointControl.h EnumType.h WorldModel.h \
 BasicConfigure.h ConfFileRead.h Predicate.h Geometry.h Object.h Hear.h \
 Encryption.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h
Dribble.o: Dribble.cpp Dribble.h stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 WorldModel.h BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef /usr/include/bits/wchar.h \
 /usr/include/xlocale.h /usr/include/c++/4.4/exception \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/c++/4.4/cmath /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/string.h \
 /usr/include/c++/4.4/fstream /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 HumanGoto.h Obstacle.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
Kick.o: Kick.cpp Kick.h stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 WorldModel.h BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef /usr/include/bits/wchar.h \
 /usr/include/xlocale.h /usr/include/c++/4.4/exception \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/c++/4.4/cmath /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/string.h \
 /usr/include/c++/4.4/fstream /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 HumanGoto.h Obstacle.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
Motion.o: Motion.cpp Motion.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h ConfFileRead.h \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/xlocale.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 MotionGoto.h Action.h JointControl.h ActionData.h ActionKickData.h \
 ActionKickNew.h ActionGetUpData.h HumanoidControl.h BasicWalk.h \
 Kinematics.h HumanGoto.h stdafx.h Obstacle.h Dribble.h Kick.h \
 HandleBall.h MotionDribble.h MotionKick.h MotionPass.h RunPosition.h
MotionGoto.o: MotionGoto.cpp MotionGoto.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 Action.h JointControl.h ActionData.h ActionKickData.h ActionKickNew.h \
 ActionGetUpData.h HumanoidControl.h BasicWalk.h Kinematics.h
SmartGoto.o: SmartGoto.cpp MotionGoto.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 Action.h JointControl.h ActionData.h ActionKickData.h ActionKickNew.h \
 ActionGetUpData.h HumanoidControl.h BasicWalk.h Kinematics.h
MotionDribble.o: MotionDribble.cpp MotionDribble.h WorldModel.h \
 BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 MotionGoto.h CommandQuene.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
MotionKick.o: MotionKick.cpp MotionKick.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 MotionGoto.h CommandQuene.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
MotionPass.o: MotionPass.cpp MotionPass.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 MotionGoto.h CommandQuene.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
HumanGoto.o: HumanGoto.cpp HumanGoto.h stdafx.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h Obstacle.h \
 WorldModel.h BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef /usr/include/bits/wchar.h \
 /usr/include/xlocale.h /usr/include/c++/4.4/exception \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio \
 /usr/include/c++/4.4/cmath /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/string.h \
 /usr/include/c++/4.4/fstream /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 Action.h JointControl.h ActionData.h ActionKickData.h ActionKickNew.h \
 ActionGetUpData.h HumanoidControl.h BasicWalk.h Kinematics.h
Obstacle.o: Obstacle.cpp Obstacle.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
HandleBall.o: HandleBall.cpp HandleBall.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 MotionGoto.h CommandQuene.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
RunPosition.o: RunPosition.cpp RunPosition.h WorldModel.h \
 BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 MotionGoto.h CommandQuene.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h
Brain.o: Brain.cpp Brain.h ConfFileRead.h /usr/include/c++/4.4/map \
 /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 CommandQuene.h Motion.h MotionGoto.h Action.h JointControl.h \
 ActionData.h ActionKickData.h ActionKickNew.h ActionGetUpData.h \
 HumanoidControl.h BasicWalk.h Kinematics.h HumanGoto.h stdafx.h \
 Obstacle.h Dribble.h Kick.h HandleBall.h MotionDribble.h MotionKick.h \
 MotionPass.h RunPosition.h Vision.h Say.h
BrainGoalie.o: BrainGoalie.cpp Brain.h ConfFileRead.h \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 CommandQuene.h Motion.h MotionGoto.h Action.h JointControl.h \
 ActionData.h ActionKickData.h ActionKickNew.h ActionGetUpData.h \
 HumanoidControl.h BasicWalk.h Kinematics.h HumanGoto.h stdafx.h \
 Obstacle.h Dribble.h Kick.h HandleBall.h MotionDribble.h MotionKick.h \
 MotionPass.h RunPosition.h Vision.h Say.h
BrainNormal.o: BrainNormal.cpp Brain.h ConfFileRead.h \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc /usr/include/ctype.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc Predicate.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 Geometry.h FloatMath.h Object.h BasicConfigure.h EnumType.h Hear.h \
 Encryption.h WorldModel.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 CommandQuene.h Motion.h MotionGoto.h Action.h JointControl.h \
 ActionData.h ActionKickData.h ActionKickNew.h ActionGetUpData.h \
 HumanoidControl.h BasicWalk.h Kinematics.h HumanGoto.h stdafx.h \
 Obstacle.h Dribble.h Kick.h HandleBall.h MotionDribble.h MotionKick.h \
 MotionPass.h RunPosition.h Vision.h Say.h
coach.o: coach.cpp coach.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
Vision.o: Vision.cpp Vision.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
Hear.o: Hear.cpp Hear.h Object.h stdinc.h /usr/include/c++/4.4/cstdlib \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/xlocale.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/time.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/stdio.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/c++/4.4/cmath /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h /usr/include/c++/4.4/bits/cmath.tcc \
 /usr/include/c++/4.4/ctime /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/postypes.h \
 /usr/include/c++/4.4/cwchar /usr/include/bits/wchar.h \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/iosfwd \
 /usr/include/c++/4.4/cctype /usr/include/ctype.h \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/sched.h \
 /usr/include/signal.h /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc /usr/include/string.h \
 /usr/include/c++/4.4/iostream /usr/include/c++/4.4/ostream \
 /usr/include/c++/4.4/ios /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/bits/locale_classes.h \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc BasicConfigure.h EnumType.h \
 Geometry.h FloatMath.h Encryption.h /usr/include/c++/4.4/bitset
Say.o: Say.cpp Say.h WorldModel.h BasicConfigure.h \
 /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h \
 Geometry.h FloatMath.h Object.h EnumType.h Hear.h Encryption.h Matrix.h \
 /usr/include/memory.h Logger.h /usr/include/c++/4.4/deque \
 /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc CommandQuene.h \
 /usr/include/c++/4.4/bitset
AgentInfo.o: AgentInfo.cpp AgentInfo.h Geometry.h FloatMath.h \
 /usr/include/math.h /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h Logger.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc WorldModel.h BasicConfigure.h \
 stdinc.h /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc ConfFileRead.h Predicate.h Object.h \
 EnumType.h Hear.h Encryption.h Matrix.h /usr/include/memory.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc
Agent.o: Agent.cpp Agent.h BasicConfigure.h /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc Logger.h Timer.h \
 /usr/include/c++/4.4/iomanip /usr/include/sys/time.h Connection.h \
 /usr/include/arpa/inet.h /usr/include/netinet/in.h /usr/include/stdint.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h /usr/include/bits/uio.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm-generic/socket.h \
 /usr/include/asm/sockios.h /usr/include/asm-generic/sockios.h \
 /usr/include/bits/in.h CommandQuene.h EnumType.h CommandHandle.h \
 WorldModel.h ConfFileRead.h Predicate.h Geometry.h FloatMath.h Object.h \
 Hear.h Encryption.h Matrix.h /usr/include/memory.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Attitude.h Brain.h Situation.h \
 /usr/include/c++/4.4/algorithm /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 Motion.h MotionGoto.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h HumanGoto.h stdafx.h Obstacle.h Dribble.h \
 Kick.h HandleBall.h MotionDribble.h MotionKick.h MotionPass.h \
 RunPosition.h Vision.h Say.h linuxthread.h /usr/include/fcntl.h \
 /usr/include/bits/fcntl.h /usr/include/sys/stat.h \
 /usr/include/bits/stat.h /usr/include/termios.h \
 /usr/include/bits/termios.h /usr/include/sys/ttydefaults.h \
 /usr/include/bits/signum.h /usr/include/bits/siginfo.h \
 /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h \
 /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h \
 /usr/include/bits/sigthread.h /usr/include/sys/ioctl.h \
 /usr/include/bits/ioctls.h /usr/include/asm/ioctls.h \
 /usr/include/asm-generic/ioctls.h /usr/include/linux/ioctl.h \
 /usr/include/asm/ioctl.h /usr/include/asm-generic/ioctl.h \
 /usr/include/bits/ioctl-types.h /usr/include/sys/timeb.h
main.o: main.cpp /usr/include/c++/4.4/iostream \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++config.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/os_defines.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/cpu_defines.h \
 /usr/include/c++/4.4/ostream /usr/include/c++/4.4/ios \
 /usr/include/c++/4.4/iosfwd /usr/include/c++/4.4/bits/stringfwd.h \
 /usr/include/c++/4.4/bits/postypes.h /usr/include/c++/4.4/cwchar \
 /usr/include/c++/4.4/cstddef \
 /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stddef.h /usr/include/wchar.h \
 /usr/include/stdio.h /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
 /usr/include/bits/wchar.h /usr/include/xlocale.h \
 /usr/include/c++/4.4/exception /usr/include/c++/4.4/bits/char_traits.h \
 /usr/include/c++/4.4/bits/stl_algobase.h \
 /usr/include/c++/4.4/bits/functexcept.h \
 /usr/include/c++/4.4/exception_defines.h \
 /usr/include/c++/4.4/bits/cpp_type_traits.h \
 /usr/include/c++/4.4/ext/type_traits.h \
 /usr/include/c++/4.4/ext/numeric_traits.h \
 /usr/include/c++/4.4/bits/stl_pair.h /usr/include/c++/4.4/bits/move.h \
 /usr/include/c++/4.4/bits/concept_check.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.4/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.4/bits/stl_iterator.h \
 /usr/include/c++/4.4/debug/debug.h /usr/include/c++/4.4/bits/localefwd.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++locale.h \
 /usr/include/c++/4.4/clocale /usr/include/locale.h \
 /usr/include/bits/locale.h /usr/include/c++/4.4/cctype \
 /usr/include/ctype.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/c++/4.4/bits/ios_base.h \
 /usr/include/c++/4.4/ext/atomicity.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/bits/sched.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/setjmp.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/atomic_word.h \
 /usr/include/c++/4.4/bits/locale_classes.h /usr/include/c++/4.4/string \
 /usr/include/c++/4.4/bits/allocator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++allocator.h \
 /usr/include/c++/4.4/ext/new_allocator.h /usr/include/c++/4.4/new \
 /usr/include/c++/4.4/bits/ostream_insert.h \
 /usr/include/c++/4.4/cxxabi-forced.h \
 /usr/include/c++/4.4/bits/stl_function.h \
 /usr/include/c++/4.4/backward/binders.h \
 /usr/include/c++/4.4/bits/basic_string.h \
 /usr/include/c++/4.4/initializer_list \
 /usr/include/c++/4.4/bits/basic_string.tcc \
 /usr/include/c++/4.4/bits/locale_classes.tcc \
 /usr/include/c++/4.4/streambuf /usr/include/c++/4.4/bits/streambuf.tcc \
 /usr/include/c++/4.4/bits/basic_ios.h \
 /usr/include/c++/4.4/bits/locale_facets.h /usr/include/c++/4.4/cwctype \
 /usr/include/wctype.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_base.h \
 /usr/include/c++/4.4/bits/streambuf_iterator.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/ctype_inline.h \
 /usr/include/c++/4.4/bits/locale_facets.tcc \
 /usr/include/c++/4.4/bits/basic_ios.tcc \
 /usr/include/c++/4.4/bits/ostream.tcc /usr/include/c++/4.4/istream \
 /usr/include/c++/4.4/bits/istream.tcc BasicConfigure.h stdinc.h \
 /usr/include/c++/4.4/cstdlib /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/c++/4.4/cstdio /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/stdio_lim.h \
 /usr/include/bits/sys_errlist.h /usr/include/c++/4.4/cmath \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/c++/4.4/bits/cmath.tcc /usr/include/c++/4.4/ctime \
 /usr/include/string.h /usr/include/c++/4.4/fstream \
 /usr/include/c++/4.4/bits/codecvt.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/basic_file.h \
 /usr/include/c++/4.4/i486-linux-gnu/bits/c++io.h \
 /usr/include/c++/4.4/bits/fstream.tcc /usr/include/c++/4.4/sstream \
 /usr/include/c++/4.4/bits/sstream.tcc /usr/include/c++/4.4/list \
 /usr/include/c++/4.4/bits/stl_list.h /usr/include/c++/4.4/bits/list.tcc \
 /usr/include/c++/4.4/map /usr/include/c++/4.4/bits/stl_tree.h \
 /usr/include/c++/4.4/bits/stl_map.h \
 /usr/include/c++/4.4/bits/stl_multimap.h /usr/include/c++/4.4/vector \
 /usr/include/c++/4.4/bits/stl_construct.h \
 /usr/include/c++/4.4/bits/stl_uninitialized.h \
 /usr/include/c++/4.4/bits/stl_vector.h \
 /usr/include/c++/4.4/bits/stl_bvector.h \
 /usr/include/c++/4.4/bits/vector.tcc Connection.h \
 /usr/include/arpa/inet.h /usr/include/netinet/in.h /usr/include/stdint.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h /usr/include/bits/uio.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm-generic/socket.h \
 /usr/include/asm/sockios.h /usr/include/asm-generic/sockios.h \
 /usr/include/bits/in.h Timer.h /usr/include/c++/4.4/iomanip \
 /usr/include/sys/time.h CommandHandle.h EnumType.h CommandQuene.h \
 WorldModel.h ConfFileRead.h Predicate.h Geometry.h FloatMath.h Object.h \
 Hear.h Encryption.h Matrix.h /usr/include/memory.h Logger.h \
 /usr/include/c++/4.4/deque /usr/include/c++/4.4/bits/stl_deque.h \
 /usr/include/c++/4.4/bits/deque.tcc Agent.h Attitude.h Brain.h \
 Situation.h /usr/include/c++/4.4/algorithm \
 /usr/include/c++/4.4/bits/stl_algo.h \
 /usr/include/c++/4.4/bits/algorithmfwd.h \
 /usr/include/c++/4.4/bits/stl_heap.h \
 /usr/include/c++/4.4/bits/stl_tempbuf.h AgentInfo.h Formation.h \
 SitUnitSquare.h SitDribble.h SitKick.h SitPass.h SitRun.h coach.h \
 Motion.h MotionGoto.h Action.h JointControl.h ActionData.h \
 ActionKickData.h ActionKickNew.h ActionGetUpData.h HumanoidControl.h \
 BasicWalk.h Kinematics.h HumanGoto.h stdafx.h Obstacle.h Dribble.h \
 Kick.h HandleBall.h MotionDribble.h MotionKick.h MotionPass.h \
 RunPosition.h Vision.h Say.h linuxthread.h \
 /usr/include/c++/4.4/stdexcept
