/*--------------------------------------------------------|
| _________                                               |
| \_   ___ \_______  ____   ____  __ __  ______           |
| /    \  \/\_  __ \/    \ /    \|  |  \/  ___/           |
| \     \____|  | \(  ( ) )   |  \  |  /\___ \            |
|  \______  /|__|   \____/|___|  /____//____  >           |
|         \/                   \/           \/            |
|---------------------------------------------------------|
| Equipe Atual: Cronus Dev Team                           |
| Autores: Hercules & (*)Athena Dev Team                  |
| Licença: GNU GPL                                        |
|----- Descrição: ----------------------------------------|
|                                                         |
|---------------------------------------------------------*/


#ifndef COMMON_NULLPO_H
#define COMMON_NULLPO_H

#include "../common/cbasetypes.h"

// enabled by default on debug builds
#if defined(DEBUG) && !defined(NULLPO_CHECK)
#define NULLPO_CHECK
#endif

// Skip assert checks on release builds
#if !defined(RELEASE) && !defined(ASSERT_CHECK)
#define ASSERT_CHECK
#endif

/** Assert */

#if defined(ASSERT_CHECK)
// extern "C" {
#include <assert.h>
// }
#if !defined(DEFCPP) && defined(WIN32) && !defined(MINGW)
#include <crtdbg.h>
#endif // !DEFCPP && WIN && !MINGW
#define Assert(EX) assert(EX)
#define Assert_chk(EX) ( (EX) ? false : (assert_report(__FILE__, __LINE__, __func__, #EX, "failed assertion"), true) )
#else // ! ASSERT_CHECK
#define Assert(EX) (EX)
#define Assert_chk(EX) ((EX), false)
#endif // ASSERT_CHECK

#if defined(NULLPO_CHECK)
/**
 * Reports NULL pointer information if the passed pointer is NULL
 *
 * @param t pointer to check
 * @return true if the passed pointer is NULL, false otherwise
 */
#define nullpo_chk(t) ( (t) != NULL ? false : (assert_report(__FILE__, __LINE__, __func__, #t, "nullpo info"), true) )
#else // ! NULLPO_CHECK
#define nullpo_chk(t) ((void)(t), false)
#endif // NULLPO_CHECK


/**
 * Returns 0 if a NULL pointer is found.
 *
 * @param t pointer to check
 */
#define nullpo_ret(t) \
	do { if (nullpo_chk(t)) return(0); } while(0)

/**
 * Returns void if a NULL pointer is found.
 *
 * @param t pointer to check
 */
#define nullpo_retv(t) \
	do { if (nullpo_chk(t)) return; } while(0)


/**
 * Returns the given value if a NULL pointer is found.
 *
 * @param ret value to return
 * @param t   pointer to check
 */
#define nullpo_retr(ret, t) \
	do { if (nullpo_chk(t)) return(ret); } while(0)



void assert_report(const char *file, int line, const char *func, const char *targetname, const char *title);

#endif /* COMMON_NULLPO_H */
