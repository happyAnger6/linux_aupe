#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([linux_aupe], [1.0], [happyAnger6@163.com])
AC_CONFIG_SRCDIR([src/ipcs/core/test.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(linux_aupe,1.0)

dnl 检测系统类型并把输出变量设置成规范的系统类型，在调用了AC_CANONICAL_SYSTEM之后,下列输出变量包含了系统类型信息。
dnl build,host,target 于是可以在configure 命令行通过 --host=arm_linux 来设置交叉编译
dnl build就是您正在使用的机器,host就是您编译好的程式能够运行的平台,target就是您编译的程式能够处理的平台.
dnl 这个build和host比较好理解,但是target就不好办了,到底什么意思呢?一般来说,我们平时所说的交差编译用不到他target的,比如./configure --build=i386-linux,--host=arm-linux就能够了, 在386的平台上编译能够运行在arm板的程式.
dnl 但是,一般我们都是编译程式,而不是编译工具,假如我们编译工具,比如gcc,这个target就有用了.假如我们需要在一个我们的机器上为arm研发板编译一个能够处理mips程式的gcc,那么target就是mips了 */
dnl
AC_CANONICAL_SYSTEM

# Checks for programs.
dnl 检查系统可用的C编译器，若源代码是用C写的就需要这个宏。
dnl
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS(sys/types.h sys/time.h time.h errno.h fcntl.h limits.h signal.h stdio.h stdlib.h string.h sys/stat.h unistd.h sys/wait.h sys/ipc.h sys/msg.h sys/sem.h sys/shm.h mqueue.h semaphore.h sys/mman.h sys/select.h poll.h stropts.h strings.h sys/ioctl.h sys/filio.h pthread.h door.h rpc/rpc.h sys/sysctl.h)
AC_FUNC_MALLOC
AC_CHECK_FUNCS([sigwait])
AC_CACHE_CHECK(for siginfo_t{}, ac_cv_have_siginfo_t_struct,
	AC_EGREP_HEADER(siginfo_t, signal.h,
		ac_cv_have_siginfo_t_struct=yes,
		ac_cv_have_siginfo_t_struct=no))
if test $ac_cv_have_siginfo_t_struct = yes ; then
	AC_DEFINE([HAVE_SIGINFO_T_STRUCT],1,["siginfo_t struct 1"])
fi
AC_PROG_RANLIB
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_PROG_LIBTOOL
#AC_CONFIG_FILES([src/ipcs/core/Makefile
#                 src/lib/Makefile])
dnl Some system-specific stuff ...
dnl Some operating systems require additional flags in order to get all
dnl the definitions that we're looking for in some system headers.
case "$host_os" in
*aix*)		CFLAGS="$CFLAGS -D_ALL_SOURCE" ;;
*hpux*)		CFLAGS="$CFLAGS -D_HPUX_SOURCE" ;;
*osf*)		CFLAGS="$CFLAGS -D_SOCKADDR_LEN" ;;
*solaris*)	if test "$ac_cv_prog_gcc" = yes; then
		   CFLAGS="$CFLAGS -D__EXTENSIONS__"
		else
		   CFLAGS="$CFLAGS -D__STDC__"
		fi
		AC_DEFINE([POSIX_IPC_PREFIX], "/", [Define it to "/" if you are in posix])
		;;
*linux*)
		AC_DEFINE([POSIX_IPC_PREFIX], "/", [Define it to "/" if you are in posix])
		;;
esac

AC_OUTPUT([Makefile
	src/ipcs/core/Makefile
	src/svipc/Makefile
	src/svmsg/Makefile
	src/pipe/Makefile
	src/pipemsg/Makefile
	src/pxmsg/Makefile
	src/rtsignals/Makefile
        src/lib/Makefile])
