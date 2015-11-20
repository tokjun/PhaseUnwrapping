cmake_minimum_required(VERSION 2.8.9)

project(PhaseUnwrapping)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/PhaseUnwrapping")
set(EXTENSION_CATEGORY "Filtering")
set(EXTENSION_CONTRIBUTORS "Junichi Tokuda (Brigham and Women's Hospital)")
set(EXTENSION_DESCRIPTION "Phase unwrapping module. This is a CLI wrapper for itkQualityGuidedPhaseUnwrappingImageFilter class developed by Davis M. Vigneault et al.")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/PhaseUnwrapping.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/PhaseUnwrapping/Screenshots/1.png")

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(PhaseUnwrappingModule)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})
