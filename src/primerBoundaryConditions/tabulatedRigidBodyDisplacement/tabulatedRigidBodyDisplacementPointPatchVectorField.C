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

\*---------------------------------------------------------------------------*/

#include "tabulatedRigidBodyDisplacementPointPatchVectorField.H"
#include "pointPatchFields.H"
#include "addToRunTimeSelectionTable.H"
#include "Time.H"
#include "fvMesh.H"
#include "IFstream.H"
#include "transformField.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tabulatedRigidBodyDisplacementPointPatchVectorField::
tabulatedRigidBodyDisplacementPointPatchVectorField
(
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF
)
:
    fixedValuePointPatchField<vector>(p, iF),
    dict_()
{}


tabulatedRigidBodyDisplacementPointPatchVectorField::
tabulatedRigidBodyDisplacementPointPatchVectorField
(
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF,
    const dictionary& dict
)
:
    fixedValuePointPatchField<vector>(p, iF, dict),
    dict_(dict)
{
    updateCoeffs();
}


tabulatedRigidBodyDisplacementPointPatchVectorField::
tabulatedRigidBodyDisplacementPointPatchVectorField
(
    const tabulatedRigidBodyDisplacementPointPatchVectorField& ptf,
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF,
    const pointPatchFieldMapper& mapper
)
:
    fixedValuePointPatchField<vector>(ptf, p, iF, mapper),
    dict_()
{}


tabulatedRigidBodyDisplacementPointPatchVectorField::
tabulatedRigidBodyDisplacementPointPatchVectorField
(
    const tabulatedRigidBodyDisplacementPointPatchVectorField& ptf,
    const DimensionedField<vector, pointMesh>& iF
)
:
    fixedValuePointPatchField<vector>(ptf, iF),
    dict_()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tabulatedRigidBodyDisplacementPointPatchVectorField::autoMap
(
    const pointPatchFieldMapper& m
)
{
    fixedValuePointPatchField<vector>::autoMap(m);

}


void tabulatedRigidBodyDisplacementPointPatchVectorField::rmap
(
    const pointPatchField<vector>& ptf,
    const labelList& addr
)
{
    const tabulatedRigidBodyDisplacementPointPatchVectorField& sDoFptf =
        refCast<const tabulatedRigidBodyDisplacementPointPatchVectorField>(ptf);

    fixedValuePointPatchField<vector>::rmap(sDoFptf, addr);

}


void tabulatedRigidBodyDisplacementPointPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    const polyMesh& mesh = this->dimensionedInternalField().mesh()();
    const Time& t = mesh.time();
    const pointPatch& ptPatch = this->patch();

    autoPtr<solidBodyMotionFunction> SBMFPtr
    (
        solidBodyMotionFunction::New(dict_, t)
    );

    pointField vectorIO(mesh.points().size(),vector::zero);

    vectorIO = transform
    (
        SBMFPtr().transformation(),
        ptPatch.localPoints()
    );

    Field<vector>::operator=
    (
        vectorIO-ptPatch.localPoints()
    );

    fixedValuePointPatchField<vector>::updateCoeffs();
}


void tabulatedRigidBodyDisplacementPointPatchVectorField::write(Ostream& os) const
{
    pointPatchField<vector>::write(os);

    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePointPatchTypeField
(
    pointPatchVectorField,
    tabulatedRigidBodyDisplacementPointPatchVectorField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
