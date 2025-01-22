#ifndef __MAIN_H__
#define	__MAIN_H__

/*
 *  Copyright 2016 zen.code.ai
 *
 *  This file is part of dlite.
 *
 *  dlite is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dlite is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dlite.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// ............................................................................
// File    : main.h
// Author  : main
// Created : September 21, 2008, 10:56 AM
// 
// Desc    : Common includes and definitions
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Error code bases
    enum
    {
        err_off_store = 0x0010, // Store errors
        err_off_expr  = 0x0020, // Expression errors
        err_off_op    = 0x0030, // Operator errors
        err_off_fact  = 0x0040, // Expr factory errors
        err_off_reasnr= 0x0050, // Reasoner errors
        err_off_node  = 0x0060, // Node errors
        err_off_abox  = 0x0070, // ABox errors
        err_off_expfmt= 0x0080, // Expression format errors
    };

    // ............................................................................
    // Common errors
    enum
    {
        err_dlite_ok = 0,   // No error
        err_dlite_err,      // Error
        err_dlite_os,       // OS error
        err_dlite_mem,      // Memory error
        err_dlite_state,    // Invalid state
        err_dlite_param,    // Invalid parameter
        err_dlite_notfnd,   // Not found
        err_dlite_unsup,    // Unsupported
    };
}

// ............................................................................

#include "shared.h"
#include "sptr.h"
#include "cache.h"
#include "object.h"
#include "expression.h"
#include "store.h"
#include "symtable.h"
#include "log.h"

#endif	//__MAIN_H__
