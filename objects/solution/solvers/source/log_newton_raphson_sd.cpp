/*! 
* \file log_newton_raphson.cpp
* \ingroup objects
* \brief LogNewtonRaphson class source file.
* \author Josh Lurz
* \date $Date$
* \version $Revision$
*/

#include "util/base/include/definitions.h"
#include <string>
#include <iostream>
#include <fstream>

#include "solution/solvers/include/solver_component.h"
#include "solution/solvers/include/log_newton_raphson_sd.h"
#include "solution/util/include/calc_counter.h"
#include "marketplace/include/marketplace.h"
#include "containers/include/world.h"
#include "solution/util/include/solver_info_set.h"
#include "solution/util/include/solver_info.h"
#include "solution/util/include/solver_library.h"
#include "util/base/include/configuration.h"
#include "util/base/include/util.h"

#include <mtl/matrix.h>
#include <mtl/mtl.h>
#include <mtl/utils.h>

using namespace std;

const string LogNewtonRaphsonSaveDeriv::SOLVER_NAME = "LogNewtonRaphsonSaveDeriv";
extern ofstream logfile, bugoutfile;

//! Default Constructor. Need to call constructor of class next up in heigharcy. Constructs the base class. 
LogNewtonRaphsonSaveDeriv::LogNewtonRaphsonSaveDeriv( Marketplace* marketplaceIn, World* worldIn, CalcCounter* calcCounterIn ):LogNewtonRaphson( marketplaceIn, worldIn, calcCounterIn ) {
}

//! Default Destructor. Currently does nothing.
LogNewtonRaphsonSaveDeriv::~LogNewtonRaphsonSaveDeriv(){
}

//! Init method.  
void LogNewtonRaphsonSaveDeriv::init() {
   calcDerivativeDefault = true;
   derivativesCalculated = false;
   savedMatrixSize = 0;
}

//! Get the name of the SolverComponent
const string& LogNewtonRaphsonSaveDeriv::getNameStatic() {
    return SOLVER_NAME;
}

//! Get the name of the SolverComponent
const string& LogNewtonRaphsonSaveDeriv::getName() const {
    return SOLVER_NAME;
}

//! Calculate derivatives
SolverComponent::ReturnCode LogNewtonRaphsonSaveDeriv::calculateDerivatives( SolverInfoSet& solverSet, Matrix& JFSM, Matrix& JFDM, Matrix& JF, int period ) {
           
   // Always calculated if derivativesCalculated is true. Otherwise, only calculated once.
   if ( calcDerivativeDefault || (!calcDerivativeDefault && !derivativesCalculated ) ) {
      derivativesCalculated = true;
               
      // Calculate derivatives.
      SolverLibrary::derivatives( marketplace, world, solverSet, period ); 
      // numDerivativeCalcs++;
   
      logfile << ",,,Derivatives calculated" << endl;
      if ( trackED ) {
         cout <<" End Derivatives " << endl;
      }
               
      // Update the JF, JFDM, and JFSM matrices
      SolverLibrary::updateMatrices( solverSet, JFSM, JFDM, JF );
      SolverLibrary::invertMatrix( JF );
               
      // Save matricies
      if ( !calcDerivativeDefault ) {
         JFSave.reset( new Matrix( solverSet.getNumSolvable(), solverSet.getNumSolvable() ) );
         JFDMSave.reset( new Matrix( solverSet.getNumSolvable(), solverSet.getNumSolvable() ) );
         JFSMSave.reset( new Matrix( solverSet.getNumSolvable(), solverSet.getNumSolvable() ) );
         copy( JF, *JFSave );
         copy( JFDM, *JFDMSave );
         copy( JFSM, *JFSMSave );
         savedMatrixSize = solverSet.getNumSolvable();
      }
      // If not calculating derivatives then restore from saved values
      } else {
         if ( solverSet.getNumSolvable() != savedMatrixSize ) {
            logfile << "ERROR: Matrix sizes changed " << solverSet.getNumSolvable() << ", "<< savedMatrixSize << endl;
            return FAILURE_SOLUTION_SIZE_CHANGED;
         }
         copy( *JFSave, JF );
         copy( *JFDMSave, JFDM );
         copy( *JFSMSave, JFSM );
      }
           
      return SUCCESS;
}