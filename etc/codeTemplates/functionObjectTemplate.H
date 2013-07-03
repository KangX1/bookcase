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
    Template for use with code generation of a OutputFilter 
    functionObject.

SourceFiles
    functionObject.C

\*---------------------------------------------------------------------------*/

#ifndef TYPENAME_H
#define TYPENAME_H

#include "stringList.H"
#include "pointField.H"
#include "functionObject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class objectRegistry;
class dictionary;
class polyMesh;
class mapPolyMesh;
class fvMesh;

/*---------------------------------------------------------------------------*\
                         A templated functionObject
\*---------------------------------------------------------------------------*/

class TYPENAME
    :
        public functionObject
{
    // Private data
    
        //- Registry
        const objectRegistry& obr_;

    // Private Member Functions

        const objectRegistry& obr() const;

        const fvMesh& mesh() const;

public:

    //- Runtime type information
    TypeName("TYPENAME");

    // Constructors

        //- Construct for given objectRegistry and dictionary.
        //  Allow the possibility to load fields from files
        TYPENAME
        (
            const word& name,
            const objectRegistry& unused,
            const dictionary&,
            const bool loadFromFilesUnused = false
        );


    //- Destructor
     ~TYPENAME();


    // Member Functions

        //- Read the system calls
         bool read(const dictionary&);

        //- Execute the "executeCalls" at each time-step
         bool execute(const bool forceWrite=false);

        //- Called at the start of the time-loop
         bool start();

        //- Execute the "endCalls" at the final time-loop
         bool end();

        //- Write, execute the "writeCalls"
         void write();

        //- Called when time was set at the end of the Time::operator++
         bool timeSet();

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
