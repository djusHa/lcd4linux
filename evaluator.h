/* $Id: evaluator.h,v 1.5 2004/03/06 20:31:16 reinelt Exp $
 *
 * expression evaluation
 *
 * Copyright 1999, 2000 Michael Reinelt <reinelt@eunet.at>
 * Copyright 2004 The LCD4Linux Team <lcd4linux-devel@users.sourceforge.net>
 *
 * This file is part of LCD4Linux.
 *
 * LCD4Linux is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * LCD4Linux is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 * $Log: evaluator.h,v $
 * Revision 1.5  2004/03/06 20:31:16  reinelt
 * Complete rewrite of the evaluator to get rid of the code
 * from mark Morley (because of license issues).
 * The new Evaluator does a pre-compile of expressions, and
 * stores them in trees. Therefore it should be reasonable faster...
 *
 * Revision 1.4  2004/03/03 03:47:04  reinelt
 * big patch from Martin Hejl:
 * - use qprintf() where appropriate
 * - save CPU cycles on gettimeofday()
 * - add quit() functions to free allocated memory
 * - fixed lots of memory leaks
 *
 * Revision 1.3  2004/01/12 03:51:01  reinelt
 * evaluating the 'Variables' section in the config file
 *
 * Revision 1.2  2003/10/11 06:01:53  reinelt
 *
 * renamed expression.{c,h} to client.{c,h}
 * added config file client
 * new functions 'AddNumericVariable()' and 'AddStringVariable()'
 * new parameter '-i' for interactive mode
 *
 * Revision 1.1  2003/10/06 04:34:06  reinelt
 * expression evaluator added
 *
 */


#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_


// RESULT bitmask
#define R_NUMBER 1
#define R_STRING 2

typedef struct {
  int type;
  double number;
  char  *string;
} RESULT;


int  SetVariable        (char *name, RESULT *value);
int  SetVariableNumeric (char *name, double  value);
int  SetVariableString  (char *name, char   *value);

int  AddFunction        (char *name, int argc, void (*func)());

void DeleteVariables    (void);
void DeleteFunctions    (void);

void    DelResult (RESULT *result);
RESULT* SetResult (RESULT **result, int type, void *value);

double R2N (RESULT *result);
char*  R2S (RESULT *result);

int  Compile (char *expression, void **tree);
int  Eval    (void *tree, RESULT *result);
void DelTree (void *tree);

#endif
