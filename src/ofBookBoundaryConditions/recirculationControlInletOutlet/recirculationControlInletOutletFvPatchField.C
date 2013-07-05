/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "recirculationControlInletOutletFvPatchField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF
)
:
    inletOutletFvPatchField<Type>(p, iF)
{
}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf,
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    inletOutletFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const dictionary& dict
)
:
    inletOutletFvPatchField<Type>(p, iF, dict)
{
}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf
)
:
    inletOutletFvPatchField<Type>(ptf)
{}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf,
    const DimensionedField<Type, volMesh>& iF
)
:
    inletOutletFvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::updateCoeffs()
{
    inletOutletFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::write(Ostream& os) const
{
    inletOutletFvPatchField<Type>::write(os); 
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::operator=
(
    const fvPatchField<Type>& ptf
)
{
    inletOutletFvPatchField<Type>::operator=(ptf); 
}


// ************************************************************************* //
