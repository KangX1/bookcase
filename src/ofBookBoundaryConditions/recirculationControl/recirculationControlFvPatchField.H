/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2012 OpenFOAM Foundation
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
    Foam::recirculationControlFvPatchField

Description

    Decorator for the fvPatchField.

    This boundary condition checks for recirculation using the specified flux
    field and controls the specified controlled patch in order to reduce the 
    recirculation.

    Usage

        type             controlledRecirculation;
        baseType         zeroGradient;
        fluxField        phi; 
        controlledPatch  inlet;  

SeeAlso
    Foam::fvPatchField

SourceFiles
    recirculationControlFvPatchField.C
    recirculationControlFvPatchFields.C

Authors:
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#ifndef recirculationControlFvPatchField_H
#define recirculationControlFvPatchField_H

#include "autoPtr.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class recirculationControlFvPatchField Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class recirculationControlFvPatchField
:
    public fvPatchField<Type>
{

protected:

    // Base boundary condition. 
    tmp<fvPatchField<Type> > baseTypeTmp_; 

    const word baseTypeName_; 
    const word fluxFieldName_; 
    const word controlledPatchName_;

    scalar recirculationRate_; 

public:

    //- Runtime type information
    TypeName("recirculationControl");

    // Constructors

        //- Construct from patch and internal field
        recirculationControlFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        recirculationControlFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given recirculationControlFvPatchField onto a new patch
        recirculationControlFvPatchField
        (
            const recirculationControlFvPatchField<Type>&,
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        recirculationControlFvPatchField
        (
            const recirculationControlFvPatchField<Type>&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchField<Type> > clone() const
        {
            return tmp<fvPatchField<Type> >
            (
                new recirculationControlFvPatchField<Type>(*this)
            );
        }

        //- Construct as copy setting internal field reference
        recirculationControlFvPatchField
        (
            const recirculationControlFvPatchField<Type>&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchField<Type> > clone
        (
            const DimensionedField<Type, volMesh>& iF
        ) const
        {
            return tmp<fvPatchField<Type> >
            (
                new recirculationControlFvPatchField<Type>(*this, iF)
            );
        }

        virtual tmp<Field<Type > > gradientInternalCoeffs () const
        {
            return baseTypeTmp_->gradientInternalCoeffs(); 
        }

    // Member functions
    
        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;

    // Member operators

        virtual void operator=(const fvPatchField<Type>& pvf);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "recirculationControlFvPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
