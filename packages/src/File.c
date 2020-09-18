#include "File.h"

lval* builtin_fileOpen(lenv* e, lval* a)
{
  LASSERT_NUM("fileOpen", a, 2);
  LASSERT_TYPE("fileOpen", a, 0, LVAL_STR);
  LASSERT_TYPE("fileOpen", a, 1, LVAL_STR);

  return lval_file(a->cell[0]->str, a->cell[1]->str);
}

lval* builtin_fileClose(lenv* e, lval* a)
{
  LASSERT_NUM("fileClose", a, 1);
  LASSERT_TYPE("fileClose", a, 0, LVAL_FILE);

  lval* result;
  
  if (a->cell[0]->file == NULL)
  {
      result = lval_err("FileIO", "Not a file");
  }
  else
  {
      fclose(a->cell[0]->file);
      result = lval_sexpr();
  }
  lval_del(a);
  return result;
}

lval* builtin_readchar(lenv* e, lval* a)
{
  LASSERT_NUM("readchar", a, 1);
  LASSERT_TYPE("readchar", a, 0, LVAL_FILE);

  int characterRead;
  char readString [2];
  lval* result;

  characterRead = fgetc(a->cell[0]->file);

  if (characterRead == EOF)
  {
    result = lval_err("FileIO","EOF");
  }
  else
  {
    readString[0] = (char)characterRead;
    readString[1] = '\0';
    result = lval_str(readString);
  }
  lval_del(a);
  return result;
}

lval* builtin_writechar(lenv* e, lval* a)
{
  LASSERT_NUM("writechar", a, 2);
  LASSERT_TYPE("writechar", a, 0, LVAL_FILE);
  LASSERT_TYPE("writechar", a, 1, LVAL_STR);
	
  lval* result = NULL;

  putc(a->cell[1]->str[0], a->cell[0]->file);
  result = lval_copy(a->cell[0]);
  
  lval_del(a);
  
  return result;
}
