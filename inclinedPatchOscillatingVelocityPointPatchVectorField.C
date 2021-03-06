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

#include "inclinedPatchOscillatingVelocityPointPatchVectorField.H"
#include "pointPatchFields.H"
#include "addToRunTimeSelectionTable.H"
#include "Time.H"
#include "polyMesh.H"
#include "mathematicalConstants.H" 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

oscillatingVelocityPointPatchVectorField::
oscillatingVelocityPointPatchVectorField
(
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF
)
:
    fixedValuePointPatchField<vector>(p, iF),
    amplitude_(0.0),
    freq_(0.0),
    rc_(0.0),
    centerPoint_(vector::zero),
    direction_(vector::zero),
    p0_(p.localPoints())
{}


oscillatingVelocityPointPatchVectorField::
oscillatingVelocityPointPatchVectorField
(
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF,
    const dictionary& dict
)
:
    fixedValuePointPatchField<vector>(p, iF),
    amplitude_(0.),
    freq_(0.),
    rc_(0.),
    centerPoint_(vector::zero),
    direction_(vector::zero)
{
    fixedValuePointPatchField<vector>::operator=(vectorField("value",dict,p.size()));
    dict.lookup("amplitude") >> amplitude_;
    dict.lookup("freq") >> freq_ ;
    dict.lookup("rc") >> rc_;
    centerPoint_ = dict.lookupOrDefault<vector>("centerPoint",vector::zero);
    direction_ = dict.lookupOrDefault<vector>("direction",vector::zero);

    if (!dict.found("value"))
    {
        updateCoeffs();
    }

    if (dict.found("p0"))
    {
        p0_ = vectorField("p0", dict , p.size());
    }
    else
    {
        p0_ = p.localPoints();
    }
}


oscillatingVelocityPointPatchVectorField::
oscillatingVelocityPointPatchVectorField
(
    const oscillatingVelocityPointPatchVectorField& ptf,
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF,
    const pointPatchFieldMapper& mapper
)
:
    fixedValuePointPatchField<vector>(ptf, p, iF, mapper),
    amplitude_(ptf.amplitude_),
    freq_(ptf.freq_),
    rc_(ptf.rc_),
    centerPoint_(ptf.centerPoint_),
    direction_(ptf.direction_),
    p0_(ptf.p0_, mapper)
{}

oscillatingVelocityPointPatchVectorField::
oscillatingVelocityPointPatchVectorField
(
    const oscillatingVelocityPointPatchVectorField& ptf,
    const DimensionedField<vector, pointMesh>& iF
)
:
    fixedValuePointPatchField<vector>(ptf, iF),
    amplitude_(ptf.amplitude_),
    freq_(ptf.freq_),
    rc_(ptf.rc_),
    centerPoint_(ptf.centerPoint_),
    direction_(ptf.direction_),
    p0_(ptf.p0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void oscillatingVelocityPointPatchVectorField::autoMap
(
    const pointPatchFieldMapper& m
)
{
    fixedValuePointPatchField<vector>::autoMap(m);

    p0_.autoMap(m);
}


void oscillatingVelocityPointPatchVectorField::rmap
(
    const pointPatchField<vector>& ptf,
    const labelList& addr
)
{
    const oscillatingVelocityPointPatchVectorField& oVptf =
        refCast<const oscillatingVelocityPointPatchVectorField>(ptf);

    fixedValuePointPatchField<vector>::rmap(oVptf, addr);

    p0_.rmap(oVptf.p0_, addr);
}


void oscillatingVelocityPointPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    const polyMesh& mesh = this->internalField().mesh()();
    const Time& t = mesh.time();
    const pointPatch& p = this->patch();
    vectorField sd = p0_;
    vector p0rot;
    vector pointMove(vector::zero);
    scalar PI = constant::mathematical::pi;

    for(label patchPointI = 0; patchPointI < p0_.size(); patchPointI++)
    {
        p0rot = p0_[patchPointI] - centerPoint_;    

        pointMove  = amplitude_*(1-pow(mag(p0rot)/rc_,2.))*sin(2*PI*freq_*t.value())*(direction_);
        
        p0rot = pointMove;

        sd[patchPointI] = p0rot;
    };

    Field<vector>::operator=
    (
        (p0_ + sd - p.localPoints())
       /t.deltaTValue()
    );

    fixedValuePointPatchField<vector>::updateCoeffs();
}


void oscillatingVelocityPointPatchVectorField::write(Ostream& os) const
{
    pointPatchVectorField::write(os);
    os.writeKeyword("amplitude")
        << amplitude_ << token::END_STATEMENT << nl;
    os.writeKeyword("freq")
        << freq_ << token::END_STATEMENT << nl;
    os.writeKeyword("rc")
        << rc_ << token::END_STATEMENT << nl;
    os.writeKeyword("centerPoint") 
        << centerPoint_ << token::END_STATEMENT << nl;
    os.writeKeyword("direction") 
        << direction_ << token::END_STATEMENT << nl;
    p0_.writeEntry("p0", os);
    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePointPatchTypeField
(
    pointPatchVectorField,
    oscillatingVelocityPointPatchVectorField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
