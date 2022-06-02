/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*               This file is part of the program and library                */
/*    PaPILO --- Parallel Presolve for Integer and Linear Optimization       */
/*                                                                           */
/* Copyright (C) 2020-2022 Konrad-Zuse-Zentrum                               */
/*                     fuer Informationstechnik Berlin                       */
/*                                                                           */
/* This program is free software: you can redistribute it and/or modify      */
/* it under the terms of the GNU Lesser General Public License as published  */
/* by the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>.    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _PAPILO_PRESOLVERS_PURE_LIT_HPP_
#define _PAPILO_PRESOLVERS_PURE_LIT_HPP_

#include "papilo/core/PresolveMethod.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemUpdate.hpp"

namespace papilo
{

/// presolver to find pure literal
template <typename REAL>
class PureLit : public PresolveMethod<REAL>
{
 public:
   PureLit() : PresolveMethod<REAL>()
   {
      this->setName( "pureliteral" );
      this->setTiming( PresolverTiming::kFast );
      this->setType( PresolverType::kIntegralCols );
   }

   virtual PresolveStatus
   execute( const Problem<REAL>& problem,
            const ProblemUpdate<REAL>& problemUpdate, const Num<REAL>& num,
            Reductions<REAL>& reductions ) override;

   int
   checkCol( const ConstraintMatrix<REAL>& consMatrix,
             const VariableDomains<REAL>& domains, const Vec<RowFlags>& rflags,
             const Vec<ColFlags>& cflags, const Vec<REAL>& objVec,
             const Vec<REAL>& lbs, const Vec<REAL>& ubs, const Vec<REAL>& lhs,
             const Vec<REAL>& rhs, const int& ncols, const int& nrow,
             const Num<REAL>& num, const int& i );
};

#ifdef PAPILO_USE_EXTERN_TEMPLATES
extern template class PureLit<double>;
extern template class PureLit<Quad>;
extern template class PureLit<Rational>;
#endif

template <typename REAL>
int
PureLit<REAL>::checkCol( const ConstraintMatrix<REAL>& consMatrix,
                         const VariableDomains<REAL>& domains,
                         const Vec<RowFlags>& rflags,
                         const Vec<ColFlags>& cflags, const Vec<REAL>& objVec,
                         const Vec<REAL>& lbs, const Vec<REAL>& ubs,
                         const Vec<REAL>& lhs, const Vec<REAL>& rhs,
                         const int& ncols, const int& nrow,
                         const Num<REAL>& num, const int& i )
{
   if( cflags[i].test( ColFlag::kUnbounded, ColFlag::kInactive,
                       ColFlag::kFixed ) ||
       lbs[i] == ubs[i] )
   {
      return -1;
   }
   assert( domains.isBinary( i ) );
   assert( consMatrix.getColSizes()[i] >= 0 );

   auto colvec = consMatrix.getColumnCoefficients( i );
   const REAL* colVals = colvec.getValues();
   const int* indices = colvec.getIndices();
   const auto len = colvec.getLength();

   //* requires: 1: same sign for every coefficient;
   //* 2: same operator every constraint it appears
   //* 3: fix to 1 should have <= 0 obj, fix to 0 should have >= 0 obj
   int st = -1;
   for( int r = 0; r < len; r++ )
   {
      if( rflags[indices[r]].test( RowFlag::kEquation ) ||
          ( !rflags[indices[r]].test( RowFlag::kRhsInf ) &&
            !rflags[indices[r]].test( RowFlag::kLhsInf ) ) )
      { // block by equation and a<=x<=b
         st = -1;
         break;
      }
      else if( !rflags[indices[r]].test( RowFlag::kRedundant ) )
      {
         st = r;
         break;
      }
   }
   if( st == -1 )
   {
      return -1;
   }
   const bool op = rflags[indices[st]].test( RowFlag::kRhsInf ); // true => 0<=x
   const bool sign = num.isFeasGT( colVals[st], 0 );             // true => >0

   // auto rowvec = consMatrix.getRowCoefficients( indices[st] );
   // const REAL* rowVals = rowvec.getValues();
   // for( int i = 0; i < rowvec.getLength(); i++ )
   // {
   //    msg.info( " {}", rowVals[i] );
   // }
   // msg.info( " op: {}, sign {} for {}\n", op, sign, i );
   // msg.info( " lhs: {}, rhs: {}\n", lhs[indices[st]], rhs[indices[st]] );

   assert( !rflags[indices[st]].test( RowFlag::kRedundant ) );
   assert( !rflags[indices[st]].test( RowFlag::kEquation ) );
   assert( !rflags[indices[st]].test( RowFlag::kIntegral ) );
   assert( op == false ? rflags[indices[st]].test( RowFlag::kLhsInf )
                       : rflags[indices[st]].test( RowFlag::kRhsInf ) );
   assert( !num.isFeasEq( colVals[st], 0 ) );

   bool ok = true;
   bool rop, rsign;
   for( int r = st + 1; r < len; r++ )
   {
      if( rflags[indices[r]].test( RowFlag::kRedundant ) )
      {
         continue;
      }
      else if( rflags[indices[r]].test( RowFlag::kEquation ) ||
               ( !rflags[indices[r]].test( RowFlag::kLhsInf ) &&
                 !rflags[indices[r]].test( RowFlag::kRhsInf ) ) )
      { // block equation and a<=x<=b
         ok = false;
         break;
      }

      rop = ( rflags[indices[r]].test( RowFlag::kRhsInf ) == op );
      rsign = ( num.isFeasGT( colVals[r], 0 ) == sign );

      if( rop ^ rsign )
      {
         assert( ( ( rflags[indices[r]].test( RowFlag::kRhsInf ) != op ) &&
                   num.isFeasGT( colVals[r], 0 ) == sign ) ||
                 ( ( rflags[indices[r]].test( RowFlag::kRhsInf ) == op ) &&
                   num.isFeasGT( colVals[r], 0 ) != sign ) );
         ok = false;
         break;
      }
      else
      {
         assert( ( ( rflags[indices[r]].test( RowFlag::kRhsInf ) != op ) &&
                   num.isFeasGT( colVals[r], 0 ) != sign ) ||
                 ( ( rflags[indices[r]].test( RowFlag::kRhsInf ) == op ) &&
                   num.isFeasGT( colVals[r], 0 ) == sign ) );

         continue;
      }
   }
   if( ok == true )
   {
      if( ( op && sign ) || ( !op && !sign ) ) //* 0<=x or -x<=0 => x=1
      {
         if( num.isFeasLE( objVec[i], 0 ) ) //* obj coeff of i should <=0
         {
            assert( ubs[i] == 1 );
            // msg.info( "fix {} to {}\n", i, ubs[i] );
            return 1;
         }
      }
      else if( ( !op && sign ) || ( op && !sign ) ) //* x<=0 or 0<=-x => x=0
      {
         if( num.isFeasGE( objVec[i], 0 ) )
         {
            assert( lbs[i] == 0 );
            // msg.info( "fix {}  to {}\n", i, lbs[i] );
            return 0;
         }
      }
   }
   else
   {
      return -1;
   }

   return -1;
}

template <typename REAL>
PresolveStatus
PureLit<REAL>::execute( const Problem<REAL>& problem,
                        const ProblemUpdate<REAL>& problemUpdate,
                        const Num<REAL>& num, Reductions<REAL>& reductions )
{
   assert( problem.getNumIntegralCols() != 0 );

   const auto& consMatrix = problem.getConstraintMatrix();
   const auto& domains = problem.getVariableDomains();
   const auto& rflags = consMatrix.getRowFlags();
   const auto& cflags = domains.flags;
   const auto& objective = problem.getObjective();
   const auto& objVec = objective.coefficients;
   const auto& lbs = problem.getLowerBounds();
   const auto& ubs = problem.getUpperBounds();
   const papilo::Vec<REAL>& lhs = consMatrix.getLeftHandSides();
   const papilo::Vec<REAL>& rhs = consMatrix.getRightHandSides();
   const int ncols = consMatrix.getNCols();
   const int nrow = consMatrix.getNRows();

   PresolveStatus result = PresolveStatus::kUnchanged;

   Message msg;
   // msg.info( "start purelit/n" );

   if( problemUpdate.getPresolveOptions().runs_sequentiell() ||
       !problemUpdate.getPresolveOptions().pureliteral_parallel )
   {
      for( int i = 0; i < ncols; ++i )
      {
         int state = checkCol( consMatrix, domains, rflags, cflags, objVec, lbs,
                               ubs, lhs, rhs, ncols, nrow, num, i );
         if( state == -1 )
         {
            continue;
         }
         else if( state == 0 ) //* fix to lb
         {
            TransactionGuard<REAL> tg{ reductions };
            reductions.lockColBounds( i );
            reductions.fixCol( i, lbs[i] );
            result = PresolveStatus::kReduced;
         }
         else if( state == 1 ) //* fix to ub
         {
            TransactionGuard<REAL> tg{ reductions };
            reductions.lockColBounds( i );
            reductions.fixCol( i, ubs[i] );
            result = PresolveStatus::kReduced;
         }
      }
   }
   else
   {
      Vec<int> states( ncols, -2 );
      tbb::parallel_for( tbb::blocked_range<int>( 0, ncols ),
                         [&]( tbb::blocked_range<int> r )
                         {
                            for( int i = r.begin(); i < r.end(); ++i )
                            {
                               states[i] = checkCol(
                                   consMatrix, domains, rflags, cflags, objVec,
                                   lbs, ubs, lhs, rhs, ncols, nrow, num, i );
                            }
                         } );
      assert( std::all_of( states.begin(), states.end(),
                           []( int i ) { return i != -2; } ) );
      for( int i = 0; i < ncols; i++ )
      {
         if( states[i] == -1 )
         {
            continue;
         }
         else if( states[i] == 0 ) //* fix to lb
         {
            TransactionGuard<REAL> tg{ reductions };
            reductions.lockColBounds( i );
            reductions.fixCol( i, lbs[i] );
            result = PresolveStatus::kReduced;
         }
         else if( states[i] == 1 ) //* fix to ub
         {
            TransactionGuard<REAL> tg{ reductions };
            reductions.lockColBounds( i );
            reductions.fixCol( i, ubs[i] );
            result = PresolveStatus::kReduced;
         }
      }
   }

   // msg.info( "finish pure literal\n" );
   // msg.info( "\n\n" );
   return result;
}

} // namespace papilo

#endif
