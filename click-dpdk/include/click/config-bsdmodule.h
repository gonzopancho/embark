/* include/click/config-bsdmodule.h.  Generated from config-bsdmodule.h.in by configure.  */
/* Process this file with configure to produce config-bsdmodule.h. -*- mode: c -*- */
#ifndef CLICK_CONFIG_BSDMODULE_H
#define CLICK_CONFIG_BSDMODULE_H

/* Define stuff under a FreeBSD module. */
#ifndef __FreeBSD__
# error "I must be compiled on a FreeBSD machine"
#endif

/* Define if Click should use an adaptive scheduler to share the CPU(s) more
   fairly with the kernel. */
/* #undef HAVE_ADAPTIVE_SCHEDULER */

/* Define if your BSD kernel has polling extensions. */
/* #undef HAVE_BSD_POLLING */

/* Define if your BSD kernel has Click extensions. */
/* #undef HAVE_CLICK_BSD_KERNEL */

/* Define if 'int64_t' is typedefed to 'long' in bsdmodule. */
/* #undef HAVE_INT64_IS_LONG_BSDMODULE */

/* Define if 'int64_t' is typedefed to 'long long' in bsdmodule. */
/* #undef HAVE_INT64_IS_LONG_LONG_BSDMODULE */

/* Define to enable assertion checking. Failed assertions will print a message
   and optionally stop the router. */
/* #undef HAVE_KERNEL_ASSERT */

/* Define if NETISR scheduling should be used. */
#define BSD_NETISRSCHED 1

/* The size of a `click_jiffies_t', as computed by sizeof. */
#define SIZEOF_CLICK_JIFFIES_T SIZEOF_INT

/* Include integer and other type definitions. */
#include <sys/types.h>

/* Define assert macro. */
# ifdef __cplusplus
extern "C" {
# endif
void click_assert_failed(const char *file, int line, const char *problem_text);
# ifdef __cplusplus
}
# endif

#ifdef HAVE_KERNEL_ASSERT
# define assert(x)	((x) ? (void)0 : click_assert_failed(__FILE__, __LINE__, #x))
#else
# define assert(x)	/* nada */
#endif

/* Define likely and unlikely macros. */
#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

/* Define HAVE_INT64_IS_LONG based on HAVE_INT64_IS_LONG_BSDMODULE. */
#ifdef HAVE_INT64_IS_LONG_BSDMODULE
# define HAVE_INT64_IS_LONG HAVE_INT64_IS_LONG_BSDMODULE
#endif

/* Define HAVE_INT64_IS_LONG_LONG based on HAVE_INT64_IS_LONG_LONG_BSDMODULE. */
#if HAVE_LONG_LONG && defined(HAVE_INT64_IS_LONG_LONG_BSDMODULE)
# define HAVE_INT64_IS_LONG_LONG HAVE_INT64_IS_LONG_LONG_BSDMODULE
#endif

#ifdef __cplusplus

/* Declare operator new. */
void *operator new(size_t) throw ();
void *operator new[](size_t) throw ();

/* Provide placement new. */
inline void *operator new(size_t, void *v) throw () { return v; }
#define HAVE_PLACEMENT_NEW 1

/* Define macros that surround Click declarations. */
#define CLICK_DECLS		namespace Click {
#define CLICK_ENDDECLS		}
#define CLICK_USING_DECLS	using namespace Click;
#define CLICK_NAME(name)	::Click::name

#endif /* __cplusplus */

#endif /* CLICK_CONFIG_BSDMODULE_H */
