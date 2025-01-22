#ifndef __EXPRESSION_H__
#define	__EXPRESSION_H__

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
// File    : expression.h
// Author  : main
// Created : September 21, 2008, 9:10 AM
// 
// Desc    : Expression class and definictions
//
// ............................................................................


/*!\file expression.h
 * \brief Expression classes and related types and constants
 */
 
/*!\typedef dword DLITE::operator_t
 * \brief Expression operator identifier
 */

namespace DLITE
{
    // ............................................................................
    // Definitions
    typedef dword operator_t;

    // Operators
    #define OP_INVALID     ((dword) 0x00) // Invalid
    #define OP_ONTOLOGY    ((dword) 0x01) // Ontology
    #define OP_NAMESPACE   ((dword) 0x02) // Namespace
    #define OP_DEFINITION  ((dword) 0x03) // Concept definition
    #define OP_GCI         ((dword) 0x04) // Global concept inclusion
    #define OP_INDIVIDUAL  ((dword) 0x05) // Individual
    #define OP_CONCEPT     ((dword) 0x06) // Concept
    #define OP_CONCEPTNEG  ((dword) 0x07) // Concept neg
    #define OP_ROLE        ((dword) 0x08) // Role
    #define OP_ROLENEG     ((dword) 0x09) // Role neg
    #define OP_TOP         ((dword) 0x0A) // Top
    #define OP_BOTTOM      ((dword) 0x0B) // Bottom
    #define OP_UNIV        ((dword) 0x0C) // Universal
    #define OP_EXIST       ((dword) 0x0D) // Exitential
    #define OP_UNION       ((dword) 0x0E) // Or
    #define OP_INTER       ((dword) 0x0F) // And
    #define OP_MAX         ((dword) 0x10) // Max type val

    // Operator type and mask
    struct tOperatorDef
    {
        dword type;    // Type ID
        dword mask;    // Negation mask
    };

    // Operator definition table
    extern tOperatorDef g_asOp[];

    // Operator handling
    #define OP_DEF(TYPE, MASK) { TYPE << 24, MASK << 24 }
    #define OP_TYPE_MASK    ((dword) 0xFF000000)
    #define OP_IDNT_MASK    ((dword) 0x00FFFFFF)
    #define OP_TYPE(OP)     ((OP) >> 24)
    #define OP_IDNT(OP)     ((OP) & OP_IDNT_MASK)
    #define OP_VALID(OP)    (((OP) & OP_TYPE_MASK) && ((OP) < (OP_MAX << 24))
    #define OP_NEG(OP)      ((OP) ^ g_asOp[OP_TYPE(OP)].mask)
    #define OP_ABS(OP)      ((OP) & ~(g_asOp[OP_TYPE(OP)].mask))
    #define OP_ABS_TYPE(OP) (OP_TYPE(OP_ABS(OP)))
    #define OP_MAKE(TYPE, IDNT) (((TYPE) << 24) + (IDNT))

    #define OP_CMPL_MASK    ((dword) 0x01000000)
    #define OP_CMPL_NEG(OP) ((OP) ^ OP_CMPL_MASK)
    #define OP_CMPL_ABS(OP) ((OP) & (~OP_CMPL_MASK))
    #define OP_CMPL_FLG(OP) ((OP) & (OP_CMPL_MASK))

    #define OP_HDR_SZ (2)

    // Root namespace
    #define OP_ROOT_NS  (OP_MAKE(OP_NAMESPACE, 0))

    // ............................................................................
    // Expression class
    class tOperator
    {
    public:

        // Errors
        enum
        {
            err_op_size = err_off_op,   // Arg size error
        };

    private:

        bool    m_fNeg;         // Complement flag
        dword   m_dwSize;       // Operator size
        pdword  m_pdwOp;        // Operator pointer
        dword   m_nOffset;      // Offset in arg list

    protected:

        // Expression size
        inline static dword sizeOf(const pdword i_pdwOp) { return *(i_pdwOp + 1) + OP_HDR_SZ; }

    public:

        // c'tor
        tOperator()
            : m_fNeg(false), m_dwSize(0), m_pdwOp(NULL), m_nOffset(0) {}
        tOperator(const pdword i_pdwOp, const bool i_fNeg = false)
            : m_fNeg(i_fNeg), m_dwSize(sizeOf(i_pdwOp)), m_pdwOp(i_pdwOp), m_nOffset(OP_HDR_SZ) {}
        tOperator(const tOperator& i_oSrc)
            : m_fNeg(i_oSrc.m_fNeg), m_dwSize(i_oSrc.m_dwSize), m_pdwOp(i_oSrc.m_pdwOp), m_nOffset(OP_HDR_SZ) {}

