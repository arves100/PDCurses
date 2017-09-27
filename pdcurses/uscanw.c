/* Public Domain Curses */
/* Unicode modification by Arves100 released under Public Domain License */

#include <curspriv.h>
#include <curses.h>

/*man-start**************************************************************

scanw
-----

### Synopsis

int uscanw(const wchar_t *fmt, ...);
int wuscanw(WINDOW *win, const wchar_t *fmt, ...);
int mvuscanw(int y, int x, const wchar_t *fmt, ...);
int mvwuscanw(WINDOW *win, int y, int x, const wchar_t *fmt, ...);
int vwuscanw(WINDOW *win, const wchar_t *fmt, va_list varglist);
int vw_uscanw(WINDOW *win, const wchar_t *fmt, va_list varglist);

### Description

Same as scanw but in uncode format

### Return Value

On successful completion, these functions return the number of
items successfully matched.  Otherwise they return ERR.

**man-end****************************************************************/

#include <string.h>
#define MAXLINE 255
#define PDC_LOGX(x) PDC_debug x

int wugetnstr(WINDOW *win, wchar_t *str, int n)
{
	wchar_t wstr[MAXLINE + 1];

	if (n < 0 || n > MAXLINE)
		n = MAXLINE;

	if (wgetn_wstr(win, (wint_t *)wstr, n) == ERR)
		return ERR;

//	return PDC_wcstombs(str, wstr, n);
	return 0;
}

int vwuscanw(WINDOW *win, const wchar_t *fmt, va_list varglist)
{
	wchar_t scanbuf[256];

	PDC_LOGX(("vwuscanw() - called\n"));

	if (wugetnstr(win, scanbuf, 255) == ERR)
		return ERR;

	return vswscanf(scanbuf, fmt, varglist);
}

int uscanw(const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("uscanw() - called\n"));

	va_start(args, fmt);
	retval = vwuscanw(stdscr, fmt, args);
	va_end(args);

	return retval;
}

int wuscanw(WINDOW *win, const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("wsucanw() - called\n"));

	va_start(args, fmt);
	retval = vwuscanw(win, fmt, args);
	va_end(args);

	return retval;
}

int mvuscanw(int y, int x, const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("mvuscanw() - called\n"));

	if (move(y, x) == ERR)
		return ERR;

	va_start(args, fmt);
	retval = vwuscanw(stdscr, fmt, args);
	va_end(args);

	return retval;
}

int mvwuscanw(WINDOW *win, int y, int x, const wchar_t *fmt, ...)
{
	va_list args;
	int retval;

	PDC_LOGX(("mvscanw() - called\n"));

	if (wmove(win, y, x) == ERR)
		return ERR;

	va_start(args, fmt);
	retval = vwuscanw(win, fmt, args);
	va_end(args);

	return retval;
}

int vw_uscanw(WINDOW *win, const wchar_t *fmt, va_list varglist)
{
	PDC_LOGX(("vw_uscanw() - called\n"));

	return vwuscanw(win, fmt, varglist);
}