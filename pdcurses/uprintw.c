/* Public Domain Curses */
/* Unicode modification by Arves100 released under Public Domain License */

#include <curspriv.h>

/*man-start**************************************************************

uprintw
------

### Synopsis

int uprintw(const wchar_t *fmt, ...);
int wuprintw(WINDOW *win, const wchar_t *fmt, ...);
int mvuprintw(int y, int x, const wchar_t *fmt, ...);
int mvwuprintw(WINDOW *win, int y, int x, const wchar_t *fmt,...);
int vwuprintw(WINDOW *win, const wchar_t *fmt, va_list varglist);
int vw_uprintw(WINDOW *win, const wchar_t *fmt, va_list varglist);

### Description

The uprintw() have the same functonalty as printw but it works for Unicode characters


### Return Value

All functions return the number of characters printed, or
ERR on error.

**man-end****************************************************************/

#include <string.h>

#define PDC_LOGX(x) PDC_debug x

int vwuprintw(WINDOW *win, const wchar_t *fmt, va_list varglist)
{
	wchar_t printbuf[513];
	int len;

	PDC_LOGX(("vwuprintw() - called\n"));

#ifdef HAVE_VSNPRINTF
	len = _vsnwprintf(printbuf, 512, fmt, varglist);
#else
	len = vswprintf(printbuf, 512, fmt, varglist);
#endif
	return (wuaddstr(win, printbuf) == ERR) ? ERR : len;
}

int uprintw(const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("uprintw() - called\n"));

	va_start(args, fmt);
	retval = vwuprintw(stdscr, fmt, args);
	va_end(args);

	return retval;
}

int wuprintw(WINDOW *win, const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("wuprintw() - called\n"));

	va_start(args, fmt);
	retval = vwuprintw(win, fmt, args);
	va_end(args);

	return retval;
}

int mvuprintw(int y, int x, const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("mvuprintw() - called\n"));

	if (move(y, x) == ERR)
		return ERR;

	va_start(args, fmt);
	retval = vwuprintw(stdscr, fmt, args);
	va_end(args);

	return retval;
}

int mvwuprintw(WINDOW *win, int y, int x, const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("mvwuprintw() - called\n"));

	if (wmove(win, y, x) == ERR)
		return ERR;

	va_start(args, fmt);
	retval = vwuprintw(win, fmt, args);
	va_end(args);

	return retval;
}

int vw_uprintw(WINDOW *win, const wchar_t *fmt, va_list varglist)
{
	PDC_LOGX(("vw_uprintw() - called\n"));

	return vwuprintw(win, fmt, varglist);
}