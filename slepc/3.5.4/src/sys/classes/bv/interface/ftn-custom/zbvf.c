/*
   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   SLEPc - Scalable Library for Eigenvalue Problem Computations
   Copyright (c) 2002-2014, Universitat Politecnica de Valencia, Spain

   This file is part of SLEPc.

   SLEPc is free software: you can redistribute it and/or modify it under  the
   terms of version 3 of the GNU Lesser General Public License as published by
   the Free Software Foundation.

   SLEPc  is  distributed in the hope that it will be useful, but WITHOUT  ANY
   WARRANTY;  without even the implied warranty of MERCHANTABILITY or  FITNESS
   FOR  A  PARTICULAR PURPOSE. See the GNU Lesser General Public  License  for
   more details.

   You  should have received a copy of the GNU Lesser General  Public  License
   along with SLEPc. If not, see <http://www.gnu.org/licenses/>.
   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/

#include <petsc-private/fortranimpl.h>
#include <slepcbv.h>

#if defined(PETSC_HAVE_FORTRAN_CAPS)
#define bvcreate_                 BVCREATE
#define bvdestroy_                BVDESTROY
#define bvsetoptionsprefix_       BVSETOPTIONSPREFIX
#define bvappendoptionsprefix_    BVAPPENDOPTIONSPREFIX
#define bvgetoptionsprefix_       BVGETOPTIONSPREFIX
#define bvview_                   BVVIEW
#elif !defined(PETSC_HAVE_FORTRAN_UNDERSCORE)
#define bvcreate_                 bvcreate
#define bvdestroy_                bvdestroy
#define bvsetoptionsprefix_       bvsetoptionsprefix
#define bvappendoptionsprefix_    bvappendoptionsprefix
#define bvgetoptionsprefix_       bvgetoptionsprefix
#define bvview_                   bvview
#endif

PETSC_EXTERN void PETSC_STDCALL bvcreate_(MPI_Fint *comm,BV *newbv,PetscErrorCode *ierr)
{
  *ierr = BVCreate(MPI_Comm_f2c(*(comm)),newbv);
}

PETSC_EXTERN void PETSC_STDCALL bvdestroy_(BV *bv,PetscErrorCode *ierr)
{
  *ierr = BVDestroy(bv);
}

PETSC_EXTERN void PETSC_STDCALL bvsetoptionsprefix_(BV *bv,CHAR prefix PETSC_MIXED_LEN(len),PetscErrorCode *ierr PETSC_END_LEN(len))
{
  char *t;

  FIXCHAR(prefix,len,t);
  *ierr = BVSetOptionsPrefix(*bv,t);
  FREECHAR(prefix,t);
}

PETSC_EXTERN void PETSC_STDCALL bvappendoptionsprefix_(BV *bv,CHAR prefix PETSC_MIXED_LEN(len),PetscErrorCode *ierr PETSC_END_LEN(len))
{
  char *t;

  FIXCHAR(prefix,len,t);
  *ierr = BVAppendOptionsPrefix(*bv,t);
  FREECHAR(prefix,t);
}

PETSC_EXTERN void PETSC_STDCALL bvgetoptionsprefix_(BV *bv,CHAR prefix PETSC_MIXED_LEN(len),PetscErrorCode *ierr PETSC_END_LEN(len))
{
  const char *tname;

  *ierr = BVGetOptionsPrefix(*bv,&tname); if (*ierr) return;
  *ierr = PetscStrncpy(prefix,tname,len);
}

PETSC_EXTERN void PETSC_STDCALL bvview_(BV *bv,PetscViewer *viewer,PetscErrorCode *ierr)
{
  PetscViewer v;
  PetscPatchDefaultViewers_Fortran(viewer,v);
  *ierr = BVView(*bv,v);
}

