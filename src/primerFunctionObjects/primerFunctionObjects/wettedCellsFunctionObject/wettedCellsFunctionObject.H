/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Description
    A function object that marks cells in the domain that get wetted
    during the course of the simulation.

SourceFiles
    wettedCellsFunctionObject.C

Authors: 
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#ifndef wettedCellsFunctionObject_H
#define wettedCellsFunctionObject_H

#include "functionObject.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         A templated functionObject
\*---------------------------------------------------------------------------*/

class wettedCellsFunctionObject
    :
        public functionObject
{
    // Private data

        //- Time
        const Time& time_; 

        //- Mesh reference;  
        const fvMesh& mesh_; 

        //- Volume fraction field. 
        const volScalarField& alpha1_; 

        //- Wetted cells field.
        autoPtr<volScalarField> wettedCellsPtr_; 

        //- Wetted cell tolerance. 
        scalar wettedTolerance_; 

        //- Wetted domain percent.
        scalar wettedDomainPercent_; 

public:

    //- Runtime type information
    TypeName("wettedCells");

    // Constructors

        //- Construct for given objectRegistry and dictionary.
        //  Allow the possibility to load fields from files
        wettedCellsFunctionObject
        (
            const word& name,
            const Time& time,
            const dictionary& dict
        );

    //- Destructor
     ~wettedCellsFunctionObject();


    // Member Functions

        //- Access time
        const Time& getTime() const
        {
            return time_; 
        }

        //- Read the system calls
         bool read(const dictionary&);

        //- Execute the "executeCalls" at each time-step
         bool execute(const bool forceWrite=false);

        //- Calculate wetted cells
         virtual void calcWettedCells(); 

        //- Test if volume fraction value marks the cell wetted. 
         bool isWetted(scalar s)
         {
             return (s > wettedTolerance_); 
         } 


        //- Compute wetted domain percent.
         virtual void calcWettedDomainPercent(); 

        //- Get wetted domain perceintage.
         scalar getWettedDomainPercent()
         {
             return wettedDomainPercent_; 
         } 

        //- Report 
        virtual void report(); 
        
        //- Called at the start of the time-loop
         bool start();

        //- Execute the "endCalls" at the final time-loop
         bool end();

        //- Called when time was set at the end of the Time::operator++
         //bool timeSet();

        //- Update for changes of mesh
         void updateMesh(const mapPolyMesh&);

        //- Update for changes of mesh
         void movePoints(const polyMesh&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
