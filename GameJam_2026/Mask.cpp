#include "Mask.h"

Mask::Mask(float x)
{
	wh = x;

}
void Mask::drawMask(int x, int y)
{
	DrawRectangle(x, y, wh, wh, GREEN);
}