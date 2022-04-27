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

/// presolver to fix continuous variables whose bounds are very close
template <typename REAL>
class PureLit : public PresolveMethod<REAL>
{
 public:
   PureLit() : PresolveMethod<REAL>()
   {
      this->setName( "pureliteral" );
      this->setTiming( PresolverTiming::kMedium );
      this->setType( PresolverType::kIntegralCols );
   }

   virtual PresolveStatus
   execute( const Problem<REAL>& problem,
            const ProblemUpdate<REAL>& problemUpdate, const Num<REAL>& num,
            Reductions<REAL>& reductions ) override;
};

#ifdef PAPILO_USE_EXTERN_TEMPLATES
extern template class PureLit<double>;
extern template class PureLit<Quad>;
extern template class PureLit<Rational>;
#endif

template <typename REAL>
PresolveStatus
PureLit<REAL>::execute( const Problem<REAL>& problem,
                        const ProblemUpdate<REAL>& problemUpdate,
                        const Num<REAL>& num, Reductions<REAL>& reductions )
{
   assert( problem.getNumIntegralCols() != 0 );

   const auto& consMatrix = problem.getConstraintMatrix();
   const auto& domains = problem.getVariableDomains();
   const auto& cflags = domains.flags;
   const auto& objective = problem.getObjective();
   const auto& lbs = problem.getLowerBounds();
   const auto& ubs = problem.getUpperBounds();
   const int ncols = consMatrix.getNCols();

   Message msg;

   PresolveStatus result = PresolveStatus::kUnchanged;
   if( num.getFeasTol() == REAL{ 0 } )
      return result;

   for( int i = 0; i < ncols; ++i )
   {
      if( cflags[i].test( ColFlag::kUnbounded, ColFlag::kInactive ) )
         continue;

      assert( domains.isBinary( i ) );
      assert( lbs[i] != ubs[i] );
      assert( consMatrix.getColSizes()[i] >= 0 );

      auto colvec = consMatrix.getColumnCoefficients( i );
   }

   msg.debug( this, 1, "----------------called---------------\n\n" );
   return result;
}

} // namespace papilo

#endif
