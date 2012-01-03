#include "/ozgan/programs/h/genel.h"

void cursor_off(void)
{
	union REGS r;

	r.x.ax = 2;
	int86(0x33, &r, &r);
}

void cursor_on(void)
{
	union REGS r;

	r.x.ax = 1;
	int86(0x33, &r, &r);
}

int rightb_pressed(void)
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	return r.x.bx & 2;
}

int leftb_pressed(void)
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	return r.x.bx & 1;
}

void set_mouse_position(int x, int y)
{
	union REGS r;

	r.x.ax = 4;
	r.x.cx = x;
	r.x.dx = y;
	int86(0x33, &r, &r);
}

void mouse_position(int *x, int *y)
{
	union REGS r;

	r.x.ax = 3;
	int86(0x33, &r, &r);
	*x = r.x.cx;
	*y = r.x.dx;
}

void mouse_motion(char *deltax, char *deltay)
{
	union REGS r;

	r.x.ax = 11;
	int86(0x33, &r, &r);

	if (r.x.cx > 0)
		*deltax = M_RIGHT;
	else
		if (r.x.cx < 0)
			*deltax = M_LEFT;
		else
			*deltay = NOT_MOVED;

	if (r.x.dx < 0)
		*deltay = M_DOWN;
	else
		if (r.x.dx < 0)
			*deltay = M_UP;
		else
			*deltay = NOT_MOVED;
}

void wait_on(int button)
{
	if (button == LEFTB)
		while(leftb_pressed())
			;
	else
		while(rightb_pressed())
			;
}

void mouse_reset(void)
{
	union REGS r;

	r.x.ax = 0;
	int86(0x33, &r, &r);
	if ((int) r.x.ax != -1) {
		printf("mouse hardware or software not installed\n");
		exit(1);
	}
}

int kontrol(KONUM *konum, int uzunluk, int satir, int kolon)
{
	int i;

	for (i = 0; i < uzunluk; i++) {
		if (konum[i].baslangic_satiri <= satir &&
			konum[i].son_satiri >= satir &&
			konum[i].baslangic_kolonu <= kolon &&
			konum[i].son_kolonu >= kolon)
			return i;
	}
	return EMPTY;
}
