/*
 * FindControlRow.c
 * Created on: 2024Δκ10ΤΒ11ΘΥ
 * Author: Αυγε
 */

#include "zf_common_headfile.h"

int RowSet	   = 50;
int ControlRow = 50;

void FindControlRow(void)
{
	if (ControlRow < EndRow)
		ControlRow = EndRow + 1;
	else
		ControlRow = RowSet;
}
