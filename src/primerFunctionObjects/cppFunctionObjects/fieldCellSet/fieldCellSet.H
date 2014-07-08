/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original authors
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

Class
    Foam::fieldCellSet

Description
    Creates a set of cells using function objects. 

SourceFiles
    fieldCellSet.C
    fieldCellSetTemplates.C

Authors:
    Tomislav Maric tomislav@sourceflux.de
    Jens Hoepken jens@sourceflux.de
    Kyle Mooney kyle.g.mooney@gmail.com

\*---------------------------------------------------------------------------*/

#ifndef fieldCellSet_H
#define fieldCellSet_H

#include "HashSet.H"
#include "regIOobject.H"
#include "polyMesh.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    class polyMesh;

/*---------------------------------------------------------------------------*\
                         Class fieldCellSet Declaration
\*---------------------------------------------------------------------------*/

class fieldCellSet
:
    public labelHashSet, 
    public regIOobject
{

public:

    // TODO: foamToVTK expects the "cellSet" object in the header.  
    //       Move to the constructor: modify the IOobject name after 
    //       construction. 
    TypeName ("cellSet"); 
   
    const polyMesh& mesh_; 

// Constructors
        
    //- Construct from polyMesh and name. Checks for valid cell ids.
    fieldCellSet 
    (
        const IOobject& io, 
        const polyMesh& mesh
    );

// Member Functions
    
    //- Write
    bool writeData(Ostream& os) const;  

    //- Edit
    template<typename Collector>
    void collectCells(const volScalarField& field, Collector col); 

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "fieldCellSetTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
