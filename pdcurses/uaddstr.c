/* Public Domain Curses */
/* Unicode modification by Arves100 released under Public Domain License */
#include <curspriv.h>

/*man-start**************************************************************

addstr
------

### Synopsis

int uaddstr(const wchar_t *str);
int uaddnstr(const wchar_t *str, int n);
int wuaddstr(WINDOW *win, const wchar_t *str);
int wuaddnstr(WINDOW *win, const wchar_t *str, int n);
int mvuaddstr(int y, int x, const wchar_t *str);
int mvuaddnstr(int y, int x, const wchar_t *str, int n);
int mvuwaddstr(WINDOW *win, int y, int x, const wchar_t *str);
int mvuwaddnstr(WINDOW *win, int y, int x, const wchar_t *str, int n);

int uaddwstr(const wchar_t *wstr);
int uaddnwstr(const wchar_t *wstr, int n);
int wuaddwstr(WINDOW *win, const wchar_t *wstr);
int wuaddnwstr(WINDOW *win, const wchar_t *wstr, int n);
int mvuaddwstr(int y, int x, const wchar_t *wstr);
int mvuaddnwstr(int y, int x, const wchar_t *wstr, int n);
int mvwuaddwstr(WINDOW *win, int y, int x, const wchar_t *wstr);
int mvwuaddnwstr(WINDOW *win, int y, int x, const wchar_t *wstr, int n);

### Description

Same works as addstr.c but in unicode

### Return Value

All functions return OK or ERR.

**man-end****************************************************************/

#include <cstdlib>
#define PDC_LOGX(x) PDC_debug x

int wuaddnstr(WINDOW *win, const wchar_t *str, int n)
{
	int i = 0;

	PDC_LOGX(("wuaddnstr() - called: string=\"%S\" n %d \n", str, n));

	if (!win || !str)
		return ERR;

	while (str[i] && (i < n || n < 0))
	{
		chtype wch = str[i++];

		if (waddch(win, wch) == ERR)
			return ERR;
	}

	return OK;
}

int uaddstr(const wchar_t *str)
{
	PDC_LOGX(("addstr() - called: string=\"%S\"\n", str));

	return wuaddnstr(stdscr, str, -1);
}

int uaddnstr(const wchar_t *str, int n)
{
	PDC_LOGX(("uaddnstr() - called: string=\"%S\" n %d \n", str, n));

	return wuaddnstr(stdscr, str, n);
}

int wuaddstr(WINDOW *win, const wchar_t *str)
{
	PDC_LOGX(("wuaddstr() - called: string=\"%S\"\n", str));

	return wuaddnstr(win, str, -1);
}

int mvuaddstr(int y, int x, const wchar_t *str)
{
	PDC_LOGX(("mvuaddstr() - called: y %d x %d string=\"%S\"\n", y, x, str));

	if (move(y, x) == ERR)
		return ERR;

	return wuaddnstr(stdscr, str, -1);
}

int mvuaddnstr(int y, int x, const wchar_t *str, int n)
{
	PDC_LOGX(("mvaddnstr() - called: y %d x %d string=\"%S\" n %d \n",
		y, x, str, n));

	if (move(y, x) == ERR)
		return ERR;

	return wuaddnstr(stdscr, str, n);
}

int mvwuaddstr(WINDOW *win, int y, int x, const wchar_t *str)
{
	PDC_LOGX(("mvwuaddstr() - called: string=\"%S\"\n", str));

	if (wmove(win, y, x) == ERR)
		return ERR;

	return wuaddnstr(win, str, -1);
}

int mvwuaddnstr(WINDOW *win, int y, int x, const wchar_t *str, int n)
{
	PDC_LOGX(("mvwuaddnstr() - called: y %d x %d string=\"%S\" n %d \n",
		y, x, str, n));

	if (wmove(win, y, x) == ERR)
		return ERR;

	return wuaddnstr(win, str, n);
}

#ifdef PDC_WIDE
int wuaddnwstr(WINDOW *win, const wchar_t *wstr, int n)
{
	int i = 0;

	PDC_LOGX(("wuaddnwstr() - called\n"));

	if (!win || !wstr)
		return ERR;

	while (wstr[i] && (i < n || n < 0))
	{
		chtype wch = wstr[i++];

		if (waddch(win, wch) == ERR)
			return ERR;
	}

	return OK;
}

int uaddwstr(const wchar_t *wstr)
{
	PDC_LOGX(("uaddwstr() - called\n"));

	return wuaddnwstr(stdscr, wstr, -1);
}

int uaddnwstr(const wchar_t *wstr, int n)
{
	PDC_LOGX(("uaddnwstr() - called\n"));

	return wuaddnwstr(stdscr, wstr, n);
}

int wuaddwstr(WINDOW *win, const wchar_t *wstr)
{
	PDC_LOGX(("wuaddwstr() - called\n"));

	return wuaddnwstr(win, wstr, -1);
}

int mvuaddwstr(int y, int x, const wchar_t *wstr)
{
	PDC_LOGX(("mvuaddstr() - called\n"));

	if (move(y, x) == ERR)
		return ERR;

	return wuaddnwstr(stdscr, wstr, -1);
}

int mvuaddnwstr(int y, int x, const wchar_t *wstr, int n)
{
	PDC_LOGX(("mvuaddnstr() - called\n"));

	if (move(y, x) == ERR)
		return ERR;

	return wuaddnwstr(stdscr, wstr, n);
}

int mvwuaddwstr(WINDOW *win, int y, int x, const wchar_t *wstr)
{
	PDC_LOGX(("mvwuaddstr() - called\n"));

	if (wmove(win, y, x) == ERR)
		return ERR;

	return wuaddnwstr(win, wstr, -1);
}

int mvwuaddnwstr(WINDOW *win, int y, int x, const wchar_t *wstr, int n)
{
	PDC_LOGX(("mvwuaddnstr() - called\n"));

	if (wmove(win, y, x) == ERR)
		return ERR;

	return wuaddnwstr(win, wstr, n);
}
#endif
