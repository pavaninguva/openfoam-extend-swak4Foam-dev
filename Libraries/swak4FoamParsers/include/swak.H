/*---------------------------------------------------------------------------*\
|                       _    _  _     ___                       | The         |
|     _____      ____ _| | _| || |   / __\__   __ _ _ __ ___    | Swiss       |
|    / __\ \ /\ / / _` | |/ / || |_ / _\/ _ \ / _` | '_ ` _ \   | Army        |
|    \__ \\ V  V / (_| |   <|__   _/ / | (_) | (_| | | | | | |  | Knife       |
|    |___/ \_/\_/ \__,_|_|\_\  |_| \/   \___/ \__,_|_| |_| |_|  | For         |
|                                                               | OpenFOAM    |
-------------------------------------------------------------------------------
License
    This file is part of swak4Foam.

    swak4Foam is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    swak4Foam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with swak4Foam; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class


Description
    Define versions and flags for swak to distinguish different features
    via #ifdef

SourceFiles

Contributors/Copyright:
    2012-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>
    2015-2016 Bruno Santos <wyldckat@gmail.com>
    2016-2018 Mark Olesen <Mark.Olesen@esi-group.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef SwakMacroHeader_H
#define SwakMacroHeader_H

#include "foamVersion4swak.H"
#if (FOAM_VERSION4SWAK_MAJOR < 2)
#error "This swak4Foam-version is only used for the 2.x-versions of OpenFOAM. For lower versions there is a special branch"
#endif

#define VERSION_NR(major,minor,patch) (     \
    10000 * major + \
    100   * minor + \
    patch )

#define VERSION_NR2(major,minor) (     \
    10000 * major + \
    100   * minor + \
    99 )

#define FOAM_VERSION4SWAK VERSION_NR(FOAM_VERSION4SWAK_MAJOR,FOAM_VERSION4SWAK_MINOR,FOAM_VERSION4SWAK_PATCH_NUM)

#if (FOAM_VERSION4SWAK > VERSION_NR2(1,7) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)) || (FOAM_VERSION4SWAK > VERSION_NR2(3,0))
// Just to make sure that stuff that comes from 1.7 works correctly
#define FOAM_HAS_SORTED_TOC
#endif

// OpenFOAM-dev version. Has no number. Is assumed to be 2999.x
#if FOAM_VERSION4SWAK_MAJOR >= 2999
#define FOAM_OF_DEV_VERSION
#endif

#if (defined(FOAM_VERSION4SWAK_IS_EXTEND) && FOAM_VERSION4SWAK_MAJOR<2)
#define FOAM_OLDTIME_PROBLEM
#endif

// in 1.6-ext the operation s1 & s2 of two symmetrical tensor fields does not yield a symmetric tensor
#if defined(FOAM_VERSION4SWAK_IS_EXTEND) || FOAM_VERSION4SWAK_MAJOR>1
#define FOAM_SYMMTENSOR_WORKAROUND
#endif

#if (OPENFOAM_COM >= 1606) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_EIGENVECTORS_RETURNS_SYMMTENSOR
#endif

#if (OPENFOAM_COM >= 1606) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_MISSING_POW2_DEFINITION_IN_COF_METHOD
#endif

// in 1.6-ext nextRelease a different Macro is used for the creation of certain patch types
#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_USE_MAKE_TEMPLATE_PATCH_TYPE
#endif

// Certain OpenFOAM-versions don't have all tensor operations defined
#if FOAM_VERSION4SWAK < VERSION_NR(1,7,0) || defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_INCOMPLETE_OPERATORS
#endif

#if FOAM_VERSION4SWAK <= VERSION_NR2(2,1) || defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_DELTATCHEM_NOT_DIMENSIONED
#endif

// Versions before 2.1
#if FOAM_VERSION4SWAK < VERSION_NR(2,1,0) || defined(FOAM_VERSION4SWAK_IS_EXTEND)
// what is later called mappedPatch is called directMappedPatch
#define FOAM_MAPPED_IS_DIRECTMAPPED
#endif

#if !(FOAM_VERSION4SWAK < VERSION_NR(2,1,0) || defined(FOAM_VERSION4SWAK_IS_EXTEND))
// has basicSources
#define FOAM_HAS_BASICSOURCES
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,2,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_DEFAULTCOMMSTYPE_IS_METHOD
#endif

#if (FOAM_VERSION4SWAK >= VERSION_NR(2,1,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
// this Foam-Version now has ABI-patches
#define FOAM_HAS_ABI_PATCHES
#endif

#if (FOAM_VERSION4SWAK >= VERSION_NR(2,1,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND) \
    || ((FOAM_VERSION4SWAK > VERSION_NR(4,0,9)) && defined(FOAM_VERSION4SWAK_IS_EXTEND))
// the coded function objects have an additional data entry
#define SWAK_FUNCTION_OBJECT_HAS_DATAPTR

#endif

// this changed starting with 2.2
#if FOAM_VERSION4SWAK > VERSION_NR2(2,1)

#if ((FOAM_VERSION4SWAK > VERSION_NR(2,2,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)) \
    || ((FOAM_VERSION4SWAK > VERSION_NR(4,0,9)) && defined(FOAM_VERSION4SWAK_IS_EXTEND))
// this is NOT changed in 2.2.0 but in the earliest commits of 2.2.x
// lookupClass returns a non-const list
#define FOAM_LOOKUPCLASS_NO_CONST
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND)
// meshSearch parameter for sampledSet-constructor is now const
#define FOAM_MESHSEARCH_CONST_SAMPLEDSET
#else
#define FOAM_SAMPLEDSET_NEEDS_REFPOINT
#endif

#if (OPENFOAM_COM >= 1612)
#define FOAM_SAMPLED_SURFACE_ADDITIONAL_METHODS
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND)
// interpolate-method for meshToMesh needs a reduce-operation
#define FOAM_MESHTOMESH_INTERPOLATE_REDUCE
#else
#define FOAM_MESHTOMESH_OLD_STYLE
#endif

#if (OPENFOAM_COM >= 1606)
#define FOAM_MESHTOMESH_MAPSRCTOTGT_REDUCE
#endif

#if (OPENFOAM_COM >= 1606)
#define FOAM_MESHTOMESH_MAPSRCTOTGT_NO_TENSOR
#endif

#ifdef OPENFOAM_COM
#define FOAM_MESHTOMESH_HAS_CORRECTEDCELLVOLUMEWEIGHT
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND) || (FOAM_VERSION4SWAK > VERSION_NR2(4,0))
// functionObject now needs at least dummy-implementations of updateMesh and movePoints
#define FOAM_FUNCTIONOBJECT_NEEDS_UPDATEMESH
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
// new revised fluidThermo
#define FOAM_HAS_FLUIDTHERMO
#endif

#if (FOAM_VERSION4SWAK < VERSION_NR(2,3,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_HAS_FLUIDTHERMO_CLOUD
#endif

// RR from the chemistry does no longer return a complete field
#define FOAM_RR_ONLY_DIMENSIONED_FIELD

// there is no mixed-BC for point patches
#define FOAM_NO_MIXED_POINT_PATCH

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
// this version has fvOptions
#define FOAM_HAS_FVOPTIONS
#endif

#if defined(OPENFOAM_COM) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_FVOPTIONS_IN_FV
#endif

#if defined(FOAM_VERSION4SWAK_IS_COM) || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(2,2))
#define FOAM_HAS_ACMI_INTERFACE
#endif

#if defined(FOAM_VERSION4SWAK_IS_COM) || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(2,2))
#define FOAM_HAS_AMI_INTERFACE
#endif

#if (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK<VERSION_NR(4,0,0))
#define FOAM_OLD_AMI_ACMI
#endif

#if (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(6,0,0))
#define FOAM_ACMI_RESETAMI_NO_PARAMETERS
#endif

#if (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(6,0,0))
#define FOAM_ACMI_HAS_NO_AMI_METHOD
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
// movePoints now gets a polyMesh
#define FOAM_MOVEPOINTS_GETS_POLYMESH
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
// coordinates method of searchable surfaces uses a tmp as return
#define FOAM_SEARCHABLE_SURF_USES_TMP
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_SEARCHABLE_SURF_HAS_BOUND_METHOD
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
// points method of searchable surfaces now part of interface
#define FOAM_SEARCHABLE_SURF_HAS_POINTS
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_EDGEMESH_INCLUDE_WITH_FA
#endif

#endif // version starting with 2.2

// Certain OpenFOAM-versions don't have this method in fvMesh
#if FOAM_VERSION4SWAK < VERSION_NR(1,7,0) || defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_FV_MESH_HAS_NO_SOLVERDICT
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,1)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_HAS_ENERGY_HE
#endif

// Additional tensor types in nextRelease
#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_DEV_ADDITIONAL_TENSOR_TYPES
#endif

// The kineamticPArcel has no property active in 1.6-ext
#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_KINEMTATIC_HAS_NO_ACTIVE_PROPERTY
#endif

// mathematical constants have no separate namespace
#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_NO_SEPARATE_CONSTANT_NAMESPACE
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK<VERSION_NR(4,1,0))
#define FOAM_FUNCTIONOBJECT_EXECUTE_HAS_NO_FORCE
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_FUNCTIONOBJECT_HAS_SEPARATE_WRITE_METHOD_AND_NO_START
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK < VERSION_NR(4,1,0))
#define FOAM_ISTREAM_HAS_NO_STDSTREAM
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND) || (FOAM_VERSION4SWAK > VERSION_NR2(4,0))
#define FOAM_SURFACEWRITER_NOT_A_TEMPLATE
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_PARTICLE_CLASS_IS_TEMPLATE
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK < VERSION_NR2(4, 0))
#define FOAM_HAS_NO_DATAENTRY_CLASS
#endif

#if (OPENFOAM_COM >= 1606) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0)) \
    || (defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK > VERSION_NR2(4, 0)))
#define FOAM_DATAENTRY_IS_NOW_FUNCTION1
#endif

#if (FOAM_VERSION4SWAK_MAJOR>=2) && (FOAM_VERSION4SWAK_MINOR>0)
#define FOAM_DATAENTRY_HAS_TENSOR_INSTANCES
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND) \
    || (defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK > VERSION_NR2(4, 0)))
#define FOAM_DATAENTRY_CLASS_NEEDS_WRITEDATA
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK < VERSION_NR(4,0,9))
#define FOAM_HAS_NO_CODED_CLASS
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_JUMP_IS_JUMP_CYCLIC
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_CYCLIC_FV_PATCH_FIELD_HAS_NEIGHBOUR_PATCH
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_OLD_THERMOPHYSICS
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_NO_SLG_THERMOPHYSICS
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_TOPOSETSOURCE_HAS_SETTYPE
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_HAS_STRINGOPS
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && FOAM_VERSION4SWAK < VERSION_NR(4,1,0)
#define FOAM_DLLIBRARY_USES_STATIC_METHODS
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_COUPLEDPOLYPATCH_HAS_OWNER
#endif

#if FOAM_VERSION4SWAK > VERSION_NR(4,0,9) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_COUPLEDPOLYPATCH_MASTER_IS_OWNER
#endif

#if FOAM_VERSION4SWAK > VERSION_NR2(2,2) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_NEW_MESH2MESH
#endif

#ifdef OPENFOAM_COM
#define FOAM_MESH2MESH_NO_2ND_ORDER_TENSOR
#endif

#if FOAM_VERSION4SWAK > VERSION_NR2(2,2) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_VOLUMETYPE_IS_TYPE
#endif

#if FOAM_VERSION4SWAK < VERSION_NR(2,3,0) || defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_CHEMISTRYMODEL_SOLVE_NEEDS_TIME
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,1)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_HAS_SCOPED_LOOKUP
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_FACECELLWAVE_HAS_TRACKINGDATA
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_FVMESH_IS_DATAOBJECT
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK < VERSION_NR(4,0,9))
#define FOAM_ZONEMESH_HAS_NO_FINDINDEX
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && (FOAM_VERSION4SWAK < VERSION_NR(4,0,9))
#define FOAM_HAS_NO_FOUR_PARAMETER_FINDINSTANCE
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_SOLUTION_HAS_NO_READ_WITH_DICT
#define FOAM_SCHEMES_HAS_NO_READ_WITH_DICT
#define FOAM_FVMESH_NOT_CHILD_OF_FVSCHEMES_SOLUTION
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,2,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_HAS_LOCAL_DEBUGSWITCHES
#endif

#if FOAM_VERSION4SWAK < VERSION_NR2(2,2) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_LDUMATRIX_SOLVER_PERFORMANCE
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,0,0) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_WALLDIST_HAS_Y_METHOD
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,2)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_PTRAITS_HAS_ROOTMAX
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,2,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_MOVED_TIME_AND_STRING_HEADERS
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_FV_HAS_SMOOTH_SWEEP_SPREAD
#endif

#if !defined(FOAM_VERSION4SWAK_IS_EXTEND)
// currently the available version of interpolation2DTable have a syntax error
#define FOAM_NEEDS_PATCHED_INTERPOLATION2DTABLE
#endif

#if ((FOAM_VERSION4SWAK > VERSION_NR2(2,2)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)) || defined(FOAM_NEEDS_PATCHED_INTERPOLATION2DTABLE)
#define FOAM_HAS_INTERPOLATION2DTABLE
#endif

#if (FOAM_VERSION4SWAK >= VERSION_NR(2,2,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_HAS_IOMRFLIST
#endif

#if (FOAM_VERSION4SWAK >= VERSION_NR(2,3,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_MRF_NEW_METHOD_NAME
#endif

#if (FOAM_VERSION4SWAK >= VERSION_NR(3,0,0)) && !defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_MRF_CHANGED_CORIOLIS
#endif


#if FOAM_VERSION4SWAK >= VERSION_NR(4,0,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_LDUSOLVERPERFORMANCE
#elif FOAM_VERSION4SWAK < VERSION_NR(4,0,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_LDUMATRIX_SOLVERPERFORMANCE
#endif

#if (defined(FOAM_VERSION4SWAK_IS_COM) && OPENFOAM_COM < 1612)      \
        || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK<VERSION_NR(5,0,0))
#define FOAM_SOLVERPERFORMANCE_NITERATIONS_NO_VECTOR
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(4,0,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_FVSCHEMES_HAS_SETFLUXREQUIRED
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_POINTPATCHFIELD_HAS_FIVE_TEMPLATE_PARAMETERS
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_HAS_NO_POINT_PATCH_FIELD_TYPEDEF
#endif

#ifndef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_HAS_SYMMETRY_PLANE_POLY_PATCH
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_HAS_TOLERANCE_SWITCHES
#endif

#ifdef FOAM_VERSION4SWAK_IS_EXTEND
#define FOAM_HAS_LONG_DOUBLE_SCALAR
#endif

#if defined(FOAM_VERSION4SWAK_IS_EXTEND) && FOAM_VERSION4SWAK<VERSION_NR(4,0,9)
#define FOAM_TOKEN_CLASS_HAS_FATAL_ERROR
#endif

#if (OPENFOAM_COM >= 1606) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_HAS_TYPE_HEADER_OK
#if (OPENFOAM_COM >= 1712)
#define FOAM_TYPE_HEADER_OK_HAS_EXTRA_PARAMTERS
#endif
#endif

#if (OPENFOAM_COM >= 1606) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_HAS_LOCAL_FILEPATH
#endif

#if (OPENFOAM_COM >= 1712) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_LOCAL_FILEPATH_NEEDS_TYPE_PARAMETER
#endif

#if (OPENFOAM_COM >= 1712) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_READSTREAM_METHOD_NEEDS_BOOL_PARAMETER
#endif

#if (OPENFOAM_COM >= 1606) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_COMPONENT_NAMES_ARE_CONST_PTR
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_PATCHFIELDTYPE_IN_GEOFIELD_IS_NOW_PATCH
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_IOFILTER_WRITE_NEEDS_BOOL
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_HAS_NO_IOFILTERFUNCTIONOBJECT_ANYMORE
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
// TODO: currently only used to comment the instantiations out
#define FOAM_CODED_FUNCTION_OBJECT_NEW_INTERFACE
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR2(3,0))
#define FOAM_NO_DIMENSIONEDINTERNAL_IN_GEOMETRIC
#endif

#if (OPENFOAM_COM >= 1612) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_MAKE_TEMPLATE_PATCHTYPE_FIELD_USES_PRIMITIVES
#endif

#if __cplusplus > 199711L
#define FOAM_CXX_COMPILER_ALLOWS_NON_POD_IN_UNION
#endif

#if __cplusplus < 201103L
#define FOAM_CXX_COMPILER_HAS_NO_NULLPTR
#ifndef nullptr
#define nullptr NULL
#endif
#endif

#if (OPENFOAM_COM >= 1706)
#define FOAM_RANDOM_CLASS_NEW_INTERFACE
#endif

#if (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>VERSION_NR(5,0,0))
#define FOAM_RANDOM_CLASS_GAUSS_RENAMED
#endif

#if (OPENFOAM_COM >= 1706) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_PSTREAM_COMMSTYPE_IS_ENUMCLASS
#endif

#if (OPENFOAM_COM >= 1712) \
    || (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(5,0,0))
#define FOAM_REGIOOBJECT_WRITEOBJECT_WITH_VALID
#endif

#if (OPENFOAM_COM >= 1803)
#define FOAM_LIST_HAS_MOVABLE_CONSTRUCT
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(4,1,0) && defined(FOAM_VERSION4SWAK_IS_EXTEND)
#define FOAM_HAS_IMMERSED_BOUNDARY_CONDITION
#endif

#if (OPENFOAM_COM >= 1803)
#define FOAM_HASH_PTR_LIST_ACCEPTS_NO_RAW_POINTERS
#endif

#if (OPENFOAM_COM >= 1803)
#define FOAM_SAMPLEDSURFACE_SAMPLE_WANTS_INTERPOLATION
#endif

#if (OPENFOAM_COM >= 1803)
#define FOAM_MESHTOMESH_WANTS_PROCMAP_PARAMETER
#endif

#if (OPENFOAM_COM >= 1811)
#define FOAM_MESHOBJECT_GRAVITY
#endif

#if (defined(FOAM_VERSION4SWAK_IS_ORG) && FOAM_VERSION4SWAK>=VERSION_NR(6,0,0))
#define FOAM_TIME_HAS_SEPARATE_SETDELTAT_NOADJUST
#endif

#include "swakVersion.H"
#include "DebugOStream.H"
#include "BackportMacros.H"

#endif

// ************************************************************************* //