        // Null operator?
        inline bool null() const { return (m_pdwOp == NULL); }

        // Operator
        operator_t op() const { return m_fNeg ? OP_NEG(*m_pdwOp) : *m_pdwOp; }

        // Operator size
        inline dword size() const { return m_dwSize; }

        // Operator type
        inline dword type() const { return OP_TYPE(op()); }

        // Complement operator
        void neg() { *m_pdwOp = OP_NEG(*m_pdwOp); }

        // Set to begining of operators list
        void begin()
        {
            m_nOffset = OP_HDR_SZ;
        }

        // End of arg list?
        inline bool end() const { return m_nOffset >= m_dwSize; }

        // Last item of arg list?
        bool last() const
        {
            if (end()) return true;

            return (m_nOffset + sizeOf(m_pdwOp + m_nOffset)) >= m_dwSize;
        }

        // Current operator
        inline tOperator cur() const
        {
            return end() ? tOperator() : tOperator(m_pdwOp + m_nOffset);
        }

        // Next operator
        tOperator next()
        {
            tOperator op = cur();
            m_nOffset += op.size();

            return op;
        }
    };

    // ............................................................................
    // Expression class

    class tExpression;
    typedef _s_ptr<tExpression> sptExpression;

    class tExpression
    {
    public:

        // Errors
        enum
        {
            err_expr_size = err_off_expr,   // Blob size error
        };

    private:

        _buffer<operator_t> m_oExpr; // Expression data

    protected:

        // Reset object
        void reset()
        {

        }

        // Assign blob
        tExpression& assign(const _buffer<byte>& i_oBlob)
        {
            size_t nSrcSz = i_oBlob.size();
            _check(!(nSrcSz % 4), err_expr_size);

            size_t nDesSz = nSrcSz / sizeof(dword);

            m_oExpr.set(nDesSz);

            pbyte  pSrc = i_oBlob.ptr();
            pdword pDes = m_oExpr.ptr();

            for(size_t i = 0; i < nDesSz; i ++)
            {
                dword nCur = *(pSrc ++);
                nCur = (nCur << 8) | *(pSrc ++);
                nCur = (nCur << 8) | *(pSrc ++);
                nCur = (nCur << 8) | *(pSrc ++);
                *(pDes ++) = nCur;
            }

            return *this;
        }

    public:

        // Clear object
        void clear()
        {
            reset();
        }

        // c'tor
        tExpression(const _buffer<byte>& i_oBlob) { reset(); assign(i_oBlob); }

        // c'tor
        tExpression(const _buffer<operator_t>& i_oExpr) { reset(); m_oExpr = i_oExpr; }

        // d'tor
        virtual ~tExpression() { clear(); }

        // Return buffer
        const _buffer<operator_t>& buffer() const { return m_oExpr; }

        // Root operator
        tOperator root(const bool i_fNeg = false) const
        {
            if (m_oExpr.null())
            {
                return tOperator();
            }
            else
            {
                _check(m_oExpr.size() >= OP_HDR_SZ, err_expr_size);
                tOperator op(m_oExpr.ptr(), i_fNeg);
                _check(m_oExpr.size() == op.size(), err_expr_size);

                return op;
            }
        }

        // Serialize
        _buffer<byte> serialize() const
        {
            _buffer<byte> oBuf;
            if (!m_oExpr.null())
            {
                size_t nSize = m_oExpr.size() * sizeof(operator_t);
                oBuf.set(nSize);
                pdword p = m_oExpr.end();
                pbyte  q = oBuf.end();

                dword cur = 0;
                for(size_t i = 0; i < nSize; i ++)
                {
                    if (!(i % sizeof(operator_t))) cur = *(-- p);
                    *(-- q) = (byte) (cur & 0xFF);
                    cur >>= 8;
                }
            }

            return oBuf;
        }

        // Dependency list
        void depend(set<operator_t>& o_oDep)
        {
            o_oDep.clear();
            if (!m_oExpr.null())
            {
                size_t nSize = m_oExpr.size();
                pdword p = m_oExpr.ptr();
                for(size_t i = 0; i < nSize; i ++, p ++)
                {
                    operator_t op = OP_ABS(*p);
                    if (OP_TYPE(op) == OP_CONCEPT) o_oDep.insert(op);
                }
            }
        }

        // Factory method
        static sptExpression Create(const _buffer<byte>& i_oBlob)
        {
            return sptExpression(new tExpression(i_oBlob));
        }

        // Factory method
        static sptExpression Create(const _buffer<operator_t>& i_oExpr)
        {
            return sptExpression(new tExpression(i_oExpr));
        }
    };
}

#endif	//__EXPRESSION_H__
